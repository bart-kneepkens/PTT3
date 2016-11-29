#include <iostream>
#include <unistd.h>
#include <fstream>

#include "MazeSolver.hpp"
#include "MazeParser.hpp"

using namespace maze_solver;    // Forgive me Father for I have sinned.
using std::vector;

/*vector<vector<char> > * mock_maze = new vector<vector<char> >({
    {'#', ' ', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', ' ', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#'},
    {'#', '#' ,'#' ,'#' ,'#' ,'#' ,'#' ,' ', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', ' ', '#'}
});*/

vector<vector<std::string> *> *mock_maze = new vector<vector<std::string> *>({
                                                                                     new vector<std::string>{"#", " ",
                                                                                                             "#", "#",
                                                                                                             "#", "#",
                                                                                                             "#", "#",
                                                                                                             "#", "#"},
                                                                                     new vector<std::string>{"#", " ",
                                                                                                             "#", "#",
                                                                                                             "#", "#",
                                                                                                             "#", "#",
                                                                                                             "#", "#"},
                                                                                     new vector<std::string>{"#", " ",
                                                                                                             " ", " ",
                                                                                                             " ", " ",
                                                                                                             " ", " ",
                                                                                                             "#", "#"},
                                                                                     new vector<std::string>{"#", "#",
                                                                                                             "#", "#",
                                                                                                             "#", "#",
                                                                                                             "#", " ",
                                                                                                             " ", "#"},
                                                                                     new vector<std::string>{"#", " ",
                                                                                                             " ", " ",
                                                                                                             " ", " ",
                                                                                                             " ", "#",
                                                                                                             " ", "#"},
                                                                                     new vector<std::string>{"#", " ",
                                                                                                             " ", " ",
                                                                                                             " ", " ",
                                                                                                             " ", "#",
                                                                                                             " ", "#"},
                                                                                     new vector<std::string>{"#", " ",
                                                                                                             " ", " ",
                                                                                                             " ", " ",
                                                                                                             " ", "#",
                                                                                                             " ", "#"},
                                                                                     new vector<std::string>{"#", " ",
                                                                                                             " ", " ",
                                                                                                             " ", " ",
                                                                                                             " ", "#",
                                                                                                             " ", "#"},
                                                                                     new vector<std::string>{"#", " ",
                                                                                                             " ", " ",
                                                                                                             " ", " ",
                                                                                                             " ", "#",
                                                                                                             " ", "#"},
                                                                                     new vector<std::string>{"#", "#",
                                                                                                             "#", "#",
                                                                                                             "#", "#",
                                                                                                             "#", "#",
                                                                                                             " ",
                                                                                                             "#"}});

vector<vector<std::string> *> *mock_solution = new vector<vector<std::string> *>({
                                                                                         new vector<std::string>{"*",
                                                                                                                 " ",
                                                                                                                 "*",
                                                                                                                 "*",
                                                                                                                 "*",
                                                                                                                 "*",
                                                                                                                 "*",
                                                                                                                 "*",
                                                                                                                 "*",
                                                                                                                 "*"},
                                                                                         new vector<std::string>{"*",
                                                                                                                 " ",
                                                                                                                 "*",
                                                                                                                 "*",
                                                                                                                 "*",
                                                                                                                 "*",
                                                                                                                 "*",
                                                                                                                 "*",
                                                                                                                 "*",
                                                                                                                 "*"},
                                                                                         new vector<std::string>{"*",
                                                                                                                 " ",
                                                                                                                 " ",
                                                                                                                 " ",
                                                                                                                 " ",
                                                                                                                 " ",
                                                                                                                 " ",
                                                                                                                 " ",
                                                                                                                 "*",
                                                                                                                 "*"},
                                                                                         new vector<std::string>{"*",
                                                                                                                 "*",
                                                                                                                 "*",
                                                                                                                 "*",
                                                                                                                 "*",
                                                                                                                 "*",
                                                                                                                 "*",
                                                                                                                 " ",
                                                                                                                 " ",
                                                                                                                 "*"},
                                                                                         new vector<std::string>{"*",
                                                                                                                 " ",
                                                                                                                 " ",
                                                                                                                 " ",
                                                                                                                 " ",
                                                                                                                 " ",
                                                                                                                 " ",
                                                                                                                 "*",
                                                                                                                 " ",
                                                                                                                 "*"},
                                                                                         new vector<std::string>{"*",
                                                                                                                 " ",
                                                                                                                 " ",
                                                                                                                 " ",
                                                                                                                 " ",
                                                                                                                 " ",
                                                                                                                 " ",
                                                                                                                 "*",
                                                                                                                 " ",
                                                                                                                 "*"},
                                                                                         new vector<std::string>{"*",
                                                                                                                 " ",
                                                                                                                 " ",
                                                                                                                 " ",
                                                                                                                 " ",
                                                                                                                 " ",
                                                                                                                 " ",
                                                                                                                 "*",
                                                                                                                 " ",
                                                                                                                 "*"},
                                                                                         new vector<std::string>{"*",
                                                                                                                 " ",
                                                                                                                 " ",
                                                                                                                 " ",
                                                                                                                 " ",
                                                                                                                 " ",
                                                                                                                 " ",
                                                                                                                 "*",
                                                                                                                 " ",
                                                                                                                 "*"},
                                                                                         new vector<std::string>{"*",
                                                                                                                 " ",
                                                                                                                 " ",
                                                                                                                 " ",
                                                                                                                 " ",
                                                                                                                 " ",
                                                                                                                 " ",
                                                                                                                 "*",
                                                                                                                 " ",
                                                                                                                 "*"},
                                                                                         new vector<std::string>{"*",
                                                                                                                 "*",
                                                                                                                 "*",
                                                                                                                 "*",
                                                                                                                 "*",
                                                                                                                 "*",
                                                                                                                 "*",
                                                                                                                 "*",
                                                                                                                 " ",
                                                                                                                 "*"}});

MazeMessage *msg = new MazeMessage(mock_maze, mock_solution);

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

    MazeMessage *msgFromJson = maze_solver::jsonToMazeMessage(jsonStringValue, true, false);
    std::cout << msgFromJson->toString() << std::endl;
    return 0;
}

