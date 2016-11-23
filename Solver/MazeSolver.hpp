#ifndef SOLVER_MAZESOLVER_H
#define SOLVER_MAZESOLVER_H

#include "MazeMessage.hpp"

namespace maze_solver {
    
    class MazeSolver {
    private:
        std::vector<std::vector<char>> maze;
        bool solveForCoordinates(int X, int Y);
        void printMaze();
    public:
        MazeSolver();
        void solve(MazeMessage maze_);
    };
}
#endif
