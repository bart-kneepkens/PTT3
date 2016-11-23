#include "MazeMessage.hpp"

maze_solver::MazeMessage::MazeMessage(vector<vector<char> > *maze, vector<vector<char> > *solution) {
    Maze = maze;
    Solution = solution;
}

maze_solver::MazeMessage::~MazeMessage() {
    //delete Maze;
    delete Solution;
}
