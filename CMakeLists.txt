cmake_minimum_required(VERSION 3.25)
project(Graphic)

set(CMAKE_CXX_STANDARD 20)

#add_subdirectory(Tests)
include(FetchContent)

FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
#FetchContent_MakeAvailable(SFML)

FetchContent_GetProperties(sfml)
if(NOT sfml_POPULATED)
    FetchContent_Populate(sfml)
    add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR})
endif()

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

target_link_libraries(Graphic PRIVATE sfml-graphics
                                      sfml-system
                                      sfml-window)
