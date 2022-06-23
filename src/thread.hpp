#pragma once

#include <any>

class mopthread {
public:
    int nref[1];     // atomic reference count
    uint32_t tid;    // thread id
    std::any handle; // win32 thread handle
    std::any status; // exit code
    std::any param;  // startup parameter
};

extern const std::any crt_module;
extern const uint32_t tls_index;
extern const mopthread main_thread;