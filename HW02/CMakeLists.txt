cmake_minimum_required(VERSION 3.3)
project(HW02)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(SOURCE_FILES main.cpp Memory.cpp Instruction.cpp Process.cpp)
add_executable(HW02 ${SOURCE_FILES})