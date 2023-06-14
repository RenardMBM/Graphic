cmake_minimum_required(VERSION 3.25)
project(Graphic)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Tests)
add_executable(Graphic main.cpp Graphic.h)
