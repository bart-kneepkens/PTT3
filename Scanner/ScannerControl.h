#ifndef SCANNERCONTROL_H_
#define SCANNERCONTROL_H_

#include "MotorDriver.h"
#include "Scanner.h"
#include <stdlib.h> 
#include <string>
#include <iostream>
#include <vector>
#include "../Generic Module Client/IModule.hpp"

class ScannerControl : public IModule
{
	public:
		int Run(maze_parser::MazeMessage** msg);
		ScannerControl();
		~ScannerControl();
	
	private:
		int xSpeed;
		int xPosition;
		int xSize;

		int ySpeed;
		int yStepSize;
		int ySize; // callibratie 

		int scanSize;
		int blackThreshold; // callibratie 
		int whiteThreshold;

		MotorDriver* motorX;
		MotorDriver* motorY;
		MotorDriver* motorZ;

		Scanner* scanner;
		
		void setMotor(MotorDriver* motor, bool forward);
		void readConfigFile();
};

#endif
