# Miscellaneous settings.
cmake_minimum_required(VERSION 2.5)
project(Solver)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

# All core files required by executables.
add_library(Core_Files
        "MazeSolver.cpp"
        "../maze_parser/MazeMessage.cpp"
        "../maze_parser/MazeParser.cpp"
)

# Executables to be build.
add_executable(Solver
        "Solver.cpp")
add_executable(SolverModule
        "../Generic Module Client/ModuleClient.cpp"
        "../SocketUtils/SocketUtils.cpp")

# Linking core files to executables.
target_link_libraries(Solver Core_Files)
target_link_libraries(SolverModule Core_Files)
