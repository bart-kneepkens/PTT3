# Miscellaneous settings.
cmake_minimum_required(VERSION 2.5)
project(Module)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11")

# Core files required by all executables.
add_library(Core_Files
        "../maze_parser/MazeMessage.hpp"
        "../maze_parser/MazeMessage.cpp"
        "../maze_parser/MazeParser.hpp"
        "../maze_parser/MazeParser.cpp"
		"SocketUtils.hpp"
		"SocketUtils.cpp"
)

# Files required only by server.
add_library(Server_Files
        "InputHandler.hpp"
        "ModuleData.hpp"
        "ModuleData.cpp" ModuleHandler.hpp ModuleHandler.cpp)

# Files required only by client.
add_library(Client_Files
        "IModule.hpp"
        "../Solver/MazeSolver.hpp"
        "../Solver/MazeSolver.cpp")

# Executables to be build.
add_executable(ModuleServer ModuleServer.cpp)
add_executable(ModuleClient ModuleClient.cpp)

# Linking core files to executables.
target_link_libraries(ModuleServer Core_Files Server_Files)
target_link_libraries(ModuleClient Core_Files Client_Files)


