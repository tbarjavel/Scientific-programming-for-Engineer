
cmake_minimum_required(VERSION 2.6)
project(snippet)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES  ${PROJECT_SOURCE_DIR}/*.cpp)
foreach(f ${SOURCES})
  get_filename_component(basename ${f} NAME_WE)
  get_filename_component(dir ${f} DIRECTORY)
  add_executable(${basename} ${f})
endforeach()
