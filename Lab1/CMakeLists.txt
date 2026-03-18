cmake_minimum_required(VERSION 4.1)
project(Lab1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab1
        main.cpp)

target_link_libraries(Lab1 SDL3)
