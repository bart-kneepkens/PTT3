#include <iostream>
#include "MazeParser.hpp"

int main() {
    std::vector<std::vector<int>> maze = {
            {1, 1, 0, 1, 1, 1},
            {1, 0, 0, 0, 0, 1},
            {1, 1, 0, 1, 0, 1},
            {1, 0, 0, 0, 1, 1},
            {1, 0, 1, 0, 0, 1},
            {1, 1, 1, 0, 1, 1}};

    const nlohmann::json j = {"maze", maze};
    nlohmann::json::array
    //std::string str = j.dump(4);
    //std::cout << str << std::endl;

    maze_parser::validateMaze(maze);

    return 0;
}

