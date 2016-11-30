#ifndef SOLVER_MAZESOLVER_H
#define SOLVER_MAZESOLVER_H

#include "../maze_parser/MazeParser.hpp"

namespace maze_solver {

    using std::vector;
    using std::string;

    class MazeSolver {
    private:
        vector<vector<char>*> Maze;
        vector<vector<char>*>*Solution;
        bool solveForCoordinates(int X, int Y);
        /**
         * Generates an empty field (a 2d char vector) with the given number of columns and rows.
         *
         * @param columns
         * @param rows
         * @return
         */
        vector<vector<char>*>* emptyField(unsigned int columns, unsigned int rows);
    public:
        MazeSolver();
        ~MazeSolver();
        void solve(maze_parser::MazeMessage& message);
    };
}
#endif
