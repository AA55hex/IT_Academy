cmake_minimum_required(VERSION 3.8)

project(Task_6)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS ON)

find_package(SDL2 REQUIRED
    NAMES SDL2 sdl2)

add_subdirectory(glad)

add_subdirectory(engine)
add_subdirectory(game)
