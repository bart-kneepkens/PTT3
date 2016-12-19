# Miscellaneous settings.

cmake_minimum_required(VERSION 2.5)
project(Module)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


# All core files required by executables.

add_library(Core_Files
        "../maze_parser/MazeMessage.hpp"
        "../maze_parser/MazeMessage.cpp"
        "../maze_parser/MazeParser.hpp"
        "../maze_parser/MazeParser.cpp"
		"../Solver/MazeSolver.hpp"
        "../Solver/MazeSolver.cpp"
		"IModule.hpp"
		"SocketUtils.hpp"
		"SocketUtils.cpp"
)


# Executables to be build.

add_executable(SolverSocketServer SolverSocketServer.cpp)
add_executable(SolverSocketClient SolverSocketClient.cpp)


# Linking core files to executables.

target_link_libraries(SolverSocketServer Core_Files)
target_link_libraries(SolverSocketClient Core_Files)
