add_library(gladlib STATIC
    src/glad.c
    include/KHR/khrplatform.h
    include/glad/glad.h)

target_include_directories(gladlib PUBLIC include/)
