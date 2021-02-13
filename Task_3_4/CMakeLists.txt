cmake_minimum_required(VERSION 2.8)

project(Task_3_4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS ON)

find_package(SDL2 REQUIRED
    NAMES SDL2 sdl2)

add_subdirectory(engine)
add_subdirectory(game)
add_subdirectory(lib_manager)
