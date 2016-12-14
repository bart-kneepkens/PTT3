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

    maze_parser::MazeMessage *MazeSolver::Run(maze_parser::MazeMessage &msg) {
        this->Maze = *(msg.Scan);
        startingPoint = COORD(-1, -1);
        endingPoint = COORD(-1, -1);
        const unsigned int columnLength = Maze.size();
        const unsigned int rowLength = (Maze.at(0))->size();
        const unsigned int maxYIndex = columnLength - 1;
        const unsigned int maxXIndex = rowLength - 1;
        unsigned int yStart = 0;
        bool foundWall = false;

        // Find row with first occurrence of an entrance.
        for (; yStart < columnLength; yStart++) {
            for (unsigned int x = 0; x < rowLength; x++) {
                const char block = Maze.at(yStart)->at(x);

                if (block == maze_parser::WALL) {
                    foundWall = true;
                    std::cout << "Found first wall on position: Y=" << yStart << "; X=" << x << std::endl;
                    break;
                }
            }

            if (foundWall) {
                break;
            }
        }

        // If no walls were found at all, print error message and return.
        if (!foundWall) {
            std::cout << "Invalid maze: it contains no walls!" << std::endl;
            return NULL;
        }

        // Try find an opening in the top wall.
        for (unsigned int x = 0; x < rowLength; x++) {
            const char block = Maze.at(yStart)->at(x);

            if (block == maze_parser::EMPTY) {
                if (startingPoint.X < 0) {
                    startingPoint.X = x;
                    startingPoint.Y = yStart;
                    std::cout << "Set starting point to: Y=" << yStart << "; X=" << x << std::endl;

                } else if (endingPoint.X < 0) {
                    endingPoint.X = x;
                    endingPoint.Y = yStart;
                    std::cout << "Set ending point to: Y=" << yStart << "; X=" << x << std::endl;
                    break;
                }
            }
        }

        // Try find an opening in the left and right walls.
        if (startingPoint.X < 0 || endingPoint.X < 0) {
            for (unsigned int y = yStart + 1; y < maxYIndex; y++) {
                char block = Maze.at(y)->at(0);

                if (block == maze_parser::EMPTY) {
                    if (startingPoint.X < 0) {
                        startingPoint.X = 0;
                        startingPoint.Y = y;
                        std::cout << "Set starting point to: Y=" << y << "; X=" << 0 << std::endl;
                    } else if (endingPoint.X < 0) {
                        endingPoint.X = 0;
                        endingPoint.Y = y;
                        std::cout << "Set ending point to: Y=" << y << "; X=" << 0 << std::endl;
                        break;
                    }
                }

                block = Maze.at(y)->at(maxXIndex);

                if (block == maze_parser::EMPTY) {
                    if (startingPoint.X < 0) {
                        startingPoint.X = maxXIndex;
                        startingPoint.Y = y;
                        std::cout << "Set starting point to: Y=" << y << "; X=" << maxXIndex << std::endl;
                    } else if (endingPoint.X < 0) {
                        endingPoint.X = maxXIndex;
                        endingPoint.Y = y;
                        std::cout << "Set ending point to: Y=" << y << "; X=" << maxXIndex << std::endl;
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
                        std::cout << "Set starting point to: Y=" << maxYIndex << "; X=" << x << std::endl;
                    } else if (endingPoint.X < 0) {
                        endingPoint.X = x;
                        endingPoint.Y = maxYIndex;
                        std::cout << "Set ending point to: Y=" << maxYIndex << "; X=" << x << std::endl;
                        break;
                    }
                }
            }
        }

        // If we failed to find two openings, throw an exception.
        if (startingPoint.X < 0 || endingPoint.X < 0) {
            std::cout << "Invalid maze: it should have at least two openings!" << std::endl;
            return NULL;
        }

        // Create empty solution field.
        Solution = emptyField(columnLength, rowLength);

        // Fill solution field with actual solution.
        if (!solveForCoordinates(startingPoint.X, startingPoint.Y)) {
            std::cout << "Failed to find a solution." << std::endl;
        }

        msg.Solution = Solution;
    }

    bool maze_solver::MazeSolver::solveForCoordinates(unsigned int X, unsigned int Y) {

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
                foundEndingPoint = (exploreBlock(X, Y - 1) || exploreBlock(X - 1, Y) || exploreBlock(X, Y + 1) ||
                                    exploreBlock(X + 1, Y));
            } else if (X < endingPoint.X) {
                // Order: Y-1, X+1, Y+1, X-1
                foundEndingPoint = (exploreBlock(X, Y - 1) || exploreBlock(X + 1, Y) || exploreBlock(X, Y + 1) ||
                                    exploreBlock(X - 1, Y));
            } else {
                // Order: Y-1, X+1, X-1, Y+1
                foundEndingPoint = (exploreBlock(X, Y - 1) || exploreBlock(X + 1, Y) || exploreBlock(X - 1, Y) ||
                                    exploreBlock(X, Y + 1));
            }
        } else if (Y < endingPoint.Y) {
            if (X > endingPoint.X) {
                // Order: Y+1, X-1, Y-1, X+1
                foundEndingPoint = (exploreBlock(X, Y + 1) || exploreBlock(X - 1, Y) || exploreBlock(X, Y - 1) ||
                                    exploreBlock(X + 1, Y));
            } else if (X < endingPoint.X) {
                // Order: Y+1, X+1, Y-1, X-1
                foundEndingPoint = (exploreBlock(X, Y + 1) || exploreBlock(X + 1, Y) || exploreBlock(X, Y - 1) ||
                                    exploreBlock(X - 1, Y));
            } else {
                // Order: Y+1, X+1, X-1, Y-1
                foundEndingPoint = (exploreBlock(X, Y + 1) || exploreBlock(X + 1, Y) || exploreBlock(X - 1, Y) ||
                                    exploreBlock(X, Y - 1));
            }
        } else {
            if (X >= endingPoint.X) {
                // Order: X-1, Y+1, Y-1, X+1
                foundEndingPoint = (exploreBlock(X - 1, Y) || exploreBlock(X, Y + 1) || exploreBlock(X, Y - 1) ||
                                    exploreBlock(X + 1, Y));
            } else if (X < endingPoint.X) {
                // Order: X+1, Y+1, Y-1, X-1
                foundEndingPoint = (exploreBlock(X + 1, Y) || exploreBlock(X, Y + 1) || exploreBlock(X, Y - 1) ||
                                    exploreBlock(X - 1, Y));
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

