#include "Module.cpp"
#include "CreateTCPServerSocket.cpp"
#include "AcceptTCPConnection.cpp"
#include <sys/socket.h> // for send() and recv()
#include <iostream>
#include <unistd.h>     // for sleep(), close()
#include <vector>
#include <string>
#include <sstream>

class Server{
    
    int StartSequence(){
        
    }
    
    int connectModule(){
        
    }
    
    int runModule(){
        
    }
};

int servSocket;


Module waitForModule(){
    int clientSocket = AcceptTCPConnection(servSocket);
    
    std::cout << "Accepted client with id: " << clientSocket << std::endl;
    
    char buff[1024];
    
    int received = recv(clientSocket, buff, 1024,0);
    
    //std::cout << "Received: " << buff << std::endl;
    
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

int main(){
    // Wait for modules to send connect message async
    
    // Wait for user to give Start signal async
    
    servSocket = CreateTCPServerSocket(1234);
    
    std::cout << "Created server socket with id: " << servSocket << std::endl;
    
    waitForModule();
    
    close(servSocket);
    
    
    return 0;
}
