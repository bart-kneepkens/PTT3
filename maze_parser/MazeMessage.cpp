#include "MazeMessage.hpp"

maze_parser::MazeMessage::MazeMessage(vector < vector < char > * > *scan, vector < vector < char > * > *solution) {
    Scan = scan;
    Solution = solution;
}

maze_parser::MazeMessage::~MazeMessage() {

    for (unsigned int i = 0; i < Scan->size(); i++) {
        delete Scan->at(i);
    }
    delete Scan;

    for (unsigned int i = 0; i < Solution->size(); i++) {
        delete Solution->at(i);
    }
    delete Solution;
}

std::string maze_parser::MazeMessage::toString() const {
    std::string toString;

    if (Scan != 0) {
        toString += "Scan: \n\n";

        for (vector<char> *row : *Scan) {
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
        toString += "Solution: \n\n";

        for (vector<char> *row : *Solution) {
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
