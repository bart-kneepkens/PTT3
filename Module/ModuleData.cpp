#include "ModuleData.hpp"

ModuleType::ModuleType ModuleType::fromString(std::string str) {
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

ModuleSubType::ModuleSubType ModuleSubType::fromString(std::string str) {
    if (str == "scanner") {
        return ModuleSubType::SCANNER;
    }
    if (str == "solver") {
        return ModuleSubType::SOLVER;
    }
    if (str == "plotter") {
        return ModuleSubType::PLOTTER;
    }
    throw std::invalid_argument("Could not parse string '" + str + "' to enum 'ModuleSubType'!");
}

ModuleData::ModuleData(ModuleType::ModuleType type, ModuleSubType::ModuleSubType subType, int socketId) : type(type),
                                                                                              subType(subType),
                                                                                              socketId(socketId) {}

ModuleData::~ModuleData() {}

int ModuleData::getSocketId() const {
    return this->socketId;
}

ModuleType::ModuleType ModuleData::getType() const {
    return this->type;
}

ModuleSubType::ModuleSubType ModuleData::getSubType() const {
    return this->subType;
}

