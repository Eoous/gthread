#pragma once
#include "win32.hpp"

auto __malloc0(size_t size) {
    return HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
}

auto __msize(void* ptr) {
    return HeapSize(GetProcessHeap(), 0, ptr);
}

auto __mfree(void* ptr) {
    HeapFree(GetProcessHeap(), 0, ptr);
}

auto __mmove(void* dst, const void* src, size_t size) {
    RtlMoveMemory(dst, src, size);
}

auto __mfill(void* dst, int val, size_t size) {
    RtlFillMemory(dst, size, val);
}

auto __mzero(void* dst, size_t size) {
    RtlZeroMemory(dst, size);
}

auto __mequal(const void* src, const void* cmp, size_t size) {
    return RtlCompareMemory(src, cmp, size) == size;
}
