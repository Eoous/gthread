//
// Created by yoshino on 2022/10/20.
//

#ifndef GTHREAD_FWD_HPP
#define GTHREAD_FWD_HPP

#include <any>
#include <functional>
#include <memory>

#ifndef STARTUP
#  define DYNCONST const
#  define INLINE extern __inline__ __attribute__((gnu_inline__))
#endif

namespace gthread {
    // Make some forward-declarations.
    using thread_control = class thread_control;
    using thread_procedure = std::function<void(std::shared_ptr<thread_control>)>;

    using mutex = class mutex;
    using cond = class cond;
    using once = class once;

    // Define static data.
    extern DYNCONST std::any crt_module;
    extern DYNCONST uint32_t tls_index;
    extern DYNCONST thread_control main_thread;
}
#endif //GTHREAD_FWD_HPP