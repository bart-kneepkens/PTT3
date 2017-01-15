#include "ModuleHandler.hpp"

void* ModuleHandler::ListenToIncomingModules(void *threadArgs) {
    // Cast arguments and get logger.
    ModuleHandler *handler = (ModuleHandler*)threadArgs;
    Logger &logger = Logger::getInstance();

    // Open up the server-side socket. If it fails, print error and exit.
    handler->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (handler->sockfd < 0) {
        logger.logMessage("Error while opening socket!");
        exit(1);
    }

    // Bind the socket to the port.
    sockaddr_in serv_addr;
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(handler->port);

    // If binding failed, throw an error and exit.
    if (bind(handler->sockfd, (sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
        logger.logMessage("Error while binding socket to port!");
        close(handler->sockfd);
        exit(1);
    }

    // Start listening to the socket.
    listen(handler->sockfd, 5);
    sockaddr_in cli_addr;
    socklen_t clilen = sizeof(cli_addr);

    // Loop until instructed to stop.
    while (pthread_mutex_trylock(&handler->isListening) != 0) {
        // Accept incoming connection. If it failed, print error.
        const int newsockfd = accept(handler->sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) {
            logger.logMessage("Error while accepting new connection!");
            continue;
        }

        // Receive module type from client.
        char buffer[16];
        if (receiveMsg(newsockfd, buffer, 16) < 0) {
            logger.logMessage("Error while receiving module type!");
            close(newsockfd);
            continue;
        }

        // Make sure the module type is correct, otherwise kill the connection.
        std::string bufferStr(buffer);
        //std::cout << "Received string: '" << bufferStr << "'" << std::endl;
        std::vector<std::string> segments = splitString(bufferStr, ':');
        if (segments.size() < 3) {
            logger.logMessage("Received module type is invalid!");
            close(newsockfd);
            continue;
        }

        ModuleType::ModuleType moduleType;
        ModuleSubType::ModuleSubType moduleSubType;

        try {
            moduleType = ModuleType::FromString(segments.at(1));
            moduleSubType = ModuleSubType::FromString(segments.at(2));
        }
        catch (std::exception ex) {
            logger.logMessage("Failed to translate received string to Module(Sub)Type!");
            close(newsockfd);
            continue;
        }

        ModuleData newModule = ModuleData(moduleType, moduleSubType, newsockfd);

        // Send ACK to client.
        char ACK_MSG_COPY[ACK_BUFFER_SIZE];
        std::copy(ACK_MSG, ACK_MSG + ACK_BUFFER_SIZE, ACK_MSG_COPY);
        if (sendMsg(newsockfd, ACK_MSG_COPY) < 0) {
            logger.logMessage("Error while sending ACK to client!");
            close(newsockfd);
            continue;
        }

        // If everything went well, add the newly registered module to the vector.
        handler->modules.push_back(newModule);
        std::stringstream ss;
        ss << "New module registered with sockedfd: " << newsockfd << ".";
        logger.logMessage(ss.str());
    }

    // Close socket.
    close(handler->sockfd);

    // Clear modules list.
    //pthread_mutex_lock(&handler->modulesMutex);
    handler->modules.clear();
    //pthread_mutex_unlock(&handler->modulesMutex);

    // Unlock isListening.
    pthread_mutex_unlock(&handler->isListening);
}

ModuleHandler::ModuleHandler(const int port) : port(port) {
    // Initialize mutexes.
    pthread_mutex_init(&isListening, NULL);
    //pthread_mutex_init(&modulesMutex, NULL);
}

ModuleHandler::~ModuleHandler() {
    StopListening();
}

std::vector<ModuleData> ModuleHandler::GetModules() {
    //pthread_mutex_lock(&modulesMutex);
    std::vector<ModuleData> temp = modules;
    //pthread_mutex_unlock(&modulesMutex);
    return temp;
}

bool ModuleHandler::StartListening() {
    if (pthread_mutex_trylock(&isListening) == 0) {
        pthread_create(&listeningThread, NULL, ListenToIncomingModules, this);
        return true;
    }
    return false;
}

bool ModuleHandler::StopListening() {
    if (pthread_mutex_trylock(&isListening) != 0) {
        pthread_mutex_unlock(&isListening);
        return true;
    }
    return false;
}

void ModuleHandler::CloseAndRemoveModule(int socketId) {
    //pthread_mutex_lock(&modulesMutex);

    for (unsigned int i = 0; i < modules.size(); i++) {
        const int curSocketId = modules.at(i).GetSocketId();

        if (curSocketId == socketId) {
            close(curSocketId);
            modules.erase(modules.begin() + i);
            return;
        }
    }
    //pthread_mutex_unlock(&modulesMutex);
}

ModuleData ModuleHandler::GetModule(int socketId) {
    //pthread_mutex_lock(&modulesMutex);

    for (unsigned int i = 0; i < modules.size(); i++) {
        const ModuleData moduleData = modules.at(i);

        if (moduleData.GetSocketId() == socketId) {
            return moduleData;
        }
    }
    //pthread_mutex_unlock(&modulesMutex);
}



