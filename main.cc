#include "./src/win32.hpp"

auto main() -> int {
    LoadLibraryA("./libgthread.dll");
    return 0;
}
