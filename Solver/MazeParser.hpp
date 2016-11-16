#ifndef SOLVER_MAZEPARSER_HPP
#define SOLVER_MAZEPARSER_HPP

#include "json.hpp"

/**
 * Contains the code necessary to parse mazes and solutions (both 2-dimensional int vectors) to and from json.
 */
namespace maze_parser {

    // Using statements within the namespace to hide them from outside.
    using nlohmann::json;
    using std::vector;

    // Static constants containing our standard json key names.
    static const std::string MAZE_JSON_KEY = "maze";
    static const std::string SOLUTION_JSON_KEY = "solution";
    
    /**
     * Enum for maze block types with corresponding int values. If a maze contains
     * int values that are not in this enum, then the maze is invalid.
     */
    namespace MazeBlockType {
        enum MazeBlockType {
            EMPTY = 0,
            WALL = 1
        };
    }

    /**
     * Enum for solution block types with corresponding int values. If a solution contains
     * int values that are not in this enum, then the solution is invalid.
     */
    namespace SolutionBlockType {
        enum SolutionBlockType {
            EMPTY = 0,
            PATH = 1
        };
    }

    /**
     * Exception thrown when attempting to parse an invalid maze to json
     * or when a maze parsed from json is invalid.
     */
    class InvalidMazeException : public std::exception {
    public:
        InvalidMazeException(std::string errorMsg) : errorMsg(errorMsg) {}

        const char *what() const throw() { return errorMsg.c_str(); }

    private:
        const std::string errorMsg;
    };

    /**
     * Exception thrown when attempting to parse an invalid solution to json
     * or when a solution parsed from json is invalid.
     */
    class InvalidSolutionException : public std::exception {
    public:
        InvalidSolutionException(std::string errorMsg) : errorMsg(errorMsg) {}

        const char *what() const throw() { return errorMsg.c_str(); }

    private:
        const std::string errorMsg;
    };

    /**
     * Checks the validity of a maze.
     *
     * A maze is valid if it satisfies the following requirements:
     * - It is not empty;
     * - Its first row is not empty;
     * - All rows have the same length as the first row;
     * - All int values appear in the MazeBlockType enum.
     *
     * @param maze the maze to validate
     * @throws InvalidMazeException if the maze is invalid
     */
    void validateMaze(vector<vector<int>> &maze) {

        // Ensure the maze is not empty.
        if (maze.size() < 1)
            throw InvalidMazeException("Supplied maze is empty");

        const int width = maze[0].size();

        // Ensure the maze's first row is not empty.
        if (width < 1)
            throw InvalidMazeException("Supplied maze's first row is empty");

        // Ensure the length of each row is equal and also ensure
        // each int value is in the MazeBlockType enum.
        for (auto const &row : maze) {

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

    /**
     * Checks the validity of a solution.
     *
     * A solution is valid if it satisfies the following requirements:
     * - It is not empty;
     * - Its first row is not empty;
     * - All rows have the same length as the first row;
     * - All int values appear in the SolutionBlockType enum.
     *
     * @param solution the solution to validate
     * @throws InvalidSolutionException if the solution is invalid
     */
    void validateSolution(vector<vector<int>> &solution) {

        // Ensure the solution is not empty.
        if (solution.size() < 1)
            throw InvalidSolutionException("Supplied solution is empty");

        const int width = solution[0].size();

        // Ensure the solution's first row is not empty.
        if (width < 1)
            throw InvalidSolutionException("Supplied solution's first row is empty");

        // Ensure the length of each row is equal and also ensure
        // each int value is in the SolutionBlockType enum.
        for (auto const &row : solution) {

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

    /**
     * Parses the supplied maze to json, optionally validating it.
     *
     * @param maze
     * @param validate whether to validate the maze
     * @return the maze in json format
     * @throws InvalidMazeException if validation is done and the maze is invalid
     */
    json mazeToJson(vector<vector<int>> &maze, bool validate) {

        // Validate if specified.
        if (validate)
            validateMaze(maze);

        // Parse and return json.
        json j_vec(maze);
        return j_vec;
    }

    /**
     * Parses the supplied solution to json, optionally validating it.
     *
     * @param solution
     * @param validate whether to validate the solution
     * @return the solution in json format
     * @throws InvalidSolutionException if validation is done and the solution is invalid
     */
    json solutionToJson(vector<vector<int>> &solution, bool validate) {

        // Validate if specified.
        if (validate)
            validateSolution(solution);

        // Parse and return json.
        json j_vec(solution);
        return j_vec;
    }

    /**
     * Parses the supplied maze and solution to json, optionally validating them.
     *
     * @param maze
     * @param solution
     * @param validate whether to validate the maze and the solution
     * @return the maze and solution in json format
     * @throws InvalidMazeException if validation is done and the maze is invalid
     * @throws InvalidSolutionException if validation is done and the solution is invalid
     */
    json allToJson(vector<vector<int>> &maze, vector<vector<int>> &solution, bool validate) {
        json all;
        all[MAZE_JSON_KEY] = mazeToJson(maze, validate);
        all[SOLUTION_JSON_KEY] = solutionToJson(solution, validate);
        return all;
    }
}

#endif //SOLVER_MAZEPARSER_HPP
