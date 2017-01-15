#include "LedController.hpp"

LedController& LedController::getInstance() {
    static LedController instance;
    return instance;
}

LedController::LedController() {
    path = "/sys/class/gpio/";

    exportFile.open((path + "export").c_str());
    exportFile << 14;
    exportFile.close();

    directionFile.open((path + "gpio14/direction").c_str());
    directionFile << "out";
    directionFile.close();

    valueFile.open((path + "gpio14/value").c_str());
}

void LedController::turnLed(bool on) {
    valueFile << on;
    valueFile.flush();
}

