/**
 * The server to which ModuleClients make themselves known, and from which module chains can be edited and executed.
 */

#include <netinet/in.h>
#include <iostream>
#include <vector>

#include "SocketUtils.hpp"
#include "ModuleData.hpp"
#include "ModuleHandler.hpp"
#include "../maze_parser/MazeParser.hpp"

/** All registered modules. */
std::vector<ModuleData> modules;

int main(int argc, char *argv[]) {

    ModuleHandler mh = ModuleHandler(5);
    mh.StartListening();
    for (unsigned int i = 0; i < 1000000; i++) {
        std::cout << i << std::endl;
    }
    mh.StopListening();
    return 0;

    // If no port was provided, print error and exit.
    if (argc < 2) {
        std::cerr << "Error: no port provided!" << std::endl;
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
    std::cout << "Now listening on port " << port << "." << std::endl;

    // Continuously accept new modules.
    while (1) {
        // Accept incoming connection. If it failed, print error.
        const int newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) {
            perror("Error while accepting new connection!");
            continue;
            //close(sockfd);
            //exit(1);
        }
        std::cout << "Accepted new connection!" << std::endl;

        // Receive module type from client.
        char buffer[16];
        if (receiveMsg(newsockfd, buffer, 16) < 0) {
            perror("Error while receiving module type!");
            close(newsockfd);
            continue;
            //close(sockfd);
            //exit(1);
        }
        std::cout << "Received module type: '" << buffer << "'." << std::endl;

        // Make sure the module type is correct, otherwise kill the connection.
        std::string bufferStr(buffer);
        std::vector<std::string> segments = splitString(bufferStr, ':');
        if (segments.size() < 3) {
            std::cerr << "Received module type is invalid!" << std::endl;
            close(newsockfd);
            continue;
        }

        ModuleType::ModuleType moduleType;
        ModuleSubType::ModuleSubType moduleSubType;

        try {
            moduleType = ModuleType::FromString(segments.at(2));
            moduleSubType = ModuleSubType::FromString(segments.at(3));
        }
        catch (std::exception ex) {
            std::cerr << ex.what() << std::endl;
            close(newsockfd);
            continue;
        }

        ModuleData newModule = ModuleData(moduleType, moduleSubType, newsockfd);

        // Send ACK to client.
        char ACK_MSG_COPY[ACK_BUFFER_SIZE];
        std::copy(ACK_MSG, ACK_MSG + ACK_BUFFER_SIZE, ACK_MSG_COPY);
        if (sendMsg(newsockfd, ACK_MSG_COPY) < 0) {
            perror("Error while sending ACK to client!");
            close(newsockfd);
            continue;
            //close(sockfd);
            //exit(1);
        }
        std::cout << "Sent ACK to client." << std::endl;

        // If everything went well, add the newly registered module to the vector.
        modules.push_back(newModule);
    }

    // Send MazeMessage to client.
    /*const std::string json = "{\n"
            "  \"scan\": [\n"
            "    [\" \", \" \", \" \", \" \", \" \", \" \", \" \", \" \", \" \", \" \"],\n"
            "    [\" \", \" \", \" \", \" \", \" \", \" \", \" \", \" \", \" \", \" \"],\n"
            "    [\" \", \" \", \" \", \" \", \" \", \" \", \" \", \" \", \" \", \" \"],\n"
            "    [\"#\", \"#\", \" \", \"#\", \"#\", \"#\", \"#\", \"#\", \"#\", \"#\"],\n"
            "    [\"#\", \"#\", \" \", \"#\", \"#\", \"#\", \"#\", \" \", \" \", \"#\"],\n"
            "    [\"#\", \"#\", \" \", \" \", \" \", \" \", \" \", \" \", \"#\", \"#\"],\n"
            "    [\"#\", \"#\", \"#\", \"#\", \"#\", \" \", \"#\", \" \", \" \", \"#\"],\n"
            "    [\"#\", \" \", \" \", \"#\", \" \", \"#\", \"#\", \"#\", \" \", \"#\"],\n"
            "    [\"#\", \" \", \"#\", \"#\", \" \", \" \", \" \", \" \", \" \", \"#\"],\n"
            "    [\"#\", \" \", \" \", \" \", \" \", \"#\", \"#\", \"#\", \" \", \"#\"],\n"
            "    [\"#\", \" \", \"#\", \"#\", \" \", \"#\", \"#\", \" \", \" \", \"#\"],\n"
            "    [\"#\", \" \", \" \", \"#\", \" \", \" \", \"#\", \" \", \"#\", \"#\"],\n"
            "    [\"#\", \"#\", \"#\", \"#\", \"#\", \" \", \"#\", \"#\", \"#\", \"#\"],\n"
            "    [\" \", \" \", \" \", \" \", \" \", \" \", \" \", \" \", \" \", \" \"],\n"
            "    [\" \", \" \", \" \", \" \", \" \", \" \", \" \", \" \", \" \", \" \"],\n"
            "    [\" \", \" \", \" \", \" \", \" \", \" \", \" \", \" \", \" \", \" \"]\n"
            "  ]\n"
            "}";
    char jsonBuffer[json.length()];
    strcpy(jsonBuffer, json.c_str());
    if (sendMsg(newsockfd, jsonBuffer) < 0) {
        perror("Error while sending MazeMessage to client!");
        close(sockfd);
        exit(1);
    }
    std::cout << "Sent MazeMessage to client." << std::endl;

    // Get processed MazeMessage back from client.
    char replyBuffer[MAZE_MSG_BUFFER_SIZE];
    if (receiveMsg(newsockfd, replyBuffer, MAZE_MSG_BUFFER_SIZE) < 0) {
        close(sockfd);
        exit(1);
    }
    std::cout << "Received MazeMessage back from client." << std::endl;

    // Convert retrieved MazeMessage to object and print it for debug purposes.
    std::string replyStr(replyBuffer);
    maze_parser::MazeMessage* parsedMsg = maze_parser::jsonToMazeMessage(replyStr);
    std::cout << parsedMsg->toString() << std::endl;

    // Close and clean up.
    close(newsockfd);*/
    close(sockfd);
    std::cout << "Closed connection." << std::endl;
}