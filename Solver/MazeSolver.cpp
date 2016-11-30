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

    bool maze_solver::MazeSolver::solveForCoordinates(unsigned int X, unsigned int Y) {

        //printf("X: %d, Y: %d\n", X, Y);

        // Set the current block to the right char.
        Solution->at(Y)->at(X) = maze_parser::PATH;

        // Return true if ending point has been reached.
        if (X == endingPoint.X && Y == endingPoint.Y) {
            return true;
        }

        bool foundEndingPoint = false;

        // Travel to all 4 surrounding blocks if possible, starting with the blocks that are closest to the ending point.
        if (Y > endingPoint.Y) {
            if (X > endingPoint.X) {
                // Order: Y-1, X-1, Y+1, X+1
                foundEndingPoint = (exploreBlock(X, Y - 1) || exploreBlock(X - 1, Y) || exploreBlock(X, Y + 1) || exploreBlock(X + 1, Y));
            }
            else if (X < endingPoint.X) {
                // Order: Y-1, X+1, Y+1, X-1
                foundEndingPoint = (exploreBlock(X, Y - 1) || exploreBlock(X + 1, Y) || exploreBlock(X, Y + 1) || exploreBlock(X - 1, Y));
            }
            else {
                // Order: Y-1, X+1, X-1, Y+1
                foundEndingPoint = (exploreBlock(X, Y - 1) || exploreBlock(X + 1, Y) || exploreBlock(X - 1, Y) || exploreBlock(X, Y + 1));
            }
        }
        else if (Y < endingPoint.Y) {
            if (X > endingPoint.X) {
                // Order: Y+1, X-1, Y-1, X+1
                foundEndingPoint = (exploreBlock(X, Y + 1) || exploreBlock(X - 1, Y) || exploreBlock(X, Y - 1) || exploreBlock(X + 1, Y));
            }
            else if (X < endingPoint.X) {
                // Order: Y+1, X+1, Y-1, X-1
                foundEndingPoint = (exploreBlock(X, Y + 1) || exploreBlock(X + 1, Y) || exploreBlock(X, Y - 1) || exploreBlock(X - 1, Y));
            }
            else {
                // Order: Y+1, X+1, X-1, Y-1
                foundEndingPoint = (exploreBlock(X, Y + 1) || exploreBlock(X + 1, Y) || exploreBlock(X - 1, Y) || exploreBlock(X, Y - 1));
            }
        }
        else {
            if (X >= endingPoint.X) {
                // Order: X-1, Y+1, Y-1, X+1
                foundEndingPoint = (exploreBlock(X - 1, Y) || exploreBlock(X, Y + 1) || exploreBlock(X, Y - 1) || exploreBlock(X + 1, Y));
            }
            else if (X < endingPoint.X) {
                // Order: X+1, Y+1, Y-1, X-1
                foundEndingPoint = (exploreBlock(X + 1, Y) || exploreBlock(X, Y + 1) || exploreBlock(X, Y - 1) || exploreBlock(X - 1, Y));
            }
        }

        // If ending point was not found, set current block to be a dead end.
        if (!foundEndingPoint) {
            Solution->at(Y)->at(X) = maze_parser::DEADEND;
        }
        return foundEndingPoint;
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

    bool MazeSolver::exploreBlock(unsigned int X, unsigned int Y) {
        return (Y >= 0 && X >= 0 && Y < Maze.size() && X < Maze.at(Y)->size() &&
                Maze.at(Y)->at(X) == maze_parser::EMPTY && Solution->at(Y)->at(X) == maze_parser::EMPTY &&
                solveForCoordinates(X, Y));
    }
}

