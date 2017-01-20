CFLAGS=-O2 -Wall

TESTFLAGS= -lgtest -lgtest_main -pthread

SOLVER_TEST_SOURCE=MazeSolverTest.cpp

SOLVER_SOURCE=MazeSolver.cpp

MESSAGE_SOURCE=../maze_parser/MazeMessage.cpp

PARSER_SOURCE=../maze_parser/MazeParser.cpp

SOCKETUTILS_SOURCE=../SocketUtils/SocketUtils.cpp

MODULECLIENT_SOURCE=../Generic\ Module\ Client/ModuleClient.cpp

GPP=g++

all: solver test

solver: $(SOLVER_SOURCE)
	$(GPP) $(CFLAGS) $(SOLVER_SOURCE) $(MESSAGE_SOURCE) $(MODULECLIENT_SOURCE) $(SOCKETUTILS_SOURCE) $(PARSER_SOURCE) -o solver

test: $(SOLVER_TEST)
	$(GPP) $(CFLAGS) $(SOLVER_TEST_SOURCE) $(SOLVER_SOURCE) $(MESSAGE_SOURCE) $(TESTFLAGS) -o MazeSolverTest
	./MazeSolverTest

clean:
	@rm -rf MazeSolverTest solver
