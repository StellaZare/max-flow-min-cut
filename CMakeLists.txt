cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(cpp_project LANGUAGES CXX)

# Require compliance with C++11 standard.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Include directories
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/app")

# Find required packages
find_package(Catch2 REQUIRED)

# Define a program target called hello.
add_executable(main ${CMAKE_CURRENT_SOURCE_DIR}/app/main.cpp)
add_executable(test_graph ${CMAKE_CURRENT_SOURCE_DIR}/app/test_graph.cpp)
add_executable(test_maxmin ${CMAKE_CURRENT_SOURCE_DIR}/app/test_maxmin.cpp)
