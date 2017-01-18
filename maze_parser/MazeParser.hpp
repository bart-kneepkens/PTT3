#ifndef SOLVER_MAZEPARSER_HPP
#define SOLVER_MAZEPARSER_HPP

#include "MazeMessage.hpp"

/**
 * Contains the code necessary to parse mazes and solutions (both 2-dimensional char vectors) to and from json.
 */
namespace maze_parser {

    // Using statements within the namespace to hide them from outside.
    //using nlohmann::json;
    using std::vector;

    // Constants.
    const char EMPTY = ' ';
    const char WALL = '#';
    const char PATH = '*';
    const char DEADEND = '$';

    // Anonymous namespace containing stuff that should be hidden from outsiders.
    namespace {

        // Constants.
        const std::string SCAN_JSON_KEY = "scan";
        const std::string SOLUTION_JSON_KEY = "solution";
    }

    /**
     * Parses the supplied MazeMessage to a valid JSON-string.
     *
     * @param mazeMessage the MazeMessage to parse
     * @param validate whether to validate the MazeMessage
     * @return the MazeMessage in valid JSON-format
     */
    std::string mazeMessageToJson(MazeMessage &mazeMessage);

    /**
     * Parses the supplied JSON-string to a MazeMessage instance.
     *
     * @param json the JSON to parse
     * @param validate whether to validate the MazeMessage
     * @return a new MazeMessage
     */
    MazeMessage *jsonToMazeMessage(std::string json);
}

#endif // SOLVER_MAZEPARSER_HPP
