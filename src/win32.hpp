//
// Created by yoshino on 2022/10/20.
//

#ifndef GTHREAD_WIN32_HPP
#define GTHREAD_WIN32_HPP

namespace gthread {
    constexpr auto WIN32_LEAN_AND_MEAN = 1;
#define NOMINMAX  1
    constexpr auto NOCOMM = 1;
}
#include <windows.h>

#endif //GTHREAD_WIN32_HPP
