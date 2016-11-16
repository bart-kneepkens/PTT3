#ifndef SOLVER_MAZEPARSER_HPP
#define SOLVER_MAZEPARSER_HPP

#include "json.hpp"

namespace maze_parser {

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
     * Checks the validity of a maze (which is a vector of integer vectors).
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
    void validateMaze(std::vector<std::vector<int>> &maze) {

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
     * Checks the validity of a solution (which is a vector of integer vectors).
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
    void validateSolution(std::vector<std::vector<int>> &solution) {

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

    std::string mazeToJson(std::vector<std::vector<int>> &maze, bool validate) {

        // Validate if specified.
        if (validate)
            validateMaze(maze);

        // Parse and return json.

    }
}

#endif //SOLVER_MAZEPARSER_HPP
