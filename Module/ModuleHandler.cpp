#include "ModuleHandler.hpp"

static void* ModuleHandler::ListenToIncomingModules(void *threadArgs) {
    while (pthread_mutex_trylock(&isListening) != 0) {
        // TODO: code
        std::cout << "diiiicks" << std::endl;
    }
    pthread_mutex_unlock(&isListening);
}

ModuleHandler::ModuleHandler(const int serverPort) : serverPort(serverPort) {}

ModuleHandler::~ModuleHandler() {
    StopListening();
}

std::vector<ModuleData> ModuleHandler::GetModules() {
    pthread_mutex_lock(&modulesMutex);
    std::vector<ModuleData> temp = modules;
    pthread_mutex_unlock(&modulesMutex);
    return temp;
}

bool ModuleHandler::StartListening() {
    if (pthread_mutex_trylock(&isListening) == 0) {
        pthread_create(&listeningThread, NULL, ListenToIncomingModules, NULL);
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



