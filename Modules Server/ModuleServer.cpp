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
    std::cout << "Started listening: " << moduleHandler.StartListening() << std::endl;

    while (1) {
        // Infinite loop for testing.
        sleep(2);
        std::cout << "Connected modules: " << moduleHandler.GetModules().size() << std::endl;
    }
}