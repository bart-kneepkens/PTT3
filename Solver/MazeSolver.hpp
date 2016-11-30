#ifndef SOLVER_MAZESOLVER_H
#define SOLVER_MAZESOLVER_H

#include "../maze_parser/MazeMessage.hpp"

namespace maze_solver {

    using std::vector;
    using std::string;

    class MazeSolver {
    private:
        std::vector<std::vector<char>*> Maze;
        std::vector<std::vector<char>*>*Solution;
        bool solveForCoordinates(int X, int Y);
        void printMaze();
        void extractSolution(std::vector<std::vector<char>* >* vector);
    public:
        MazeSolver();
        ~MazeSolver();
        void solve(maze_parser::MazeMessage& message);
    };
}
#endif
