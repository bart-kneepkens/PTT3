#include "Module.cpp"
#include "CreateTCPServerSocket.cpp"
#include "AcceptTCPConnection.cpp"
#include <sys/socket.h> // for send() and recv()
#include <iostream>
#include <unistd.h>     // for sleep(), close()
#include <vector>
#include <string>
#include <sstream>
#include <pthread.h>

int servSocket;
std::vector<Module> connectedModules;

Module acceptModule(int clientSocket){
    std::cout << "Accepted client with id: " << clientSocket << std::endl;
    
    char buff[1024];
    
    int received = recv(clientSocket, buff, 1024,0);
    
    
    std::string helloString(buff);
    
    std::cout << "Received: " << helloString << std::endl;
    
    std::vector<std::string> segments;
    std::string segment;
    std::stringstream ss;
    ss.str(helloString);
    
    while(std::getline(ss, segment, ':')){
        segments.push_back(segment);
    }
    
    std::string moduleName = segments.at(2);
    std::string moduleType = segments.at(1);
    
    //close(clientSocket);
    
    std::cout << "returning module : "<< moduleType << ":" << moduleName << ":" << clientSocket << std::endl;
    return Module(moduleType, moduleName, clientSocket);
}

static void * myThread (void * threadArgs){
    int * clntSock_ptr = (int*) threadArgs;
    
    Module m = acceptModule(*clntSock_ptr);
    connectedModules.push_back(m);
    
    pthread_detach(pthread_self());
    return (NULL);
}

void printModules(){
    std::cout << "===================" << std::endl;
    for (size_t i = 0; i < connectedModules.size(); i++) {
        std::cout << connectedModules.at(i).GetName() << ":" << connectedModules.at(i).GetType() << ":" << connectedModules.at(i).GetSocketFD() << std::endl;
    }
    std::cout << "===================" << std::endl;
}

int main(){
    servSocket = CreateTCPServerSocket(1111);
    
    std::cout << "Created server socket with id: " << servSocket << std::endl;
    
    while(connectedModules.size() != 3){
        
        int clientSocket = AcceptTCPConnection(servSocket);
        
        std::cout << "Accepted client: " << clientSocket;
        
        pthread_t threadID;
        
        int result = pthread_create(&threadID, NULL, myThread, &clientSocket);
        
        if(result != 0){
            std::cout << "Error creating thread. Exiting." << result << std::endl;
            return 1;
        }

    }
    
    std::cout << "Has 3 modules!!!! " << std::endl;
    
    printModules();
    
    close(servSocket);
    
    return 0;
}
