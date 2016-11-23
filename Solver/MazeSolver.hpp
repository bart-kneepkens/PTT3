#ifndef MAZESOLVER_H
#define MAZESOLVER_H

#include "MazeMessage.hpp"

class MazeSolver {
private:
    MazeMessage maze;
    
public:
    void solve(MazeMessage maze);
};
#endif
