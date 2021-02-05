cmake_minimum_required(VERSION 2.8)

project(Task_3_1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(SDL2_SHARED ON)

find_package(SDL2 REQUIRED)

add_executable(game-3.1 "main.cpp")

if(SDL2_SHARED)
    target_link_libraries(game-3.1 PRIVATE SDL2::SDL2)
else()
    target_link_libraries(game-3.1 PRIVATE SDL2::SDL2-static)
endif()

target_compile_features(game-3.1 PRIVATE cxx_std_17)
