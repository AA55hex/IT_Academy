cmake_minimum_required(VERSION 3.18)
project(Task_2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(SDL2_SHARED "Using dynamic" ON)

find_package(SDL2 REQUIRED)

add_executable(Test bin/test.cpp)
target_link_directories(Test PRIVATE ${SDL2_INCLUDE_DIRS})

if(SDL2_SHARED)
    message(SHARED)
    target_link_libraries(Test PRIVATE SDL2::SDL2 SDL2::SDL2main)
else()
    message(STATIC)
    target_link_libraries(Test PRIVATE SDL2::SDL2-static)
endif()



enable_testing()
add_test(NAME Simple_test COMMAND Test)
