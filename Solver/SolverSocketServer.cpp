#include <netinet/in.h>
#include <iostream>

#include "SocketUtils.hpp"

int main(int argc, char *argv[]) {

    // Startup message.
    std::cout << "Starting up SolverSocketServer..." << std::flush;

    // If no port was provided, print error and exit.
    if (argc < 2) {
        fprintf(stderr, "Error: no port provided!\n");
        exit(1);
    }

    // Open up the server-side socket. If it fails, print error and exit.
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error while opening socket!");
        exit(1);
    }

    // Bind the socket to the port.
    sockaddr_in serv_addr;
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    const int port = atoi(argv[1]);
    serv_addr.sin_port = htons(port);

    // If binding failed, throw an error and exit.
    if (bind(sockfd, (sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error while binding socket to port!");
        close(sockfd);
        exit(1);
    }

    // Now start listening to the socket.
    listen(sockfd, 5);
    sockaddr_in cli_addr;
    socklen_t clilen = sizeof(cli_addr);
    std::cout << "Done! Now listening on port " << port << "." << std::endl;

    // Outer loop, each iteration handling a single accepted incoming connection.
    //while (1) {

        // Accept incoming connection. If it failed, print error.
        const int newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        std::cout << "Accepting new connection!" << std::endl;
        if (newsockfd < 0) {
            perror("Error while accepting!");
            exit(1);
        }

    char buffer[256];
    int n = receiveMsg(newsockfd, buffer, 256);
    printf("Here is the message: %s\n",buffer);

    bzero(buffer, 256);
    buffer[0] = 'A';
    buffer[1] = 'C';
    buffer[2] = 'K';
    n = sendMsg(newsockfd, buffer);
    std::cout << "Replied to client." << std::endl;

    close(newsockfd);
    close(sockfd);
    std::cout << "Closed connection." << std::endl;
}