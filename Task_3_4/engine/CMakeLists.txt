add_library(engine
    include/engine.h
    src/engine.cpp)
target_include_directories(engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(engine PRIVATE SDL2::SDL2)

target_compile_features(engine PRIVATE cxx_std_17)
