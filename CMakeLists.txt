cmake_minimum_required(VERSION 3.15)

project(myTlpi)
include_directories(include)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(myTlpi src/syscall_speed.c)
target_link_libraries(myTlpi tlpi)
