#include "MazeParser.hpp"

// Static constants containing our standard json key names.

namespace {
    const std::string MAZE_JSON_KEY = "maze";
    const std::string SOLUTION_JSON_KEY = "solution";
}

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

// Implementations of global functions.

void maze_solver::validateMaze(vector<vector<char>> *maze) {

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
            if (block != MazeBlockType::EMPTY && block != MazeBlockType::WALL) {
                throw InvalidMazeException("Supplied maze contains invalid value: " + std::to_string(block));
            }
        }
    }
}

void maze_solver::validateSolution(vector<vector<char>> *solution) {

    // Ensure the solution is not null.
    if (solution == 0)
        throw InvalidMazeException("Supplied maze is null");

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
            if (block != SolutionBlockType::EMPTY && block != SolutionBlockType::PATH) {
                throw InvalidSolutionException(
                        "Supplied solution contains invalid value: " + std::to_string(block));
            }
        }
    }
}

std::string maze_solver::mazeMessageToJson(MazeMessage &mazeMessage, bool validate) {

    // Validate the MazeMessage's fields.
    if (validate) {
        validateMaze(mazeMessage.Maze);
        validateSolution(mazeMessage.Solution);
    }

    // Create JSON and return its string dump.
    json asJson;
    asJson[MAZE_JSON_KEY] = *mazeMessage.Maze;
    asJson[SOLUTION_JSON_KEY] = *mazeMessage.Solution;
    return asJson.dump(0);
}

maze_solver::MazeMessage* maze_solver::jsonToMazeMessage(std::string json, bool validate) {
    auto fromJson = json::parse(json);
    //std::cout << fromJson.dump(4);
    MazeMessage* msg = new MazeMessage();

    vector<char[]> dicks;

    unsigned dataArraySize = sizeof(fromJson[MAZE_JSON_KEY]) / sizeof(char);


    dicks.insert(dicks.end(), &fromJson[MAZE_JSON_KEY][0], &fromJson[MAZE_JSON_KEY][dataArraySize]);

    std::cout << dicks[0] << std::endl;

    throw "Not yet implemented!";
    return msg;
}

