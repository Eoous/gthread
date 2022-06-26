#ifndef GTHREAD_THREAD_HPP
#define GTHREAD_THREAD_HPP

#include "fwd.hpp"

namespace gthread {
    class thread_control {
    public:
        int nref[1];     // atomic reference count
        uint32_t tid;    // thread id
        std::any handle; // win32 thread handle

        thread_procedure proc; // exit code
        intptr_t param[4];  // startup parameter

        auto on_detach() noexcept {

        }
    };
}

#endif //GTHREAD_THREAD_HPP