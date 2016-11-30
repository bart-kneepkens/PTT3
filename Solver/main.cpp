#include <iostream>
#include <unistd.h>
#include <fstream>

#include "MazeSolver.hpp"
#include "../maze_parser/MazeParser.hpp"

using std::vector;

const std::string OUTPUT_FILENAME = "output.json";

int main(int argc, char **argv) {

    char *fileValue = NULL;         // The supplied file location.
    char *jsonStringValue = NULL;   // The supplied json-string.
    int c;                          // Index into the arguments.

    // Parse program arguments.
    while ((c = getopt(argc, argv, "f:j:")) != -1) {
        switch (c) {
            case 'f':
                fileValue = optarg;
                break;
            case 'j':
                jsonStringValue = optarg;
                break;
            default:
                return 1;
        }
    }

    // Print warnings for all non-option arguments.
    if (optind < argc) {
        int index;
        for (index = optind; index < argc; index++) {
            fprintf(stderr, "Ignoring non-option argument '%s'...\n", argv[index]);
        }
    }

    // If a file was given, load its contents into jsonStringValue.
    if (fileValue != 0) {
        std::string line, text;
        std::ifstream aFile(fileValue);

        while (std::getline(aFile, line)) {
            text += line;
        }
        aFile.close();
        jsonStringValue = strdup(text.c_str());
    }

    // Otherwise, we go with jsonStringValue's supplied contents. If no contents were supplied, throw an error.
    if (jsonStringValue == 0) {
        fprintf(stderr, "Supply either a json file location ('-f') or a json string ('-j')\n");
        return 1;
    }

    // Parse the json to a MazeMessage object, solve its containing maze, then parse it back to json.
    maze_parser::MazeMessage *msgFromJson = maze_parser::jsonToMazeMessage(jsonStringValue, true, false);
    maze_solver::MazeSolver solver;
    solver.solve(*msgFromJson);
    std::cout << msgFromJson->toString() << std::endl;
    const std::string jsonFromMsg = maze_parser::mazeMessageToJson(*msgFromJson, false, false);

    // Print the output to a new file.
    std::ofstream aFile(OUTPUT_FILENAME);
    aFile << jsonFromMsg;
    aFile.close();

    return 0;
}

