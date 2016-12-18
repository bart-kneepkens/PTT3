#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>

#include "MazeSolver.hpp"

// Constant values and settings.
const uint16_t BUFFER_SIZE = 256;               // Default buffer size.
const uint16_t ACK_BUFFER_SIZE = 100;//4;             // Buffer size for ACK messages.
const char DELIMITER = '^';                     // Delimiter for incoming messages.
const std::string SCANNER_STRING = "scanner";   // String that corresponds to MazeScanner (to be implemented).
const std::string SOLVER_STRING = "solver";     // String that corresponds to MazeSolver.
const std::string PLOTTER_STRING = "plotter";   // String that corresponds to MazePlotter (to be implemented).
const std::string ACK_MSG = "ACK";              // Message that is sent as acknowledgement.

/**
 * Identifies what child class of IModule to return a dynamically allocated instance of, and then does so. Will return
 * NULL if no child of IModule was found that corresponds to the supplied string.
 *
 * Currently only identifies the solver module.
 *
 * @param theString
 * @return A child of IModule, or NULL.
 */
IModule* StringToModule(std::string theString) {

    if (theString == SCANNER_STRING) {
        return NULL;
    }
    if (theString == SOLVER_STRING) {
        return new maze_solver::MazeSolver();
    }
    if (theString == PLOTTER_STRING) {
        return NULL;
    }
    return NULL;
}

/**
 * Three different parameters must be supplied for this main function:
 *
 * 1. The type of module this client will be running as;
 * 2. The name of the server to connect to;
 * 3. The server port to connect through.
 *
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    // If not enough arguments are provided, print error and return.
    if (argc < 4) {
        std::cerr << "Error: not enough arguments provided!" << std::endl;
        exit(1);
    }

    // Pull supplied arguments from array for clarity's sake.
    const std::string moduleType = std::string(argv[1]);
    const char* serverName = argv[2];
    const uint16_t serverPort = atoi(argv[3]);

    // Identify what module we're gonna be running, throwing an error if the supplied module type is invalid.
    IModule* module = StringToModule(moduleType);
    if (module == NULL) {
        std::cerr << "Error: '" << moduleType << "' is not a valid module type!" << std::endl;
        exit(1);
    }
    std::cout << "Setting module type as '" << moduleType << "'." << std::endl;

    // Open up the client-side socket. If it fails, print error and exit.
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error while creating client-side socket!");
        exit(1);
    }
    std::cout << "Created client-side socket." << std::endl;

    // Check if server exists. If not, throw warning and exit.
    const hostent *server = gethostbyname(serverName);
    if (server == NULL) {
        const std::string serverNameStr(serverName);
        const std::string errorMsg = "Error while finding server with hostname '" + serverNameStr + "'!";
        perror(errorMsg.c_str());
        close(sockfd);
        exit(1);
    }
    std::cout << "Found server with hostname '" << serverName << "'." << std::endl;

    // Bind the socket to the port.
    sockaddr_in serv_addr;
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy(server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(serverPort);

    // Connect to the server, throwing an error if it failed.
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
        perror("Error while connecting to server!");
        close(sockfd);
        exit(1);
    }

    // Inform server of this module's type.
    const char* moduleTypeCharPtr = moduleType.c_str();//(moduleType + DELIMITER).c_str();
    if (write(sockfd, moduleTypeCharPtr, strlen(moduleTypeCharPtr)) < 0) {
        perror("Error while informing server of module type!");
        close(sockfd);
        exit(1);
    }
    std::cout << "Sent module type to server." << std::endl;

    // Await acknowledgement from server.
    while (1) {
        char ackBuffer[3];
        bzero(ackBuffer, 3);
        if (read(sockfd, ackBuffer, 3) < 0) {
            perror("Error while awaiting acknowledgement from server!");
            close(sockfd);
            exit(1);
        }

        std::cout << "Server replied with: '" << ackBuffer << "'." << std::endl;
    }

    // Get test message in buffer.
    //while (1) {
        /*printf("Please enter the message: ");
        char buffer[BUFFER_SIZE];
        bzero(buffer, BUFFER_SIZE);                     // Set all values in buffer to zero.
        fgets(buffer, BUFFER_SIZE - 1, stdin);          // Load user input into buffer.
        buffer[strcspn(buffer, "\r\n")] = 0;            // Remove newlines from buffer.
        int n = write(sockfd, buffer, strlen(buffer));  // Write buffer to server socket.

        if (n < 0) {
            std::cerr << "Error while writing to socket!" << std::endl;
        }*/

        // Get reply from server.
        /*bzero(buffer, BUFFER_SIZE);
        n = read(sockfd, buffer, BUFFER_SIZE - 1);
        if (n < 0) {
            std::cerr << "Error reading from socket" << std::endl;
        }

        printf("%s\n", buffer);*/
    //}
}