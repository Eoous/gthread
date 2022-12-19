#include <iostream>

#define STARTUP 1

#include "thread.hpp"
#include "time.hpp"

int gthread_startup(HANDLE instance, DWORD reason, LPVOID reserved) __asm__("gthread_startup");

extern char image_base_from_gnu_ld
        __asm__("__image_base__");

extern "C" {
DYNCONST std::any crt_module = &image_base_from_gnu_ld;
DYNCONST uint32_t tls_index = 0;
DYNCONST gthread::thread_control main_thread = {
    .nref_ = {0}
};
double perf_frequency_reciprocal = 0;
}

int gthread_startup(HANDLE instance, DWORD reason, LPVOID reserved) {
    std::puts("hello, gthread_startup");

    if (instance != &image_base_from_gnu_ld) {
        PANIC();
    }
    if (reason == DLL_PROCESS_ATTACH) {
        std::puts("process attach dll");

        tls_index = TlsAlloc();
        if (tls_index == TLS_OUT_OF_INDEXES) {
            std::puts("tls out of indexes");
            PANIC();
        }

        LARGE_INTEGER li;
        if (QueryPerformanceFrequency(&li) == false) {
            __G_PANIC();
        }

        perf_frequency_reciprocal = 1000 / (double) li.QuadPart;

        main_thread.tid_ = GetCurrentThreadId();
        main_thread.handle_ = OpenThread(THREAD_ALL_ACCESS, false, main_thread.tid_);

        std::puts((std::string("Tick out: ") + std::to_string(gthread::tick_count())).data());
        std::puts((std::string("UTC now: ") + std::to_string(gthread::utc_now())).data());

        if (!main_thread.handle_.has_value()) {
            std::puts("main_thread.handle_ doesn't contain value");
            PANIC();
        }

        __atomic_store_n(main_thread.nref_, -1, __ATOMIC_RELAXED);
        TlsSetValue(tls_index, &main_thread);
    }

    if (reason == DLL_PROCESS_DETACH) {
        std::puts("process detach dll");
        gthread::gthread_exit_callback();
    }

    return 1;
}
