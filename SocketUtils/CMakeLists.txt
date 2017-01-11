# Miscellaneous settings.
cmake_minimum_required(VERSION 2.5)
project(SocketUtils)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# SocketUtils library.
add_library(SocketUtils
		"SocketUtils.hpp"
		"SocketUtils.cpp"
)


