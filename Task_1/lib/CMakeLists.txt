add_library(Hello_lib
    "${CMAKE_CURRENT_SOURCE_DIR}/include/hello.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/source/hello.cpp")
target_compile_features(Hello_lib PRIVATE cxx_std_17)
target_include_directories(Hello_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(Hello_lib PROPERTIES
    POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS})

install(TARGETS Hello_lib
    DESTINATION lib)

install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/hello.h"
    DESTINATION include)
