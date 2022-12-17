#pragma once
#include "fwd.hpp"
#include "win32.hpp"

namespace gthread {
    auto utc_now() __G_NOEXCEPT -> int64_t {
        FILETIME ft;
        GetSystemTimeAsFileTime(&ft);

        ULARGE_INTEGER ui;
        ui.LowPart = ft.dwLowDateTime;
        ui.HighPart = ft.dwHighDateTime;

        // convert it into unix epoch in milliseconds.
        return static_cast<int64_t>(((double) (int64_t) ui.QuadPart - 116444736e9) / 1e4);
    }

    int64_t tick_count() __G_NOEXCEPT {
        return GetTickCount();
    }

    int64_t perf_count() __G_NOEXCEPT {
        LARGE_INTEGER li;
        QueryPerformanceCounter(&li);
        return (double) li.QuadPart * perf_frequency_reciprocal;
    }
}
