/**
 * The server to which ModuleClients make themselves known, and from which module chains can be edited and executed.
 */

#include <iostream>
#include <vector>

#include "ModuleHandler.hpp"
#include "ModuleChain.hpp"
#include "../Logger/LoggerCentral.hpp"
#include "../Gpio/LedController.hpp"

/** Module chains created by user. */
std::vector<ModuleChain> moduleChains;

/**
 * Prints all available commands.
 */
void PrintHelp() {
    std::cout << "COMMAND\t\tDESCRIPTION\n";
    std::cout << "delete\t\tDelete an existing module chain. (Aliases: remove.)\n";
    std::cout << "exit\t\tExit the program. (Aliases: close, stop.)\n";
    std::cout << "chains\t\tPrint all available module chains.\n";
    std::cout << "help\t\tPrint this help. (Aliases: ?.)\n";
    std::cout << "modules\t\tPrint all available modules.\n";
    std::cout << "new\t\t\tCreate a new module chain. (Aliases: create.)\n";
    std::cout << "run\t\t\tRun a module chain. (Aliases: launch, start.)\n";
    std::cout << std::flush;
}

/**
 * Prints the supplied modules.
 * @param modules
 */
void PrintModules(const std::vector<ModuleData> &modules) {
    // If there are no modules, print appropriate info.
    if (modules.size() < 1) {
        std::cout << "No modules available!" << std::endl;
        return;
    }

    std::cout << "SOCKETFD\tMODULE TYPE\n";

    for (unsigned int i = 0; i < modules.size(); i++) {
        const ModuleData module = modules.at(i);
        std::cout << module.GetSocketId() << "\t\t\t" << ModuleType::ToString(module.GetType())
                  << ":" << ModuleSubType::ToString(module.GetSubType()) << "\n";
    }
    std::cout << std::flush;
}

/**
 * Prints all created chains.
 */
void PrintChains() {
    // If there are no chains, print appropriate info.
    if (moduleChains.size() < 1) {
        std::cout << "No module chains available!" << std::endl;
        return;
    }

    for (unsigned int i = 0; i < moduleChains.size(); i++) {
        const ModuleChain chain = moduleChains.at(i);
        std::cout << "INDEX:\t\t" << i << "\n";
        std::cout << "MODULES:\n";
        std::cout << chain.ToString();
    }
    std::cout << std::flush;
}

/**
 * Used by the thread that continuously reads log messages and writes them to a file.
 * @param threadArgs
 * @return
 */
void* LoggerCentralThread(void *threadArgs) {
    LoggerCentral loggerCentral = LoggerCentral();
    loggerCentral.run();
}

int main(int argc, char *argv[]) {
    // If no port was provided, print error and exit.
    if (argc < 2) {
        std::cerr << "Error: no port provided!" << std::endl;
        exit(1);
    }

    // Run logger central.
    pthread_t loggerCentralThread;
    pthread_create(&loggerCentralThread, NULL, LoggerCentralThread, NULL);

    // Get logger.
    Logger &logger = Logger::getInstance();
    logger.logMessage("Launching server...");

    // Setup and start ModuleHandler.
    ModuleHandler moduleHandler = ModuleHandler(atoi(argv[1]));
    if (!moduleHandler.StartListening()) {
        logger.logMessage("Failed to start ModuleHandler instance!");
        exit(1);
    }
    bool running = true;
    moduleChains = std::vector<ModuleChain>();

    // Turn on the arduino light.
    LedController::getInstance().turnLed(true);

    // Before we start looping for user input, print the available commands.
    PrintHelp();

    // Loop for user input until exiting.
    while (running) {
        std::string input;
        std::cin >> input;
        std::cin.ignore();

        if (input == "delete" || input == "remove") {
            // Delete an existing module chain.
            // Prompt user what module chain to delete, by index.
            std::cout << "Delete module chain at index:" << std::endl;
            unsigned int index;
            std::cin >> index;
            std::cin.ignore();

            // If index is within range, delete the chain at the supplied index.
            if (index < moduleChains.size()) {
                moduleChains.erase(moduleChains.begin() + index);
                logger.logMessage("Removed module chain.");
            }
            else {
                std::cout << "Index is out of range!" << std::endl;
            }
        }
        else if (input == "exit" || input == "close" || input == "stop") {
            // Prepare to exit program.
            running = false;
            logger.logMessage("Shutting down server...");
        }
        else if (input == "chains") {
            // Print available module chains.
            PrintChains();
        }
        else if (input == "help" || input == "?") {
            // Print available commands.
            PrintHelp();
        }
        else if (input == "modules") {
            // Print all modules.
            PrintModules(moduleHandler.GetModules());
        }
        else if (input == "new" || input == "create") {
            // Create a new module chain.
            // Prompt user what modules to add to the chain.
            std::cout << "Modules to add by sockfd (example: '4 2 13 6'):" << std::endl;
            std::string sockfdsStr;
            std::getline(std::cin, sockfdsStr);

            // Prepare new ModuleChain.
            ModuleChain newChain = ModuleChain();

            // Split string on spaces, then convert parts to integers.
            std::vector<std::string> strParts = splitString(sockfdsStr, ' ');
            for (unsigned int i = 0; i < strParts.size(); i++) {
                int sockfd = stoi(strParts[i]);
                ModuleData moduleData = moduleHandler.GetModule(sockfd);
                newChain.AppendModule(moduleData);
            }

            // Add new module chain to vector.
            moduleChains.push_back(newChain);
            logger.logMessage("Added new module chain.");
        }
        else if (input == "run" || input == "launch" || input == "start") {
            // Run a module chain.
            // Prompt user what module chain to run, by index.
            std::cout << "Run module chain at index:" << std::endl;
            unsigned int index;
            std::cin >> index;
            std::cin.ignore();

            // If index is within range, run the chain at the supplied index.
            if (index < moduleChains.size()) {
                logger.logMessage("Running module chain...");
                moduleChains.at(index).Run();
            }
            else {
                std::cout << "Index is out of range!" << std::endl;
            }
        }
        else {
            // Print 'command not recognized' message.
            std::cout << "Command not recognized. Type 'help' or '?' for available commands." << std::endl;
        }
    }

    // Close the ModuleHandler.
    moduleHandler.StopListening();

    // Turn off the arduino light.
    LedController::getInstance().turnLed(false);
}