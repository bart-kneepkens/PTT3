#include "ModuleData.hpp"

namespace ModuleType {
    ModuleType FromString(std::string str) {
        if (str == "in") {
            return ModuleType::IN;
        }
        if (str == "inout") {
            return ModuleType::INOUT;
        }
        if (str == "out") {
            return ModuleType::OUT;
        }
        throw std::invalid_argument("Could not parse string '" + str + "' to enum 'ModuleType'!");
    }

    std::string ToString(ModuleType moduleType) {
        switch (moduleType) {
            case ModuleType::IN:
                return "in";
            case ModuleType::INOUT:
                return "inout";
            case ModuleType::OUT:
                return "out";
        }
    }
}

namespace ModuleSubType {
    ModuleSubType FromString(std::string str) {
        if (str == "scanner") {
            return ModuleSubType::SCANNER;
        }
        if (str == "solver") {
            return ModuleSubType::SOLVER;
        }
        if (str == "plotter") {
            return ModuleSubType::PLOTTER;
        }
        if (str == "simplemazeprinter") {
            return ModuleSubType::SIMPLEMAZEPRINTER;
        }
        throw std::invalid_argument("Could not parse string '" + str + "' to enum 'ModuleSubType'!");
    }

    std::string ToString(ModuleSubType moduleSubType) {
        switch (moduleSubType) {
            case ModuleSubType::PLOTTER:
                return "plotter";
            case ModuleSubType::SCANNER:
                return "scanner";
            case ModuleSubType::SOLVER:
                return "solver";
            case ModuleSubType::SIMPLEMAZEPRINTER:
                return "simplemazeprinter";
        }
    }
}

ModuleData::ModuleData(ModuleType::ModuleType type, ModuleSubType::ModuleSubType subType, int socketId) : type(type),
                                                                                              subType(subType),
                                                                                              socketId(socketId) {}

ModuleData::~ModuleData() {}

int ModuleData::GetSocketId() const {
    return this->socketId;
}

ModuleType::ModuleType ModuleData::GetType() const {
    return this->type;
}

ModuleSubType::ModuleSubType ModuleData::GetSubType() const {
    return this->subType;
}

void ModuleData::Run(maze_parser::MazeMessage *&msg) const {
    // Get logger.
    Logger &logger = Logger::getInstance();

    // If msg is NULL, instantiate it.
    if (msg == 0) {
        msg = new maze_parser::MazeMessage();
    }

    // Parse the msg to JSON.
    std::string msgAsJson = maze_parser::mazeMessageToJson(*msg);

    // Send the JSON to the remote module.
    char buffer[msgAsJson.length()];
    strcpy(buffer, msgAsJson.c_str());

    // If sending failed, throw an exception.
    if (sendMsg(socketId, buffer) < 0) {
        std::stringstream ss;
        ss << "Failed to send data to module with socketfd '" << socketId << "'!";
        const std::string msg = ss.str();
        logger.logMessage(msg);
        throw std::logic_error(msg);
    }

    // Now read the reply.
    char msgBuffer[MAZE_MSG_BUFFER_SIZE];

    // If reading the reply failed, throw an exception.
    if (receiveMsg(socketId, msgBuffer, MAZE_MSG_BUFFER_SIZE) < 0) {
        std::stringstream ss;
        ss << "Failed to receive data from module with socketfd '" << socketId << "'!";
        const std::string msg = ss.str();
        logger.logMessage(msg);
        throw std::logic_error(msg);
    }

    // Parse the reply to a MazeMessage.
    std::string replyJson(msgBuffer);
    //std::cout << "DATA: " << replyJson << std::endl;
    try {
        delete msg;
        msg = maze_parser::jsonToMazeMessage(replyJson);
    } catch (std::invalid_argument) {
        std::stringstream ss;
        ss << "Failed to parse received data from module with socketfd '" << socketId << "'!";
        const std::string msg = ss.str();
        logger.logMessage(msg);
        throw std::logic_error(msg);
    }
}
