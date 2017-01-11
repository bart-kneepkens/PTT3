#include <iostream>
#include <fstream>
#include <unistd.h>

class LedController{
	public:
		static LedController& getInstance(){
			static LedController instance;
			return instance;
		}
		
		void turnLed(bool on) {
			valueFile << on;
			valueFile.flush();
		}
		
	private:
		std::ofstream exportFile, directionFile, valueFile; 
		std::string path;
		
		LedController(){
			path = "/sys/class/gpio/";
			
			exportFile.open((path + "export").c_str());
			exportFile << 14;
			exportFile.close();
			
			directionFile.open((path + "gpio14/direction").c_str());
			directionFile << "out";
			directionFile.close();
			
			valueFile.open((path + "gpio14/value").c_str());
		}
		
		LedController(LedController const&);
		void operator=(LedController const&);
};

