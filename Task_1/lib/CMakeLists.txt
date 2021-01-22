add_library(Hello_lib
    "include/hello.h"
    "source/hello.cpp")
target_compile_features(Hello_lib PRIVATE cxx_std_17)
target_include_directories(Hello_lib INTERFACE include)

install(TARGETS Hello_lib
    DESTINATION lib)
install(FILES "include/hello.h"
    DESTINATION lib)
