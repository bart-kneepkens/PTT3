#include <iostream>
#include "Logger.cpp"

int main(){
	std::cout << "hey b0ss." << std::endl;
	Logger::getInstance().logMessage("BOODSCHAP!!");
}
