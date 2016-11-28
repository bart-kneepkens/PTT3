#include "MazeParser.hpp"

// Implementations of InvalidMazeException.

maze_solver::InvalidMazeException::InvalidMazeException(std::string errorMsg) : errorMsg(errorMsg) {}

const char *maze_solver::InvalidMazeException::what() const throw() {
    return errorMsg.c_str();
}


// Implementations of InvalidSolutionException.

maze_solver::InvalidSolutionException::InvalidSolutionException(std::string errorMsg) : errorMsg(errorMsg) {}

const char *maze_solver::InvalidSolutionException::what() const throw() {
    return errorMsg.c_str();
}


// Implementations of functions in anonymous namespace.

namespace maze_solver {
namespace {

    std::vector<std::vector<std::string>> * json2dArrayTo2dStringVector(nlohmann::json &json2dArray) {

        std::vector<std::vector<std::string>> * field = new std::vector<std::vector<std::string>>();

        for (json::iterator it = json2dArray.begin(); it != json2dArray.end(); ++it) {

            nlohmann::json itval = it.value();
            std::vector<std::string> row = std::vector<std::string>();
            field->push_back(row);

            for (json::iterator it2 = itval.begin(); it2 != itval.end(); ++it2) {
                row.push_back(*it2);

                //std::cout << *it2 << std::endl;
            }


        }

        std::cout << field->size() << std::endl;

        for (std::vector<std::string> row : *field) {
            for (std::string block : row) {
                std::cout << block << std::endl;
            }
        }

        return field;
    }
}}

// Implementations of global functions.

void maze_solver::validateMaze(vector<vector<string>> *maze) {

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
        if (row.size() != width)
            throw InvalidMazeException("Supplied maze has unequal row lengths");

        // Ensure each int value is in the MazeBlockType enum.
        for (auto const &block : row) {
            if (block != EMPTY && block != WALL) {
                throw InvalidMazeException("Supplied maze contains invalid value: " + block);
            }
        }
    }
}

void maze_solver::validateSolution(vector<vector<string>> *solution) {

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
        if (row.size() != width)
            throw InvalidSolutionException("Supplied solution has unequal row lengths");

        // Ensure each int value is in the SolutionBlockType enum.
        for (auto const &block : row) {
            if (block != EMPTY && block != PATH) {
                throw InvalidSolutionException(
                        "Supplied solution contains invalid value: " + block);
            }
        }
    }
}

std::string maze_solver::mazeMessageToJson(MazeMessage &mazeMessage, bool validateMaze, bool validateSolution) {

    // Validate the maze if specified.
    if (validateMaze) {
        maze_solver::validateMaze(mazeMessage.Maze);
    }

    // Validate the solution if specified.
    if (validateSolution) {
        maze_solver::validateSolution(mazeMessage.Solution);
    }

    // Create JSON and return its string dump.
    json asJson;

    if (mazeMessage.Maze != 0) {
        asJson[MAZE_JSON_KEY] = *mazeMessage.Maze;
    }

    if (mazeMessage.Solution != 0) {
        asJson[SOLUTION_JSON_KEY] = *mazeMessage.Solution;
    }

    return asJson.dump(0);
}

maze_solver::MazeMessage * maze_solver::jsonToMazeMessage(std::string json, bool validateMaze, bool validateSolution) {

    nlohmann::json fromJson = json::parse(json);
    nlohmann::json maze = fromJson[MAZE_JSON_KEY];
    nlohmann::json solution = fromJson[SOLUTION_JSON_KEY];
    vector<vector<string>> *mazeVec = 0;
    vector<vector<string>> *solutionVec = 0;

    if (maze != 0) {
        mazeVec = json2dArrayTo2dStringVector(maze);
    }

    if (solution != 0) {
        solutionVec = json2dArrayTo2dStringVector(solution);
    }

    return new MazeMessage(mazeVec, solutionVec);
}

