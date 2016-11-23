#ifndef SOLVER_MAZEPARSER_HPP
#define SOLVER_MAZEPARSER_HPP

#include "json.hpp"
#include "MazeMessage.hpp"

/**
 * Contains the code necessary to parse mazes and solutions (both 2-dimensional char vectors) to and from json.
 */
namespace maze_solver {

    // Using statements within the namespace to hide them from outside.
    using nlohmann::json;
    using std::vector;

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
     * Exception thrown when validating a maze failed.
     */
    class InvalidMazeException : public std::exception {
    public:
        InvalidMazeException(std::string errorMsg);

        const char *what() const throw();

    private:
        const std::string errorMsg;
    };

    /**
     * Exception thrown when validating a solution failed.
     */
    class InvalidSolutionException : public std::exception {
    public:
        InvalidSolutionException(std::string errorMsg);

        const char *what() const throw();

    private:
        const std::string errorMsg;
    };

    /**
     * Checks the validity of a maze.
     *
     * A maze is valid if it satisfies the following requirements:
     * - It is not null;
     * - It is not empty;
     * - Its first row is not empty;
     * - All rows have the same length as the first row;
     * - All int values appear in the MazeBlockType enum.
     *
     * @param maze the maze to validate
     * @throws InvalidMazeException if the maze is invalid
     */
    void validateMaze(vector<vector<char>> *maze);

    /**
     * Checks the validity of a solution.
     *
     * A solution is valid if it satisfies the following requirements:
     * - It is not null;
     * - It is not empty;
     * - Its first row is not empty;
     * - All rows have the same length as the first row;
     * - All int values appear in the SolutionBlockType enum.
     *
     * @param solution the solution to validate
     * @throws InvalidSolutionException if the solution is invalid
     */
    void validateSolution(vector<vector<char>> *solution);

    /**
     * Parses the supplied MazeMessage to a valid JSON-string, optionally validating it first
     *
     * @param mazeMessage the MazeMessage to parse
     * @param validate whether to validate the MazeMessage
     * @return the MazeMessage in valid JSON-format
     * @throws InvalidMazeException or InvalidSolutionException if validation is done and failed
     */
    std::string mazeMessageToJson(MazeMessage &mazeMessage, bool validate);

    /**
     * Parses the supplied JSON-string to a MazeMessage instance.
     *
     * @param json the JSON to parse
     * @param validate whether to validate the MazeMessage
     * @return a new MazeMessage
     * @throws InvalidMazeException or InvalidSolutionException if validation is done and failed
     */
    MazeMessage* jsonToMazeMessage(std::string json, bool validate);
}

#endif // SOLVER_MAZEPARSER_HPP
