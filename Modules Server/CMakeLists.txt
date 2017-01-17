# Miscellaneous settings.
cmake_minimum_required(VERSION 2.5)
project(ModulesServer)
set(CMAKE_CXX_COMPILER /home/martin/buildroot/output/host/usr/bin/arm-linux-g++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lrt -pthread -std=c++11")

# Executables to be build.
add_executable(ModulesServer
		"Main.cpp"
		"ModuleData.cpp"
		"ModuleHandler.cpp"
		"ModuleChain.cpp"
		"../maze_parser/MazeMessage.cpp"
		"../maze_parser/MazeParser.cpp"
		"../SocketUtils/SocketUtils.cpp"
		"../Logger/Logger.cpp"
        "../Logger/LoggerCentral.cpp"
        "../Gpio/LedController.cpp")

target_link_libraries(ModulesServer -lrt)


