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
        throw std::invalid_argument("Could not parse string '" + str + "' to enum 'ModuleSubType'!");
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

