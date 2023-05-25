cmake_minimum_required(VERSION 3.25)
project(Graphic)

set(CMAKE_CXX_STANDARD 20)

file(GLOB Exceptions_SRC
        "Exceptions/*.h")
file(GLOB Math_SRC
        "LowLevel/*.h")

add_subdirectory(Tests)
add_executable(Graphic main.cpp ${Exceptions_SRC} ${Math_SRC} Graphic.h)
