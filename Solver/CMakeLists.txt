# Miscellaneous settings.

cmake_minimum_required(VERSION 2.5)
project(Solver)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


# All core files required by executables.

add_library(Core_Files
        "../maze_parser/MazeMessage.hpp"
        "../maze_parser/MazeMessage.cpp"
        "../maze_parser/MazeParser.hpp"
        "../maze_parser/MazeParser.cpp"
		"MazeSolver.hpp"
        "MazeSolver.cpp"
)


# Executables to be build.

add_executable(Solver.o Solver.cpp ${CORE_FILES})
add_executable(SolverSocketServer.o SolverSocketServer.cpp ${CORE_FILES})
add_executable(SolverSocketClient.o SolverSocketClient.cpp ${CORE_FILES})


# Linking core files to executables.

target_link_libraries(Solver.o Core_Files)
target_link_libraries(SolverSocketServer.o Core_Files)
target_link_libraries(SolverSocketClient.o Core_Files)
