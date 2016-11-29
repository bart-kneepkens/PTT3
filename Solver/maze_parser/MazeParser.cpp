#include "MazeParser.hpp"

// Implementations of InvalidMazeException.

maze_parser::InvalidMazeException::InvalidMazeException(string errorMsg) : errorMsg(errorMsg) {}

const char *maze_parser::InvalidMazeException::what() const throw() {
    return errorMsg.c_str();
}


// Implementations of InvalidSolutionException.

maze_parser::InvalidSolutionException::InvalidSolutionException(string errorMsg) : errorMsg(errorMsg) {}

const char *maze_parser::InvalidSolutionException::what() const throw() {
    return errorMsg.c_str();
}


// Implementations of functions in anonymous namespace.

namespace maze_parser {
namespace {

    vector<vector<string>*> * json2dArrayTo2dStringVector(json &json2dArray) {

        vector<vector<string>*> * field = new vector<vector<string>*>();

        for (json::iterator it = json2dArray.begin(); it != json2dArray.end(); ++it) {

            nlohmann::json itval = it.value();
            vector<string> * row = new vector<string>();
            field->push_back(row);

            for (json::iterator it2 = itval.begin(); it2 != itval.end(); ++it2) {
                row->push_back(*it2);
            }
        }

        return field;
    }
}}


// Implementations of global functions.

void maze_parser::validateMaze(vector<vector<string>*> *maze) {

    // Ensure the maze is not null.
    if (maze == 0)
        throw InvalidMazeException("Supplied maze is null");

    // Ensure the maze is not empty.
    if (maze->size() < 1)
        throw InvalidMazeException("Supplied maze is empty");

    const int width = maze[0].size();

    // Ensure the maze's first row is not empty.
    if (width < 1)
        throw InvalidMazeException("Supplied maze's first row is empty");

    // Ensure the length of each row is equal and also ensure
    // each int value is in the MazeBlockType enum.
    for (auto const &row : *maze) {

        // Ensure the length of each row is equal.
        if (row->size() != width)
            throw InvalidMazeException("Supplied maze has unequal row lengths");

        // Ensure each int value is in the MazeBlockType enum.
        for (auto const &block : *row) {
            if (block != EMPTY && block != WALL) {
                throw InvalidMazeException("Supplied maze contains invalid value: " + block);
            }
        }
    }
}

void maze_parser::validateSolution(vector<vector<string>*> *solution) {

    // Ensure the solution is not null.
    if (solution == 0)
        throw InvalidSolutionException("Supplied solution is null");

    // Ensure the solution is not empty.
    if (solution->size() < 1)
        throw InvalidSolutionException("Supplied solution is empty");

    const int width = solution[0].size();

    // Ensure the solution's first row is not empty.
    if (width < 1)
        throw InvalidSolutionException("Supplied solution's first row is empty");

    // Ensure the length of each row is equal and also ensure
    // each int value is in the SolutionBlockType enum.
    for (auto const &row : *solution) {

        // Ensure the length of each row is equal.
        if (row->size() != width)
            throw InvalidSolutionException("Supplied solution has unequal row lengths");

        // Ensure each int value is in the SolutionBlockType enum.
        for (auto const &block : *row) {
            if (block != EMPTY && block != PATH) {
                throw InvalidSolutionException(
                        "Supplied solution contains invalid value: " + block);
            }
        }
    }
}

std::string maze_parser::mazeMessageToJson(MazeMessage &mazeMessage, bool validateMaze, bool validateSolution) {

    // Validate the maze if specified.
    if (validateMaze) {
        maze_parser::validateMaze(mazeMessage.Maze);
    }

    // Validate the solution if specified.
    if (validateSolution) {
        maze_parser::validateSolution(mazeMessage.Solution);
    }

    // Create JSON and return its string dump.
    json mazeMsgJson;

    if (mazeMessage.Maze != 0) {

        json mazeJson;

        for (vector<string> * row : *mazeMessage.Maze) {
            mazeJson.push_back(*row);
        }
        mazeMsgJson[MAZE_JSON_KEY] = mazeJson;
    }

    if (mazeMessage.Solution != 0) {
        json solutionJson;

        for (vector<string> * row : *mazeMessage.Solution) {
            solutionJson.push_back(*row);
        }
        mazeMsgJson[SOLUTION_JSON_KEY] = solutionJson;
    }

    return mazeMsgJson.dump(0);
}

maze_parser::MazeMessage * maze_parser::jsonToMazeMessage(std::string json, bool validateMaze, bool validateSolution) {

    nlohmann::json fromJson = json::parse(json);
    nlohmann::json maze = fromJson[MAZE_JSON_KEY];
    nlohmann::json solution = fromJson[SOLUTION_JSON_KEY];
    vector<vector<string>*> *mazeVec = 0;
    vector<vector<string>*> *solutionVec = 0;

    if (maze != 0) {
        mazeVec = json2dArrayTo2dStringVector(maze);
    }

    if (solution != 0) {
        solutionVec = json2dArrayTo2dStringVector(solution);
    }

    // Validate the maze if specified.
    if (validateMaze) {
        maze_parser::validateMaze(mazeVec);
    }

    // Validate the solution if specified.
    if (validateSolution) {
        maze_parser::validateSolution(solutionVec);
    }

    return new MazeMessage(mazeVec, solutionVec);
}

