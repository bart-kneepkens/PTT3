#include <iostream>
#include "Logger.cpp"

int main(){
	// Use the singleton for logging
	// It's not possible to create an instance of Logger.
	Logger::getInstance().logMessage("BOODSCHAP!!");
}
