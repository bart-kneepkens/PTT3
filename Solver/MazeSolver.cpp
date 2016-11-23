#include "MazeSolver.hpp"
#include "MazeMessage.hpp"
#include <unistd.h>
#include <iostream>
#include <vector>

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

COORD startingPoint = COORD(8,9);
COORD endingPoint = COORD(1,0);

// For debugging
void maze_solver::MazeSolver::printMaze(){
    for(int Y = 0; Y < 10; Y++){
        
        for(int i=0; i<10; i++)
        {
            std::cout << maze[Y][i];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool maze_solver::MazeSolver::solveForCoordinates(int X, int Y){
    maze[Y][X] = PERSON;
    
    //printMaze();
    //usleep(500000);
    
    // check if reached goal
    if(X == endingPoint.X && Y == endingPoint.Y){
        return true;
    }
    
    // Recursively search for the goal
    if(X > 0 && maze[Y][X - 1] == FREE && solveForCoordinates(X - 1, Y)){
        return true;
    }
    
    if(X < 10 && maze[Y][X + 1] == FREE && solveForCoordinates(X + 1, Y)){
        return true;
    }
    
    if(Y > 0 && maze[Y - 1][X] == FREE && solveForCoordinates(X, Y - 1)){
        return true;
    }
    
    if(Y < 10 && maze[Y + 1][X] == FREE && solveForCoordinates(X, Y + 1)){
        return true;
    }
    
    // Otherwise we need to backtrack and find another solution.
    maze[Y][X] = FREE;
    
    //printMaze();
    //usleep(500000);
    return false;
}

maze_solver::MazeSolver::MazeSolver(){}

void maze_solver::MazeSolver::solve(maze_solver::MazeMessage maze_){
    std::vector<std::vector<char>> mazeVector = *(maze_.Maze);
    
    this->maze = mazeVector;
    
    // Find starting and ending point
    // same for now
    

    
    
    // Solve maze
    
    if(solveForCoordinates(startingPoint.X, startingPoint.Y)){
        printMaze();
    }else {
        std::cout << "Not solved :(" << std::endl;
    }
    
    // Place the solution in the MazeMessage
}

