option(BUILD_SHARED_LIBS "Using shared libs" ON)
option(SDL2_SHARED ON)

if(BUILD_SHARED_LIBS)
    set(SDL2_SHARED ON)
endif()

add_library(engine
    include/engine.h
    src/engine.cpp)
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


find_package(SDL2 REQUIRED
    NAMES SDL2 sdl2)
if(SDL2_SHARED)
    target_link_libraries(engine PRIVATE SDL2::SDL2)
else()
    target_link_libraries(engine PRIVATE SDL2::SDL2-static)
endif()



target_compile_features(engine PRIVATE cxx_std_17)
