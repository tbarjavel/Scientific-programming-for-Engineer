cmake_minimum_required (VERSION 3.1)
project (Particles)

set(CMAKE_CXX_STANDARD 14)

include_directories(/usr/include/eigen3)
add_executable(main main.cc)
