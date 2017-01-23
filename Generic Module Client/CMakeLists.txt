# Miscellaneous settings.
cmake_minimum_required(VERSION 2.5)
project(ModuleClient)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11")

# Executables to be build.
add_executable(ModuleClient
		"ModuleClient.cpp"
        	"IModule.hpp"
		"../Solver/MazeSolver.cpp"
		"../maze_parser/MazeMessage.cpp"
		"../maze_parser/MazeParser.cpp"
		"../SocketUtils/SocketUtils.cpp"
		"../SimpleMazePrinter/SimpleMazePrinter.cpp")



