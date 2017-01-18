#include "MazeMessage.hpp"

maze_parser::MazeMessage::MazeMessage(vector<vector<char> *> *scan, vector<vector<char> *> *solution) {
    Scan = scan != 0 ? scan : new vector<vector<char> *>();
    Solution = solution != 0 ? solution : new vector<vector<char> *>();
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
    /*std::string toString;

    if (Scan != 0) {
        toString += "Scan: \n\n";

		//for (vector<char> *row : *Scan) {
		for (int r = 0; r < sizeof(*Scan); r++)
		{
			//for (char block : *row) {
			for (int b = 0; b < sizeof(*(*Scan[r])); b++)
			{
				toString += *(*Scan[r])[b];
				toString += " ";
			}
			toString += "\n";
        }
        toString += "\n";
    }

    if (Solution != 0) {
        toString += "Solution: \n\n";

        //for (vector<char> *row : *Solution) {
        for (int r = 0; r < sizeof(*Solution); r++)
        {
			//for (char block : *row) {
			for (int b = 0; b < sizeof(*(*Scan[r])); b++)
				toString += *(*Scan[r])[b];
				toString += " ";
			}
			toString += "\n";
        }
        toString += "\n";
    }

    return toString;*/
    return "";
}
