cmake_minimum_required(VERSION 2.8.4)
project(Q3MapView)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

add_subdirectory(External/glfw-3.0.4)
include_directories(External/glfw-3.0.4/include)

include_directories(External/glm-0.9.6.1/glm)
add_subdirectory(External/glm-0.9.6.1)

add_subdirectory(src)