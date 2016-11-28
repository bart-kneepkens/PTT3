#include "MazeMessage.hpp"

maze_solver::MazeMessage::MazeMessage(vector<vector<string> > *maze, vector<vector<string> > *solution) {
    Maze = maze;
    Solution = solution;
}

maze_solver::MazeMessage::~MazeMessage() {
    delete Maze;
    delete Solution;
}
