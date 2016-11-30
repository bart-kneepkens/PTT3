#include "MazeSolver.hpp"

namespace maze_solver {

    class COORD {
    public:
        int X;
        int Y;

        COORD(int x = 0, int y = 0) { X = x, Y = y; }

        COORD(const COORD &coord) {
            X = coord.X;
            Y = coord.Y;
        }
    };

    COORD startingPoint;
    COORD endingPoint;

    bool maze_solver::MazeSolver::solveForCoordinates(int X, int Y) {

        //printf("X: %d, Y: %d\n", X, Y);
        Solution->at(Y)->at(X) = maze_parser::PATH;

        // check if reached goal
        if (X == endingPoint.X && Y == endingPoint.Y) {
            return true;
        }

        // Recursively search for the goal
        if (X > 0 && Maze.at(Y)->at(X - 1) == maze_parser::EMPTY && Solution->at(Y)->at(X - 1) == maze_parser::EMPTY &&
            solveForCoordinates(X - 1, Y)) {
            return true;
        }

        if (X < Maze.at(Y)->size() - 1 && Maze.at(Y)->at(X + 1) == maze_parser::EMPTY && Solution->at(Y)->at(X + 1) == maze_parser::EMPTY &&
            solveForCoordinates(X + 1, Y)) {
            return true;
        }

        if (Y > 0 && Maze.at(Y - 1)->at(X) == maze_parser::EMPTY && Solution->at(Y - 1)->at(X) == maze_parser::EMPTY &&
            solveForCoordinates(X, Y - 1)) {
            return true;
        }

        if (Y < Maze.size() - 1 && Maze.at(Y + 1)->at(X) == maze_parser::EMPTY && Solution->at(Y + 1)->at(X) == maze_parser::EMPTY &&
            solveForCoordinates(X, Y + 1)) {
            return true;
        }

        // Otherwise we need to backtrack and find another solution.
        Solution->at(Y)->at(X) = maze_parser::DEADEND;

        return false;
    }

    maze_solver::MazeSolver::MazeSolver() {}

    maze_solver::MazeSolver::~MazeSolver() {}

    void maze_solver::MazeSolver::solve(maze_parser::MazeMessage &message) {

        this->Maze = *message.Maze;
        startingPoint = COORD(-1, -1);
        endingPoint = COORD(-1, -1);
        const vector<char> firstRow = *(Maze.at(0));
        const unsigned int columnLength = Maze.size();
        const unsigned int rowLength = firstRow.size();
        const unsigned int maxYIndex = columnLength - 1;
        const unsigned int maxXIndex = rowLength - 1;

        // Try find an opening in the top wall.
        for (unsigned int x = 0; x < rowLength; x++) {
            const char block = firstRow.at(x);

            if (block == maze_parser::EMPTY) {
                if (startingPoint.X < 0) {
                    startingPoint.X = x;
                    startingPoint.Y = 0;
                } else if (endingPoint.X < 0) {
                    endingPoint.X = x;
                    endingPoint.Y = 0;
                    break;
                }
            }
        }

        // Try find an opening in the left and right walls.
        if (startingPoint.X < 0 || endingPoint.X < 0) {
            for (unsigned int y = 1; y < maxYIndex; y++) {
                char block = Maze.at(y)->at(0);

                if (block == maze_parser::EMPTY) {
                    if (startingPoint.X < 0) {
                        startingPoint.X = 0;
                        startingPoint.Y = y;
                    } else if (endingPoint.X < 0) {
                        endingPoint.X = 0;
                        endingPoint.Y = y;
                        break;
                    }
                }

                block = Maze.at(y)->at(maxYIndex);

                if (block == maze_parser::EMPTY) {
                    if (startingPoint.X < 0) {
                        startingPoint.X = maxXIndex;
                        startingPoint.Y = y;
                    } else if (endingPoint.X < 0) {
                        endingPoint.X = maxXIndex;
                        endingPoint.Y = y;
                        break;
                    }
                }
            }
        }

        // Try find an opening in the bottom wall.
        if (startingPoint.X < 0 || endingPoint.X < 0) {
            const vector<char> lastRow = *(Maze.at(maxYIndex));

            for (unsigned int x = 0; x < rowLength; x++) {
                if (lastRow.at(x) == maze_parser::EMPTY) {
                    if (startingPoint.X < 0) {
                        startingPoint.X = x;
                        startingPoint.Y = maxYIndex;
                    } else if (endingPoint.X < 0) {
                        endingPoint.X = x;
                        endingPoint.Y = maxYIndex;
                        break;
                    }
                }
            }
        }

        //printf("startingPoint.X = %d, startingPoint.Y = %d, endingPoint.X = %d, endingPoint.Y = %d\n",
        //       startingPoint.X, startingPoint.Y, endingPoint.X, endingPoint.Y);

        // If we failed to find two openings, throw an exception.
        if (startingPoint.X < 0 || endingPoint.X < 0) {
            std::cout << "Invalid maze: it should have at least two openings!" << std::endl;
            return;
        }

        // Create empty solution field.
        Solution = emptyField(columnLength, rowLength);

        // Fill solution field with actual solution.
        if (!solveForCoordinates(startingPoint.X, startingPoint.Y)) {
            std::cout << "Failed to find a solution." << std::endl;
        }

        message.Solution = Solution;
    }

    vector<vector<char> *> *maze_solver::MazeSolver::emptyField(unsigned int columns, unsigned int rows) {
        vector<vector<char> *> *field = new std::vector<std::vector<char> *>();

        for (unsigned int y = 0; y < columns; y++) {
            vector<char> *row = new vector<char>();
            field->push_back(row);

            for (unsigned int x = 0; x < rows; x++) {
                row->push_back(maze_parser::EMPTY);
            }
        }

        return field;
    }
}

