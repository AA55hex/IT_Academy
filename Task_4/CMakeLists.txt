cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(Task_4)

find_package(SDL2 REQUIRED)

add_library(gfx STATIC
    test/gfx.cpp
    test/gfx.h)

target_link_libraries(gfx PRIVATE
    ppm)

add_subdirectory(ppm_base)

add_executable(test_ppm
    test/test.cpp)

target_link_libraries(test_ppm PRIVATE
    ppm
    gfx
    SDL2::SDL2)
