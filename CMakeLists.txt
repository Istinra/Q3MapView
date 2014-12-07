cmake_minimum_required(VERSION 2.8.4)
project(Q3MapView)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(External/glfw-3.0.4)
include_directories(External/glfw-3.0.4/include)
add_subdirectory(src)