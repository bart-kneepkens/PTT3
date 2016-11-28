#include "MazeMessage.hpp"

maze_solver::MazeMessage::MazeMessage(vector<vector<string>* > *maze, vector<vector<string>* > *solution) {
    Maze = maze;
    Solution = solution;
}

maze_solver::MazeMessage::~MazeMessage() {

    for (unsigned int i = 0; i < Maze->size(); i++) {
        delete Maze->at(i);
    }
    delete Maze;

    for (unsigned int i = 0; i < Solution->size(); i++) {
        delete Solution->at(i);
    }
    delete Solution;
}
