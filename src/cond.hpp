#pragma once
#include "fwd.hpp"

namespace gthread {
    class cond {
        using unlock_callback = std::function<intptr_t(intptr_t)>;
        using relock_callback = std::function<void(intptr_t, intptr_t)>;
    public:
        uintptr_t _reserved: 8;
#define COND_NS_B   (__INTPTR_WIDTH__ - 8)
#define COND_NS_M    (UINTPTR_MAX    >> 8)
        uintptr_t _nsleep: COND_NS_B;

    public:
        auto init() G_NOEXCEPT {
            auto temp = cond { 0 };
            __atomic_store(this, &temp, __ATOMIC_RELEASE);
        }

        auto wait(
                unlock_callback unlock_opt, relock_callback relock_opt,
                intptr_t lock_arg, const int64_t* timeout_opt
        ) G_NOEXCEPT {}

        auto signal_some(size_t max) G_NOEXCEPT {}

        auto signal_all() G_NOEXCEPT {

        }
    };
}