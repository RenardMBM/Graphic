cmake_minimum_required(VERSION 3.25)
project(Graphic)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Tests)

file(GLOB Exceptions_head
        "Exceptions/*.h")
file(GLOB Math_head
        "LowLevel/*.h")
file(GLOB Engine_head
        "Engine/*.h")
file(GLOB Engine_SRC
        "Engine/*.cpp")

set(SOURCE_FILES ${Engine_SRC})

add_executable(Graphic main.cpp Graphic.h ${Exceptions_head} ${Math_head} ${Engine_head} ${Engine_SRC})
