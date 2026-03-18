cmake_minimum_required(VERSION 4.1)
project(Lab2)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab2
        main.cpp
        Vector2D.cpp
        Vector3D.cpp
        Vector4D.cpp)

target_link_libraries(Lab2 SDL3)
