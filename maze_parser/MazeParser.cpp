#include "MazeParser.hpp"


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

std::string maze_parser::mazeMessageToJson(MazeMessage &mazeMessage) {

    // Create JSON and return its string dump.
    json mazeMsgJson;

    if (mazeMessage.Scan != 0) {

        json scanJson;

        for (vector<char> * row : *mazeMessage.Scan) {
            json rowJson;

            for (char block : *row) {
                rowJson.push_back(std::string(1, block));
            }
            scanJson.push_back(rowJson);
        }
        mazeMsgJson[SCAN_JSON_KEY] = scanJson;
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

maze_parser::MazeMessage * maze_parser::jsonToMazeMessage(std::string json) {
    nlohmann::json fromJson = json::parse(json);
    nlohmann::json scan = fromJson[SCAN_JSON_KEY];
    nlohmann::json solution = fromJson[SOLUTION_JSON_KEY];
    vector<vector<char>*> *scanVec = 0;
    vector<vector<char>*> *solutionVec = 0;

    if (scan != 0) {
        scanVec = json2dArrayTo2dStringVector(scan);
    }

    if (solution != 0) {
        solutionVec = json2dArrayTo2dStringVector(solution);
    }

    return new MazeMessage(scanVec, solutionVec);
}

