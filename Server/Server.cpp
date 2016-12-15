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
    
    send(clientSocket, "ACK", 4, 0);
    
    std::cout << "returning module : "<< moduleType << ":" << moduleName << ":" << clientSocket << std::endl;
    return Module(moduleType, moduleName, clientSocket);
}

static void * ConnectModuleThread (void * threadArgs){
    int * clntSock_ptr = (int*) threadArgs;
    
    Module m = acceptModule(*clntSock_ptr);
    connectedModules.push_back(m);
    
    pthread_detach(pthread_self());
    return (NULL);
}

static void * WaitForModulesThread (void * threadArgs){
    while(1){
		int clientSocket = AcceptTCPConnection(servSocket);
        
        std::cout << "Accepted client: " << clientSocket << std::endl;
        
        pthread_t threadID;
        
        int result = pthread_create(&threadID, NULL, ConnectModuleThread, &clientSocket);
        
        if(result != 0){
            std::cout << "Error creating thread. Exiting." << result << std::endl;
        }
        
        std::cout << "Checking " << connectedModules.size() << ":3 " << std::endl;
	}
    
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
    
    pthread_t threadID;
	int result = pthread_create(&threadID, NULL, WaitForModulesThread, NULL);
    
    while(1){
		printModules();
		sleep(1);
		
		if(connectedModules.size() == 3){
			std::cout << "--------- Thread detached" << std::endl;
			pthread_detach(threadID);
			pthread_cancel(threadID);
			break;
		}
	}
	
	std::cout << " Type 'start' to start the sequence in default order ... " << std::endl;
	
	std::string userInput;
	
	std::cin >> userInput;
	std::cin.ignore();
	
	if(userInput == "start"){
		std::cout << "Starting Sequence ... " << std::endl;
	}
	
	
    close(servSocket);
    
    return 0;
}
