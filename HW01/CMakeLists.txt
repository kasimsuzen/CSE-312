cmake_minimum_required(VERSION 3.3)
project(HW01)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall  -D DEBUG")

set(SOURCE_FILES main.cpp Memory.cpp Instruction.cpp Simulation.cpp )
add_executable(HW01 ${SOURCE_FILES})