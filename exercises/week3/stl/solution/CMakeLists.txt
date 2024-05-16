cmake_minimum_required(VERSION 2.6)

add_executable(stl
  main.cc
)

set (CMAKE_CXX_STANDARD 17)

add_executable(algorithms
  algorithms.cc
)

add_executable(memory
  memory.cc
)
