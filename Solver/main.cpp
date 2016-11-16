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
    //nlohmann::json::array
    //std::string str = j.dump(4);
    //std::cout << str << std::endl;

    std::cout << maze_parser::allToJson(maze, maze, true).dump(2) << std::endl;

    return 0;
}

