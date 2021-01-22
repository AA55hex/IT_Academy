add_executable(Test test.cpp)
target_link_libraries(Test LINK_PUBLIC Hello_lib)
target_compile_features(Test PRIVATE cxx_std_17)

install(TARGETS Test DESTINATION bin)
