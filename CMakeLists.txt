cmake_minimum_required(VERSION 4.1)
project(Labor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -g)

add_executable(main main.cpp)