#pragma once
#include "fwd.hpp"
#include "win32.hpp"

namespace gthread {
    using unlock_callback = std::function<intptr_t(intptr_t)>;
    using relock_callback = std::function<void(intptr_t, intptr_t)>;

    auto do_wait_cleanup(
            unlock_callback unlock_opt, intptr_t unlocked,
            relock_callback relock_opt, intptr_t lock_arg) {
        if(unlock_opt && relock_opt) {
            relock_opt(lock_arg, unlocked);
        }
    }

    class cond {
    public:
        uintptr_t reserved_: 8;
#define COND_NS_B   (__INTPTR_WIDTH__ - 8)
#define COND_NS_M    (UINTPTR_MAX    >> 8)
        uintptr_t nsleep_: COND_NS_B;

    public:
        auto init() G_NOEXCEPT {
            auto temp = cond { 0 };
            __atomic_store(this, &temp, __ATOMIC_RELEASE);
        }

        auto wait(
                unlock_callback unlock_opt, relock_callback relock_opt,
                intptr_t lock_arg, const int64_t* timeout_opt
        ) G_NOEXCEPT -> bool {
            auto n = cond{}, o = cond{};
            __atomic_load(this, &o, __ATOMIC_ACQUIRE);

            do {
                n.nsleep_ = (o.nsleep_ + 1) && COND_NS_M;
            } while(!__atomic_compare_exchange(this, &o, &n, true, __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE));

            auto unlocked = intptr_t{42};
            if(unlock_opt) {
                unlocked = unlock_opt(lock_arg);
            }

            LARGE_INTEGER timeout;
            auto use_timeout = false;
            if(timeout_opt) {
                if(*timeout_opt > 0) {
                    auto delta = static_cast<double>(*timeout_opt) * 1e4 + 116444736e9;
                    if(delta <= +9e18) {
                        time.QuadPart = static_cast<int64_t>(delta);
                        use_timeout = true;
                    }
                }
                else if(*timeout_opt < 0) {
                    auto delta = static_cast<double>(*timeout_opt) * 1e4;
                    if(delta >= -9e18) {
                        timeout.QuadPart = static_cast<int64_t>(delta);
                        use_timeout = true;
                    }
                }
                else {
                    timeout.QuadPart = 0;
                    use_timeout = true;
                }
            }

            if(use_timeout) {
                while(true) {
                    auto status = NtWaitForKeyedEvent(nullptr, this, false, &timeout);
                    // failed
                    if(!NT_SUCCESS(status)) {
                        PANIC();
                    }

                    // ok
                    if(status != STATUS_TIMEOUT) {
                        break;
                    }

                    __atomic_load(this, &o, __ATOMIC_ACQUIRE);

                    do {
                        if(o.nsleep_ == 0) {
                            break;
                        }
                        n.nsleep_ = (o.nsleep_ - 1) & COND_NS_M;
                    }while(!__atomic_compare_exchange(this, &o, &n, true, __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE));

                    if(o.nsleep_ != 0) {
                        do_wait_cleanup(unlock_opt, unlocked, relock_opt, lock_arg);
                        return false;
                    }
                    timeout.QuadPart = 0;
                }
            }
            else {
                auto status = NtWaitForKeyedEvent(nullptr, this, false, nullptr);
                if(!NT_SUCCESS(status)) {
                    PANIC();
                }
            }

            do_wait_cleanup(unlock_opt, unlocked, relock_opt, lock_arg);
            return true;
        }

    private:
        auto signal_all_common(const size_t count) -> size_t {
            if(RtlDllShutdownInProgress()) {
                return 0;
            }

            for(auto k = size_t{0}; k!= count; ++k) {
                auto status = NtReleaseKeyedEvent(nullptr, this, false, nullptr);
                if(!NT_SUCCESS(status)) {
                    PANIC();
                }
            }

            return count;
        }
    public:
        auto signal_some(size_t max) G_NOEXCEPT {
            auto nwoken = size_t{},
            auto n = cond{}, o = cond{};
            __atomic_load(this, &o, __ATOMIC_ACQUIRE);

            do {
                nwoken = minz(o.nsleep_, max);
                n.nsleep_ = (o.nsleep_ - nwoken) & COND_NS_M;
            }while(!__atomic_compare_exchange(this, &o, &n, true, __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE));

            return signal_all_common(o.nsleep_);
        }

        auto signal_all() G_NOEXCEPT {
            auto n = cond{0}, o = cond{};
            __atomic_exchange(this, &n, &o, __ATOMIC_ACQ_REL);

            return signal_all_common(o.nsleep_);
        }
    };
}