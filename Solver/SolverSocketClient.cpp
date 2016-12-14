#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>

namespace {
    const uint16_t BUFFER_SIZE = 256;
    const char DELIMITER = '^';
}

int main(int argc, char *argv[])
{
    // Startup message.
    std::cout << "Starting up SolverSocketClient... " << std::flush;

    // If no port was provided, print error and exit.
    if (argc < 3) {
        std::cerr << "Error: not enough arguments provided!" << std::endl;
        exit(1);
    }

    // Open up the server-side socket. If it fails, print error and exit.
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error while opening socket!" << std::endl;
        exit(1);
    }

    // Check if server exists. If not, throw warning and exit.
    const hostent *server = gethostbyname(argv[1]);
    if (server == NULL) {
        std::cerr << "Error: server not found!" << std::endl;
        close(sockfd);
        exit(1);
    }

    // Bind the socket to the port.
    const uint16_t port = atoi(argv[2]);
    sockaddr_in serv_addr;
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy(server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(port);

    // Connect to the server.
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
        std::cerr << "Error while connecting to server!" << std::endl;
    }

    std::cout << "Done!" << std::endl;

    // Get test message in buffer.
    while (1) {
        printf("Please enter the message: ");
        char buffer[BUFFER_SIZE];
        bzero(buffer, BUFFER_SIZE);                     // Set all values in buffer to zero.
        fgets(buffer, BUFFER_SIZE - 1, stdin);          // Load user input into buffer.
        buffer[strcspn(buffer, "\r\n")] = 0;            // Remove newlines from buffer.
        int n = write(sockfd, buffer, strlen(buffer));  // Write buffer to server socket.

        if (n < 0) {
            std::cerr << "Error while writing to socket!" << std::endl;
        }

        // Get reply from server.
        /*bzero(buffer, BUFFER_SIZE);
        n = read(sockfd, buffer, BUFFER_SIZE - 1);
        if (n < 0) {
            std::cerr << "Error reading from socket" << std::endl;
        }

        printf("%s\n", buffer);*/
    }
}