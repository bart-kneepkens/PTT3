#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <iostream>

int sockfd;

void closeServerSocket (void)
{
    std::cout << "Shutting down SolverSocketServer... " << std::flush;
    close(sockfd);
    std::cout << "Done!" << std::endl;
}

int main(int argc, char *argv[]) {

    // Startup message.
    std::cout << "Starting up SolverSocketServer..." << std::flush;

    // If no port was provided, print error and exit.
    if (argc < 2) {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }

    // Open up the server-side socket. If it fails, print error and exit.
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    // Make sure sockfd is closed when this program exits.
    atexit(closeServerSocket);

    // Bind the socket to the port.
    sockaddr_in serv_addr;
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(atoi(argv[1]));

    // If binding failed, throw an error and exit.
    if (bind(sockfd, (sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    // Start listening to the socket indefinitely.
    while (1) {
        listen(sockfd, 5);
        sockaddr_in cli_addr;
        socklen_t clilen = sizeof(cli_addr);

        // Accept incoming connection. If it failed, print error.
        const int newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) {
            perror("ERROR on accept");
        }

        // Start reading from incoming connection.
        char buffer[256];
        bzero(buffer, 256);
        int n = read(newsockfd, buffer, 255);

        // If reading failed, print error.
        if (n < 0) {
            perror("ERROR reading from socket");
        }

        // Do stuff with the data we received. For now, just print a simple message.
        printf("Here is the message: %s\n", buffer);

        // Write a reply to the client. If it fails, print an error.
        n = write(newsockfd, "I got your message", 18);
        if (n < 0) {
            perror("ERROR writing to socket");
        }

        // Clean up and close.
        close(newsockfd);
    }
}