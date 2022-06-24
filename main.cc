#include <iostream>

#include "./src/thread.hpp"
#include "./src/win32.hpp"

// when an exe or a dll mounting into memory, address file starts is image base(value: mz)
extern char image_base_from_gnu_ld
        __asm("__image_base__");

namespace gthread {
    DYNCONST std::any crt_module = &image_base_from_gnu_ld;
    DYNCONST uint32_t tls_index = 0;
    DYNCONST auto main_thread = thread_control{
            .nref = {0}
    };

}

int main() {
    std::cout << gthread::crt_module.has_value() << std::endl;
    return 0;
}
