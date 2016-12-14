#include <iostream>
#include <string>

class Module{
private:
    std::string type;
    std::string name;
    int socketFD;
    
public:
    Module(std::string type, std::string name, int fileDescriptor){
        this->type = type;
        this->name = name;
        this->socketFD = fileDescriptor;
    }
    
    std::string GetType(){
        return type;
    }
    
    std::string GetName(){
        return name;
    }
    
    int GetSocketFD(){
        return socketFD;
    }
};
