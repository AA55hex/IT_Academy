cmake_minimum_required(VERSION 3.5)

project(Task_5 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)

add_subdirectory(glad)
add_subdirectory(enginelib)
add_executable(opengl_test main.cpp
    vertexes.txt)

target_link_libraries(opengl_test PRIVATE engine)
