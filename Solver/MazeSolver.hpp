#ifndef MAZESOLVER_H
#define MAZESOLVER_H

#include "MazeMessage.hpp"
#include <iostream>

class MazeSolver {
private:
    maze_solver::MazeMessage maze;
    
public:
    void solve(maze_solver::MazeMessage maze);
};
#endif
