cmake_minimum_required(VERSION 3.3)
project(control_flow_optimization)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp tid.cpp tid.h solution.cpp solution.h pair_tid.cpp pair_tid.h)
add_executable(control_flow_optimization ${SOURCE_FILES})