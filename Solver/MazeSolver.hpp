#ifndef SOLVER_MAZESOLVER_H
#define SOLVER_MAZESOLVER_H

#include "MazeMessage.hpp"

namespace maze_solver {
    
    class MazeSolver {
    private:
        MazeMessage maze;
        
    public:
        void solve(MazeMessage maze);
    };
}
#endif
