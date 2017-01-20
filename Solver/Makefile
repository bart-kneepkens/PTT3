CFLAGS=-O2 -Wall

TESTFLAGS= -lgtest -lgtest_main -pthread

SOLVER_TEST_SOURCE=MazeSolverTest.cpp

SOLVER_SOURCE=MazeSolver.cpp

MESSAGE_SOURCE=../maze_parser/MazeMessage.cpp



GPP=g++

.PHONY: test

test: 
	$(GPP) $(CFLAGS) $(SOLVER_TEST_SOURCE) $(SOLVER_SOURCE) $(MESSAGE_SOURCE) $(TESTFLAGS) -o MazeSolverTest
	./MazeSolverTest

clean:
	@rm -rf MazeSolverTest
