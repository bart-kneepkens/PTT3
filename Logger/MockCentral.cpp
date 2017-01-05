#include <iostream>
#include "LoggerCentral.cpp"

int main(){
	// Use the singleton for logging
	// It's not possible to create an instance of Logger.
    LoggerCentral central = LoggerCentral();
    
    std::cout << "Will now .run()" << std::endl;
    central.run();
}
