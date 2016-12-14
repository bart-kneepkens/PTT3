#include "Module.cpp"
#include "CreateTCPServerSocket.cpp"
#include "AcceptTCPConnection.cpp"
#include <sys/socket.h> // for send() and recv()
#include <iostream>
#include <unistd.h>     // for sleep(), close()

class Server{
    
    int StartSequence(){
        
    }
    
    int connectModule(){
        
    }
    
    int runModule(){
        
    }
};


int servSocket;
int clientSocket;

int main(){
    // Wait for modules to send connect message async
    
    // Wait for user to give Start signal async
    
    servSocket = CreateTCPServerSocket(1234);
    
    std::cout << "Created server socket with id: " << servSocket << std::endl;
    
    clientSocket = AcceptTCPConnection(servSocket);
    
    std::cout << "Accepted client with id: " << clientSocket << std::endl;
    
    char buff[1024];
    
    int received = recv(clientSocket, buff, 1024,0);
    
    std::cout << "Received: " << buff << std::endl;
    
    std::string helloString(buff);
    
    std::cout << "Received: " << helloString << std::endl;
    
    close(clientSocket);
    
    close(servSocket);
    
    
    return 0;
}

Module waitForModule(){
    
    return Module();
}
