cmake_minimum_required(VERSION 3.0)
project(Task_1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)
option(BUILD_SHARED_LIBS "Using shared libs" ON)

add_subdirectory(lib)
add_subdirectory(test)

enable_testing()
add_test(NAME No_Args COMMAND Test)
add_test(NAME Args COMMAND Test test with args)
