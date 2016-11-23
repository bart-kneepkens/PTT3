#include <iostream>
#include "MazeParser.hpp"

using std::vector;

int main() {
    vector<vector<char>> *maze = new vector<vector<char>> ({
            {1, 1, 0, 1, 1, 1},
            {1, 0, 0, 0, 0, 1},
            {1, 1, 0, 1, 0, 1},
            {1, 0, 0, 0, 1, 1},
            {1, 0, 1, 0, 0, 1},
            {1, 1, 1, 0, 1, 1}});

    vector<vector<char>> *solution = new vector<vector<char>> ({
           {0, 0, 1, 0, 0, 0},
           {0, 0, 1, 0, 0, 0},
           {0, 0, 1, 0, 0, 0},
           {0, 0, 1, 1, 0, 0},
           {0, 0, 0, 1, 0, 0},
           {0, 0, 0, 1, 0, 0}});

    maze_solver::MazeMessage message = maze_solver::MazeMessage(maze, solution);
    std::string asJson = maze_solver::mazeMessageToJson(message, true);

    maze_solver::MazeMessage* message2 = maze_solver::jsonToMazeMessage(asJson, false);
    std::string asJson2 = maze_solver::mazeMessageToJson(*message2, true);

    std::cout << asJson2 << std::endl;

    return 0;
}

