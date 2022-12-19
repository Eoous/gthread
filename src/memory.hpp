#pragma once
#include "win32.hpp"

namespace gthread {
    auto malloc0(size_t size) {
        return HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
    }

    auto msize(void* ptr) {
        return HeapSize(GetProcessHeap(), 0, ptr);
    }

    auto mfree(void* ptr) {
        HeapFree(GetProcessHeap(), 0, ptr);
    }

    auto mmove(void* dst, const void* src, size_t size) {
        RtlMoveMemory(dst, src, size);
    }

    auto mfill(void* dst, int val, size_t size) {
        RtlFillMemory(dst, size, val);
    }

    auto mzero(void* dst, size_t size) {
        RtlZeroMemory(dst, size);
    }

    auto mequal(const void* src, const void* cmp, size_t size) {
        return RtlCompareMemory(src, cmp, size) == size;
    }

}