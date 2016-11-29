cmake_minimum_required(VERSION 3.5)

project(Solver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file (GLOB SOURCE_FILES
        "*.h"
        "*.hpp"
        "*.c"
        "*.cpp"
        "maze_parser/*.h"
        "maze_parser/*.hpp"
        "maze_parser/*.c"
        "maze_parser/*.cpp"
)

add_executable(Solver ${SOURCE_FILES})