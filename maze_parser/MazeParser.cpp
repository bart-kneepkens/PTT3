#include "MazeParser.hpp"

// Implementations of InvalidMazeException.

maze_parser::InvalidMazeException::InvalidMazeException(std::string errorMsg) : errorMsg(errorMsg) {}

const char *maze_parser::InvalidMazeException::what() const throw() {
    return errorMsg.c_str();
}


// Implementations of InvalidSolutionException.

maze_parser::InvalidSolutionException::InvalidSolutionException(std::string errorMsg) : errorMsg(errorMsg) {}

const char *maze_parser::InvalidSolutionException::what() const throw() {
    return errorMsg.c_str();
}


// Implementations of functions in anonymous namespace.

namespace maze_parser {
namespace {

    vector<vector<char>*> * json2dArrayTo2dStringVector(json &json2dArray) {

        vector<vector<char>*> * field = new vector<vector<char>*>();

        for (json::iterator it = json2dArray.begin(); it != json2dArray.end(); ++it) {

            nlohmann::json itval = it.value();
            vector<char> * row = new vector<char>();
            field->push_back(row);

            for (json::iterator it2 = itval.begin(); it2 != itval.end(); ++it2) {
                std::string tmp = *it2;
                row->push_back(tmp[0]);
            }
        }

        return field;
    }
}}


// Implementations of global functions.

void maze_parser::validateMaze(vector<vector<char>*> *maze) {

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

void maze_parser::validateSolution(vector<vector<char>*> *solution) {

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

        for (vector<char> * row : *mazeMessage.Maze) {
            json rowJson;

            for (char block : *row) {
                rowJson.push_back(std::string(1, block));
            }
            mazeJson.push_back(rowJson);
        }
        mazeMsgJson[MAZE_JSON_KEY] = mazeJson;
    }

    if (mazeMessage.Solution != 0) {
        json solutionJson;

        for (vector<char> * row : *mazeMessage.Solution) {
            json rowJson;

            for (char block : *row) {
                rowJson.push_back(std::string(1, block));
            }
            solutionJson.push_back(rowJson);
        }
        mazeMsgJson[SOLUTION_JSON_KEY] = solutionJson;
    }

    return mazeMsgJson.dump(0);
}

maze_parser::MazeMessage * maze_parser::jsonToMazeMessage(std::string json, bool validateMaze, bool validateSolution) {

    nlohmann::json fromJson = json::parse(json);
    nlohmann::json maze = fromJson[MAZE_JSON_KEY];
    nlohmann::json solution = fromJson[SOLUTION_JSON_KEY];
    vector<vector<char>*> *mazeVec = 0;
    vector<vector<char>*> *solutionVec = 0;

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

