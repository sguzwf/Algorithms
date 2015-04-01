cmake_minimum_required(VERSION 2.8)
project(sort)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")
add_executable(sortCompare src/sort.cpp src/sort_algorithm.cpp)

