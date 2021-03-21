add_library(engine STATIC
    src/engine.cpp
    include/engine.h
    gl_shaders/triangle_test.vert
    gl_shaders/triangle_test.frag)

target_include_directories(engine PUBLIC include)

target_include_directories(engine
	  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
	  )

target_link_libraries(engine PRIVATE gladlib)

target_link_libraries(engine PRIVATE SDL2::SDL2)
