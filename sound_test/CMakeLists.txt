cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(sound_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(SDL2 REQUIRED
    NAMES SDL2 sdl2)

add_executable(sound_test main.cpp
    include/sound.h
    src/sound.cpp)

target_link_libraries(sound_test PUBLIC SDL2::SDL2)

target_include_directories(sound_test PUBLIC include/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)
