/**
 * The server to which ModuleClients make themselves known, and from which module chains can be edited and executed.
 */

#include <iostream>

#include "ModuleHandler.hpp"

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
 * Prints all registered modules.
 * @param modules
 */
void PrintModules(const std::vector<ModuleData> &modules) {
    std::cout << "SOCKET FD\tMODULE TYPE\n";

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
    std::cout << "This action is currently unsupported!" << std::endl;
}

int main(int argc, char *argv[]) {
    // If no port was provided, print error and exit.
    if (argc < 2) {
        std::cerr << "Error: no port provided!" << std::endl;
        exit(1);
    }

    // Setup and start ModuleHandler.
    ModuleHandler moduleHandler = ModuleHandler(atoi(argv[1]));
    if (!moduleHandler.StartListening()) {
        std::cerr << "Failed to start ModuleHandler instance!" << std::endl;
        exit(1);
    }
    bool running = true;

    // Before we start looping for user input, print the available commands.
    PrintHelp();

    // Loop for user input until exiting.
    while (running) {
        std::string input;
        std::cin >> input;

        if (input == "delete" || input == "remove") {
            // Delete an existing module chain.
            std::cout << "This action is currently unsupported!" << std::endl;
        }
        else if (input == "exit" || input == "close" || input == "stop") {
            // Prepare to exit program.
            running = false;
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
            std::cout << "This action is currently unsupported!" << std::endl;
        }
        else if (input == "run" || input == "launch" || input == "start") {
            // Run a module chain.
            // TEST CODE:
            maze_parser::MazeMessage msg = maze_parser::MazeMessage();
            msg.Scan = new std::vector<std::vector<char> *>();

            // Build test scan.
            for (unsigned int i = 0; i < 10; i++) {
                msg.Scan->push_back(new std::vector<char>());

                for (unsigned int j = 0; j < 10; j++) {
                    msg.Scan->at(i)->push_back((j != 4) ? '#' : ' ');
                }
            }

            maze_parser::MazeMessage *msgPtr = &msg;
            ModuleData moduleData = moduleHandler.GetModules().at(0);
            moduleData.Run(msgPtr);
            std::cout << msgPtr->toString() << std::endl;
        }
        else {
            // Print 'command not recognized' message.
            std::cout << "Command not recognized. Type 'help' or '?' for available commands." << std::endl;
        }
    }

    // Close the ModuleHandler.
    moduleHandler.StopListening();
}