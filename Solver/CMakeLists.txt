cmake_minimum_required(VERSION 3.5)

project(Solver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES json.hpp MazeParser.hpp main.cpp)

add_executable(Solver ${SOURCE_FILES})