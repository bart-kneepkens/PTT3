# Miscellaneous settings.

cmake_minimum_required(VERSION 2.5)
project(Plotter)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


# All core files required by executables.

add_library(Core_Files
        "../maze_parser/MazeMessage.hpp"
        "../maze_parser/MazeMessage.cpp"
        "../Module/IModule.hpp"
        "../Scanner/MotorDriver.cpp"
        "../Scanner/MotorDriver.h"
        "PlotInstruction.cpp"
        "PlotInstruction.h"
        "Plotter.cpp"
        "Plotter.h"
        "PlotterController.cpp"
        "PlotterController.h"
        "PlotterStatus.h"
)


# Executables to be build.

add_executable(PlotterProgram PlotterProgram.cpp)


# Linking core files to executables.

target_link_libraries(PlotterProgram Core_Files)
