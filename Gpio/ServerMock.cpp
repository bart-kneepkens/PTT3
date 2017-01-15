#include "LedController.hpp"
#include <unistd.h>

int main(){
	while(true){
		LedController::getInstance().turnLed(true);
		sleep(1);
		LedController::getInstance().turnLed(false);
		sleep(1);
	}
	
}
