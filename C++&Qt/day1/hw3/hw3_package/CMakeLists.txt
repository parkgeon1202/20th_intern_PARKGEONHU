cmake_minimum_required(VERSION 3.11)

project(cpp_test)
include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(test src/hw3.cpp src/hw3_1.cpp)
