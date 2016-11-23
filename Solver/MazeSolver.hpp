#ifndef SOLVER_MAZESOLVER_H
#define SOLVER_MAZESOLVER_H

#include "MazeMessage.hpp"

namespace maze_solver {
    
    class MazeSolver {
    private:
        std::vector<std::vector<char>> maze;
        bool solveForCoordinates(int X, int Y);
        void printMaze();
        void extractSolution(vector<std::vector<char> >* vector);
    public:
        MazeSolver();
        void solve(MazeMessage* message);
    };
}
#endif
