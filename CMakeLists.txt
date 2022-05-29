cmake_minimum_required(VERSION 3.15)

project(myTlpi)
include_directories(include)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

link_libraries(tlpi)

add_executable(large_file src/fileio/large_file.cpp)
add_executable(free_and_sbrk src/memaclloc/free_and_sbrk.cpp)