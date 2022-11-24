#ifndef GTHREAD_FWD_HPP
#define GTHREAD_FWD_HPP

#include <any>
#include <functional>
#include <memory>

#if (0 + __BYTE_ORDER__) != __ORDER_LITTLE_ENDIAN__
#error Windows platforms are assumed to be little-endian.
#endif

#ifndef STARTUP
#  define DYNCONST const
#  define INLINE extern __inline__ __attribute__((gnu_inline__))
#else
#  define DYNCONST
#endif

constexpr auto PANIC = []() {
    __builtin_trap();
};

namespace gthread {
    // Make some forward-declarations.
    using thread_control = class thread_control;

    using mutex = class mutex;
    using cond = class cond;
    using once = class once;

    // Define static data, which are defined in 'startup.cc'
    extern DYNCONST std::any crt_module;
    extern DYNCONST uint32_t tls_index;
    extern DYNCONST thread_control main_thread;
}
#endif //GTHREAD_FWD_HPP