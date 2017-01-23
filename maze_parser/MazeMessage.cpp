#include "MazeMessage.hpp"

maze_parser::MazeMessage::MazeMessage(vector<vector<char> *> *scan, vector<vector<char> *> *solution) {
    Scan = scan;
    Solution = solution;
}

maze_parser::MazeMessage::~MazeMessage() {
    if (Scan != 0) {
        while (!Scan->empty()) {
            delete Scan->back();
            Scan->pop_back();
        }
        delete Scan;
    }

    if (Solution != 0) {
        while (!Solution->empty()) {
            delete Solution->back();
            Solution->pop_back();
        }
        delete Solution;
    }
}


std::string maze_parser::MazeMessage::toString() const {
    std::string toString = "Maze:\n\tScan:\n";

    if (Scan != 0) {
	for (unsigned int y = 0; y < Scan->size(); y++) {
		vector<char> *row = Scan->at(y);
		toString += "\t\t";
		for (unsigned int x = 0; x < row->size(); x++) {
			toString += row->at(x);
		}
		toString += "\n";
	}
    } 
    else {
	toString += "NULL\n";
    }

    toString += "\tSolution:\n";

    if (Solution != 0) {
	
	for (unsigned int y = 0; y < Solution->size(); y++) {
		vector<char> *row = Solution->at(y);
		toString += "\t\t";
		for (unsigned int x = 0; x < row->size(); x++) {
			toString += row->at(x);
		}
		toString += "\n";
	}
    } 
    else {
	toString += "NULL\n";
    }

    return toString;
}
