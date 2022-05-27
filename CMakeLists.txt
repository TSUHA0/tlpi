cmake_minimum_required(VERSION 3.15)

project(myTlpi)
include_directories(include)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

link_libraries(tlpi)

add_executable(myTlpi src/syscall_speed.c)
add_executable(copy src/fileio/copy.cpp)
add_executable(seek_io src/fileio/seek_io.cpp)
add_executable(tea src/fileio/tee.cpp)