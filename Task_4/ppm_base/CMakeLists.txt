set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_library(ppm
    include/ppm_base.h
    include/render.h
    src/raster.cpp
    src/line_render.cpp
    src/triangle.cpp
    src/basic_structures.cpp)
set_target_properties(ppm PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF)
target_include_directories(ppm PUBLIC include)
