#include <netdb.h>

#include "../Solver/MazeSolver.hpp"
#include "SocketUtils.hpp"

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
    std::cout << "Connected to server." << std::endl;

    // Send this module's type to the server, exiting if this fails.
    const std::string moduleTypeMsg = "hi:" + moduleType;
    char buffer[moduleTypeMsg.length()];
    strcpy(buffer, moduleTypeMsg.c_str());
    if (sendMsg(sockfd, buffer) < 0) {
        exit(1);
    }
    std::cout << "Sent module type to server." << std::endl;

    // Receive acknowledgement from server, exiting if this fails.
    char ackBuffer[4];
    if (receiveMsg(sockfd, ackBuffer, 4) < 0) {
        exit(1);
    }
    if (strcmp(ackBuffer, ACK_MSG) != 0) {
        std::cerr << "Received something other than ACK from server: '" << ackBuffer << "'!" << std::endl;
        exit(1);
    }
    std::cout << "Received ACK from server." << std::endl;

    // Now wait indefinitely for commands from the server.

    // Close and exit.
    close(sockfd);
    return 0;
}