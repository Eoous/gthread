cmake_minimum_required(VERSION 3.15)
project(gthread)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_SHARED_LINKER_FLAGS "-Wl,-e,gthread_startup,--exclude-symbols,gthread_startup")
add_library(gthread SHARED src/startup.cc)

add_executable(main main.cc)