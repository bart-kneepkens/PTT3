#include "CreateTCPClientSocket.h"
#include <iostream>
#include <sys/socket.h> // for send() and recv()
#include <unistd.h>     // for sleep(), close()

// Place this code into the modules, to be sent at startup.
// Change "localhost" to 10.0.0.42
// Change toSend to hi:{in/out/main}:{modulename}

int main(){
    int sock = CreateTCPClientSocket("localhost", 1111);
    std::cout << "Opened client socket";
    
    char toSend  [1024] = "hi:in:Solver";
    
    std::cout << "size: " << 1024 << " string: " << toSend << std::endl;
    
    send(sock, toSend, 1024, 0);
    std::cout << "\nsent stuff \n";
    
    char reaction [4];
    
    recv(sock,  reaction, 4, 0);
    
    std::cout << reaction << std::endl;
    
    close(sock);
}
