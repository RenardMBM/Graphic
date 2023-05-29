cmake_minimum_required(VERSION 3.25)
project(Graphic)

set(CMAKE_CXX_STANDARD 20)

file(GLOB Exceptions_SRC
        "Exceptions/*.h")
file(GLOB Math_head_SRC
        "LowLevel/*.h")
file(GLOB Engine_head_SRC
        "Engine/*.h")
file(GLOB Engine_imp_SRC
        "Engine/*.cpp")
add_subdirectory(Tests)
add_executable(Graphic main.cpp ${Exceptions_SRC} ${Math_head_SRC}
                                ${Engine_head_SRC} ${Engine_imp_SRC})
