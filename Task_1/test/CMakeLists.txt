include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(Test test.cpp)
target_link_libraries(Test PUBLIC Hello_lib)
target_compile_features(Test PRIVATE cxx_std_17)

install(TARGETS Test DESTINATION bin)
