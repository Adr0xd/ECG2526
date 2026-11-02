cmake_minimum_required(VERSION 3.16)
project(Lab2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# On macOS (Apple Silicon), tell CMake where Homebrew packages are located
if(APPLE)
    list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew")
endif()

# Find the official SDL3 CMake package
find_package(SDL3 REQUIRED)

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
        bresenham.cpp
        projection.cpp
        camera.cpp
        rasterization.cpp
)

# Linking against the imported target SDL3::SDL3 automatically configures
# both header include paths (-I) and library linking (-l)
target_link_libraries(Lab2 PRIVATE SDL3::SDL3)