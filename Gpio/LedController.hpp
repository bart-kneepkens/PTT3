#ifndef GPIO_LEDCONTROLLER_HPP
#define GPIO_LEDCONTROLLER_HPP

#include <iostream>
#include <fstream>
#include <unistd.h>

/*
 This class sets GPIO Pin 14 to HIGH or LOW.
 It does this by doing the following:
 1. Go into /sys/class/gpio.
 2. Write '14' to the file 'export' (this creates the folder gpio14).
 3. Go into /sys/class/gpio/gpio14.
 4. Write 'out' to the file 'direction' in the folder 'gpio14'.
 5. Write a HIGH (1) or LOW (0) to the file 'value' on request (turnLed() method).
 */
class LedController{
public:
    // This function makes this class a singleton.
    static LedController& getInstance();

    // Turn the LED on or off.
    void turnLed(bool on);

private:
    std::ofstream exportFile, directionFile, valueFile;
    std::string path;

    // Open the prepare the gpio14 folder, the Pin direction and open the value file.
    LedController();

    // These functions are private to make this class a singleton.
    LedController(LedController const&);
    void operator=(LedController const&);
};

#endif //GPIO_LEDCONTROLLER_HPP
