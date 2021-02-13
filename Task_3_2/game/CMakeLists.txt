add_executable(game-3.2 game.cpp)
target_link_libraries(game-3.2 PRIVATE engine)
target_compile_features(game-3.2 PRIVATE cxx_std_17)
