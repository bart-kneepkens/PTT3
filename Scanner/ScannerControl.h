#ifndef SCANNERCONTROL_H_
#define SCANNERCONTROL_H_

#include "MotorDriver.h"
#include "Scanner.h"
#include <stdlib.h> 
#include <string>
#include <iostream>
#include <libconfig.h>

class ScannerControl : public IModule
{
	public:
		int ScannerControl::Run(maze_parser::MazeMessage** msg);
	
	private:
		const int xSpeed = 500;
		const int xPosition = 2300;
		const int xSize = 23;

		const int ySpeed = 100;
		const int yStepSize = 100;
		const int ySize = 36; // callibratie 

		const int scanSize = 100;
		const int blackThreshold = 30; // callibratie 
		const int whiteThreshold = 31; // callibratie 

		MotorDriver* motorX;
		MotorDriver* motorY;
		MotorDriver* motorZ;

		Scanner* scanner;
		
		void setMotor(MotorDriver* motor, bool forward);
		void readConfigFile();
}

#endif
