#include "ModuleChain.hpp"

ModuleChain::ModuleChain() {
    modules = std::vector<ModuleData>();
}

std::string ModuleChain::ToString() const {
    std::stringstream stream;
    stream << "SOCKETFD\tMODULE TYPE\n";

    for (unsigned int i = 0; i < modules.size(); i++) {
        const ModuleData module = modules.at(i);
        stream << module.GetSocketId() << "\t\t\t" << ModuleType::ToString(module.GetType())
                  << ":" << ModuleSubType::ToString(module.GetSubType()) << "\n";
    }
    return stream.str();
}

void ModuleChain::AppendModule(ModuleData &moduleData) {
    modules.push_back(moduleData);
}

void ModuleChain::Run() const {
    // Instantiate empty MazeMessage to be sent to the first module, and get logger.
    maze_parser::MazeMessage *msgPtr = new maze_parser::MazeMessage();
    Logger &logger = Logger::getInstance();

    // For testing purposes: load scanned maze in msgPtr.
    msgPtr->Scan = new std::vector<std::vector<char>* >();
    for (unsigned int i = 0; i < 10; i++) {
        msgPtr->Scan->push_back(new std::vector<char>());
        for (unsigned int j = 0; j < 10; j++) {
            msgPtr->Scan->back()->push_back(j != 4 ? '#' : ' ');
        }
    }

    try {
        // Loop over the modules, passing the MazeMessage to each consecutive module.
        for (unsigned int i = 0; i < modules.size(); i++) {
            std::stringstream ss;
            ss << "Processing module with socketfd: " << modules.at(i).GetSocketId() << "...";
            logger.logMessage(ss.str());
            modules.at(i).Run(msgPtr);
        }
    } catch (std::exception ex) {
        std::cout << ex.what() << std::endl;
    }

    // For testing purposes, print the end result.
    //std::cout << msgPtr->toString() << std::endl;

    // Delete msgPtr to prevent memory leakage.
    delete msgPtr;
    logger.logMessage("Finished running chain!");
}
