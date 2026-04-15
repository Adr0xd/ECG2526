cmake_minimum_required(VERSION 4.1)
project(Lab2)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab2
        main.cpp
        vec2.cpp
        vec3.cpp
        vec4.cpp
        mat3.cpp
        mat4.cpp
        testMatrix.cpp
        testTransform.cpp
        transform.cpp
        polygon.cpp
        clip.cpp
)

target_link_libraries(Lab2 SDL3)
