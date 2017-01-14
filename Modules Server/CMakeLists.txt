# Miscellaneous settings.
cmake_minimum_required(VERSION 2.5)
project(ModulesServer)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11")

# Executables to be build.
add_executable(ModulesServer
		"Main.cpp"
		"ModuleData.cpp"
		"ModuleHandler.cpp"
		"../maze_parser/MazeMessage.cpp"
		"../maze_parser/MazeParser.cpp"
		"../SocketUtils/SocketUtils.cpp")


