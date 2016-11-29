#include "MazeMessage.hpp"

maze_parser::MazeMessage::MazeMessage(vector<vector<char>* > *maze, vector<vector<char>* > *solution) {
    Maze = maze;
    Solution = solution;
}

maze_parser::MazeMessage::~MazeMessage() {

    for (unsigned int i = 0; i < Maze->size(); i++) {
        delete Maze->at(i);
    }
    delete Maze;

    for (unsigned int i = 0; i < Solution->size(); i++) {
        delete Solution->at(i);
    }
    delete Solution;
}

std::string maze_parser::MazeMessage::toString() const {
    std::string toString;

    if (Maze != 0) {
        toString += "Maze: \n";

        for (vector<char> * row : *Maze) {
            if (row != 0) {
                for (char block : *row) {
                    toString += block;
                    toString += " ";
                }
                toString += "\n";
            }
        }

        toString += "\n";
    }

    if (Solution != 0) {
        toString += "Solution: \n";

        for (vector<char> * row : *Solution) {
            if (row != 0) {
                for (char block : *row) {
                    toString += block;
                    toString += " ";
                }
                toString += "\n";
            }
        }

        toString += "\n";
    }

    return toString;
}
