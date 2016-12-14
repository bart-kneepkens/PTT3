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

//class Server{
//    
//    int StartSequence(){
//        
//    }
//    
//    int connectModule(){
//        
//    }
//    
//    int runModule(){
//        
//    }
//};

int servSocket;

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
    
    close(clientSocket);
    
    std::cout << "returning module : "<< moduleType << ":" << moduleName << ":" << clientSocket << std::endl;
    return Module(moduleType, moduleName, clientSocket);
}

static void * myThread (void * threadArgs)
{
    int * clntSock_ptr = (int*) threadArgs;
    
    acceptModule(*clntSock_ptr);
    pthread_detach(pthread_self());
    return (NULL);
}

int main(){
    // Wait for modules to send connect message async
    
    // Wait for user to give Start signal async
    
    servSocket = CreateTCPServerSocket(1234);
    
    std::cout << "Created server socket with id: " << servSocket << std::endl;
    
    while(1){
        
        int clientSocket = AcceptTCPConnection(servSocket);
        
        pthread_t threadID;
        
        int result = pthread_create(&threadID, NULL, myThread, &clientSocket);
        
        if(result != 0){
            std::cout << "Error creating thread. Exiting." << result << std::endl;
            return 1;
        }

    }
    
    close(servSocket);
    
    return 0;
}
