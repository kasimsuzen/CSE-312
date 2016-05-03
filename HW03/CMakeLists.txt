cmake_minimum_required(VERSION 3.3)
project(HW03)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(SOURCE_FILES main.cpp MemoryCell.cpp Instruction.cpp Simulation.cpp Disk.cpp PageTableEntry.cpp RAM.cpp PageTable.cpp)
add_executable(HW03 ${SOURCE_FILES})
