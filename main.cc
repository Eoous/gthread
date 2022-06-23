#include <iostream>

#include "./src/thread.hpp"

// when an exe or a dll mounting into memory, address file starts is image base(value: mz)
extern char crt_image_base
  __asm("__image_base__");

int main() {
    const auto crt_module = &crt_image_base;
    auto main_thread = mopthread{
        .nref = {1}
    };
    std::cout << crt_module << std::endl;
    return 0;
}
