/**
 * The server to which ModuleClients make themselves known, and from which module chains can be edited and executed.
 */

#include <iostream>

#include "ModuleHandler.hpp"

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

    // Loop for user input until exiting.
    while (running) {
        std::string input;
        std::cin >> input;

        if (input == "exit" || input == "stop" || input == "close") {
            // Prepare to exit program.
            running = false;
        }
        else if (input == "chains") {
            // Print available module chains.
            std::cout << "This action is currently unsupported!" << std::endl;
        }
        else if (input == "help" || input == "?") {
            // Print available commands.
            std::cout << "COMMAND\t\tDESCRIPTION\n";
            std::cout << "exit\t\tExits the program. (Aliases: stop, close.)\n";
            std::cout << "chains\t\tPrints all available module chains.\n";
            std::cout << "help\t\tPrints this help. (Aliases: ?.)\n";
            std::cout << "modules\t\tPrints all available modules.\n";
            std::cout << std::flush;
        }
        else if (input == "modules") {
            // Print all modules.
            const std::vector<ModuleData> modules = moduleHandler.GetModules();
            std::cout << "INDEX\tSOCKET FD\tMODULE TYPE\n";
            for (unsigned int i = 0; i < modules.size(); i++) {
                const ModuleData module = modules.at(i);
                std::cout << i << "\t\t" << module.GetSocketId() << "\t\t\t" << ModuleType::ToString(module.GetType())
                          << ":" << ModuleSubType::ToString(module.GetSubType()) << "\n";
            }
            std::cout << std::flush;
        }
    }

    // Close the ModuleHandler.
    moduleHandler.StopListening();
}