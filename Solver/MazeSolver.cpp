#include "MazeSolver.hpp"
#include "MazeMessage.hpp"
#include <unistd.h>
#include <iostream>

char mock_maze[10][11] =
{
    "# ########",
    "# ########",
    "#       ##",
    "#######  #",
    "#      # #",
    "#      # #",
    "#      # #",
    "#      # #",
    "#      # #",
    "######## #",
};

const char WALL = '#';
const char FREE = ' ';
const char PERSON = '*';

class COORD {
public:
    int X;
    int Y;
    COORD(int x = 0, int y = 0) { X = x, Y = y; }
    COORD(const COORD &coord) { X = coord.X; Y  = coord.Y; }
};

COORD startingPoint = COORD(1,0);
COORD endingPoint = COORD(8,8);

// For debugging
void printMaze(){
    for(int Y = 0; Y < 9; Y++){
        std::cout << mock_maze[Y] << std::endl;
    }
    std::cout << std::endl;
}

bool solverino(int X, int Y){
    mock_maze[Y][X] = PERSON;
    
    printMaze();
    usleep(500000);
    
    // check if reached goal
    std::cout << X << ":" << Y  << std::endl;
    if(X == endingPoint.X && Y == endingPoint.Y){
        std::cout << "FINISHED" << std::endl;
        return true;
    }
    
    // Recursively search for the goal
    if(X > 0 && mock_maze[Y][X - 1] == FREE && solverino(X - 1, Y)){
        return true;
    }
    
    if(X < 10 && mock_maze[Y][X + 1] == FREE && solverino(X + 1, Y)){
        return true;
    }
    
    if(Y > 0 && mock_maze[Y - 1][X] == FREE && solverino(X, Y - 1)){
        return true;
    }
    
    if(Y < 10 && mock_maze[Y + 1][X] == FREE && solverino(X, Y + 1)){
        return true;
    }
    
    // Otherwise we need to backtrack and find another solution.
    mock_maze[Y][X] = FREE;
    
    printMaze();
    usleep(500000);
    return false;
}

int main(){
    if(solverino(startingPoint.X, startingPoint.Y)){
        printMaze();
    } else {
        std::cout << "Not solved :(" << std::endl;
    }
    return 0;
}

MazeSolver::solve(MazeMessage maze){
    // Solve maze
    // Place the solution in the MazeMessage
}

