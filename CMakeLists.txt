cmake_minimum_required(VERSION 3.15)
project(gthread)

set(CMAKE_CXX_STANDARD 20)

#set(CMAKE_SHARED_LINKER_FLAGS "-Wl,-egthread_startup,--exclude-symbols,gthread_startup")
add_library(gthread SHARED main.cc)

add_executable(wrapper wrapper.cc)