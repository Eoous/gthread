#include <windows.h>

extern "C" {
int puts(const char *);
}

auto main() -> int {
    auto dll_name = "libgthread.dll";
    if(LoadLibraryA(dll_name) == nullptr){
        puts("Err: Load Dynamic Library");
    }

    return 0;
}
