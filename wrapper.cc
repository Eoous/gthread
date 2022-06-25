//
// Created by yoshino on 2022/10/21.
//

#include "./src/win32.hpp"

auto main() -> int {
    LoadLibraryA("../libgthread.dll");
    return 0;
}
