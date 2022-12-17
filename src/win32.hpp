#pragma once
#include <windows.h>
#include <ntstatus.h>
#include <winternl.h>

#define WIN32_LEAN_AND_MEAN  1
#define NOMINMAX  1
#define NOCOMM 1

#undef RtlCopyMemory
#undef RtlMoveMemory
#undef RtlFillMemory
#undef RtlZeroMemory
#undef RtlCompareMemory
#undef RtlEqualMemory
namespace gthread {
    void __stdcall
    RtlMoveMemory(void* __dst, const void* __src, SIZE_T __size) __attribute__((__dllimport__, __nothrow__));

    void __stdcall RtlFillMemory(void* __dst, SIZE_T __size, int __val) __attribute__((__dllimport__, __nothrow__));

    void __stdcall RtlZeroMemory(void* __dst, SIZE_T __size) __attribute__((__dllimport__, __nothrow__));

    SIZE_T __stdcall RtlCompareMemory(const void* __s1, const void* __s2,
                                      SIZE_T __size) __attribute__((__dllimport__, __pure__, __nothrow__));

    NTSTATUS __stdcall
    NtWaitForKeyedEvent(HANDLE __event, void* __key, BOOLEAN __alertable, const LARGE_INTEGER* __timeout) __attribute__((__dllimport__, __nothrow__));

    NTSTATUS __stdcall
    NtReleaseKeyedEvent(HANDLE __event, void* __key, BOOLEAN __alertable, const LARGE_INTEGER* __timeout) __attribute__((__dllimport__, __nothrow__));

    BOOLEAN __stdcall
    RtlDllShutdownInProgress(void) __attribute__((__dllimport__, __nothrow__));
}
