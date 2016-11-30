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
        bool solveForCoordinates(unsigned int X, unsigned int Y);
        /**
         * Generates an empty field (a 2d char vector) with the given number of columns and rows.
         *
         * @param columns
         * @param rows
         * @return
         */
        vector<vector<char>*>* emptyField(unsigned int columns, unsigned int rows);
        /**
         * Checks whether the specified block can be travelled to, and if so, travels to it
         * by calling solveForCoordinates with the supplied coordinates.
         *
         * @param X
         * @param Y
         * @return
         */
        bool exploreBlock(unsigned int X, unsigned int Y);
    public:
        MazeSolver();
        ~MazeSolver();
        void solve(maze_parser::MazeMessage& message);
    };
}
#endif
