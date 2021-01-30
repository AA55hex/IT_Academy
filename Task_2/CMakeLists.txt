cmake_minimum_required(VERSION 3.18)
project(Task_2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(SDL2_SHARED "Using dynamic" ON)

find_package(SDL2 REQUIRED
    NAMES SDL2 sdl2)

add_executable(sdl2-version-test bin/test.cpp)
target_link_directories(sdl2-version-test PRIVATE ${SDL2_INCLUDE_DIRS})

if(SDL2_SHARED)
    target_link_libraries(sdl2-version-test PRIVATE SDL2::SDL2)
else()
    target_link_libraries(sdl2-version-test PRIVATE SDL2::SDL2-static)
endif()

install(TARGETS sdl2-version-test DESTINATION bin)

enable_testing()
add_test(NAME Simple_test COMMAND sdl2-version-test)
