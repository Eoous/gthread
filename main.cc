#include <iostream>

#include "./src/thread.hpp"
#include "./src/win32.hpp"

int gthread_startup(HANDLE instance, DWORD reason, LPVOID reserved) __asm__("gthread_startup");

// when an exe or a dll mounting into memory, address file starts is image base(value: mz)
extern char image_base_from_gnu_ld
        __asm__("__image_base__");

namespace gthread {
    DYNCONST std::any crt_module = &image_base_from_gnu_ld;
    DYNCONST uint32_t tls_index = 0;
    DYNCONST thread_control main_thread = thread_control{
            .nref = {0}
    };
}

int gthread_startup(HANDLE instance, DWORD reason, LPVOID reserved) {
    std::puts("hello, gthread_startup");
    return 0;
}
