#pragma once
#include "fwd.hpp"

namespace gthread {
    using thread_procedure = std::function<void(std::shared_ptr<thread_control>)>;

    class thread_control {
    public:
        int nref_[1];     // atomic reference count
        uint32_t tid_;    // thread id
        std::any handle_; // win32 thread handle_

        thread_procedure proc_; // exit code
        intptr_t param_[4];  // startup parameter
    };

    auto gthread_exit_callback() noexcept {

    }
}
