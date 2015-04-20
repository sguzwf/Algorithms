cmake_minimum_required(VERSION 2.8)
project(sort)
set(CMAKE_BUILD_TYPE release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_executable(sortCompare src/sort.cpp src/sort_algorithm.cpp)

