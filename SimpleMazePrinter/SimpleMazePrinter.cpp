#include "SimpleMazePrinter.hpp"

SimpleMazePrinter::SimpleMazePrinter() {}

SimpleMazePrinter::~SimpleMazePrinter() {}

int SimpleMazePrinter::Run(maze_parser::MazeMessage** msg) {
    std::string line, text;
    std::ifstream aFile("DemoMaze.json");

    while (std::getline(aFile, line)) {
        text += line;
    }
    aFile.close();

    std::cout << text << std::endl;
    return 0;
}
