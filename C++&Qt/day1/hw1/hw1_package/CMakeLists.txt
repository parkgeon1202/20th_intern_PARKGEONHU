cmake_minimum_required(VERSION 3.11)

project(cpp_test)
include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(test src/hw1.cpp src/hw1_1.cpp)
