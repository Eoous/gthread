#include <iostream>

#define STARTUP 1

#include "thread.hpp"
#include "win32.hpp"

int gthread_startup(HANDLE instance, DWORD reason, LPVOID reserved) __asm__("gthread_startup");

extern char image_base_from_gnu_ld
        __asm__("__image_base__");

DYNCONST std::any crt_module = &image_base_from_gnu_ld;
DYNCONST uint32_t tls_index = 0;
DYNCONST auto main_thread = gthread::thread_control{
        .nref = {0}
};

int gthread_startup(HANDLE instance, DWORD reason, LPVOID reserved) {
    std::puts("hello, gthread_startup");

    if (reason == DLL_PROCESS_ATTACH) {
        std::puts("process attach dll");

        tls_index = TlsAlloc();
        if (tls_index == TLS_OUT_OF_INDEXES) {
            std::puts("tls out of indexes");
        }

        main_thread.tid = GetCurrentThreadId();
        main_thread.handle = OpenThread(THREAD_ALL_ACCESS, false, main_thread.tid);
        if (!main_thread.handle.has_value()) {
            std::puts("main_thread.handle doesn't contain value");
        }
    }

    if (reason == DLL_PROCESS_DETACH) {
        std::puts("process detach dll");
        auto control = reinterpret_cast<gthread::thread_control*>(TlsGetValue(tls_index));
        if (control) {
            control->on_detach();
        }
    }

    return 0;
}
