add_library(lib_manager
    include/lib_manager.h
    src/lib_manager.cpp)
target_include_directories(lib_manager PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${SDL2_DIR})

target_link_libraries(lib_manager PRIVATE SDL2::SDL2)

target_compile_features(engine PRIVATE cxx_std_17)
