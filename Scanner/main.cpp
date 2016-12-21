#include "MotorDriver.h"
#include "Scanner.h"
#include <stdlib.h> 
#include <string>
#include <iostream>

const int xSpeed = 500;
const int xPosition = 2300;
const int xSize = 25;

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
void callibrate();

int main(void)
{
	callibrate();
	int indexX = 0;
	int indexY = 0;
	int scanValues[ySize][xSize]; // Y = 36
	int lastValue = 1;
	int speed = 0;
	
	motorY->Reset();
	motorY->SetSpeed(ySpeed);
	scanner->SetMode("COL-REFLECT");
	
	while(indexY < ySize)
	{
		if (indexY % 2 == 0) 
		{
			setMotor(motorX, true);
		}
		else 
		{
			setMotor(motorX, false);
		}
		
		if (lastValue != 0 && motorY->GetSpeed() == 0)
		{
			lastValue = 0;
			motorX->RunToRelPos();
			indexX = 0;
			
			while(indexX < xSize)
			{
				if (motorX->GetPosition() >= (indexX * scanSize) || motorX->GetPosition() <= -(indexX * scanSize))
				{
					if (indexY % 2 == 0) 
					{
						scanValues[indexY][indexX] = scanner->GetValue();
					}
					else 
					{
						scanValues[indexY][xSize - indexX] = scanner->GetValue();
					}
					indexX++;
				}
			}
			
			motorX->Stop();
			motorY->SetPosition(yStepSize);
			
			
			
			// DIT MOET NOG WEG!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			
			for(int x = 0; x < xSize; x++)
			{
				if (scanValues[indexY][x] <= blackThreshold) std::cout << "#";
				else if (scanValues[indexY][x] >= whiteThreshold) std::cout << " ";
				else std::cout << "*";
			}
			std::cout << std::endl;
			
			
			
			
			
			
			
			
			indexY++;
std::cout << "IndexY :" << indexY << std::endl;
			
			motorY->RunToRelPos();
		}
		speed = motorY->GetSpeed();
		if (speed == 0 && lastValue != 0) lastValue = 1;
		else lastValue = speed;
	}
	
	std::cout << std::endl << std::endl;
	for(int y = 0; y < ySize; y++)
	{
		for(int x = 0; x < xSize; x++)
		{
			if (scanValues[y][x] < blackThreshold) std::cout << "#";
			else if (scanValues[y][x] > whiteThreshold) std::cout << " ";
			else std::cout << "*";
		}
		std::cout << std::endl;
	}
}

void setMotor(MotorDriver* motor, bool forward)
{
	motor->Reset();
	motor->SetSpeed(xSpeed);
	if (forward) 
	{
		motor->SetPosition(xPosition);
	}
	else
	{
		motor->SetPosition(-xPosition);
	}
	motor->SetPolarity("normal");
}

void callibrate()
{
	std::string value = "";
	system("for f in /sys/class/tacho-motor/*; do echo -n \"$f: \"; cat $f/address; done");
	
	std::cout << "Enter number for motor X" << std::endl;
	std::cin >> value;
	std::cin.ignore();
	motorX = new MotorDriver("/sys/class/tacho-motor/motor" + value + "/");
	
	value = "";
	std::cout << "Enter number for motor Y" << std::endl;
	std::cin >> value;
	std::cin.ignore();
	motorY = new MotorDriver("/sys/class/tacho-motor/motor" + value + "/");
	
	value = "";
	std::cout << "Enter number for motor Z" << std::endl;
	std::cin >> value;
	std::cin.ignore();
	motorZ = new MotorDriver("/sys/class/tacho-motor/motor" + value + "/");
	
	system("for f in /sys/class/lego-sensor/*; do echo -n \"$f: \"; cat $f/address; done");
	
	value = "";
	std::cout << "Enter number for sensor" << std::endl;
	std::cin >> value;
	std::cin.ignore();
	scanner = new Scanner("/sys/class/lego-sensor/sensor" + value + "/");
	
	/*motorZ->Reset();
	motorX->Reset();
	motorY->Reset();
	
	motorZ->SetSpeed(500);
	motorZ->SetPosition(5000);
	motorZ->Run();
	while(motorZ->GetState().find("overloaded") == std::string::npos) { std::cout << ""; }
	std::cout << std::endl;
	
	motorZ->Stop();
	motorZ->Reset();
	
	int currentPosition = motorZ->GetPosition();
	
	motorZ->SetPosition(-200);
	motorZ->SetSpeed(195);
	motorZ->RunToRelPos();
	
	while (currentPosition + motorZ->GetPosition() > -200) { std::cout << ""; } // { /*wait }
	std::cout << std::endl;
	
std::cout << "Voor MotorY" << std::endl;
	motorY->SetSpeed(-200);
	motorY->Run();
	while(motorY->GetState().find("overloaded") == std::string::npos) { std::cout << ""; }
	std::cout << std::endl;
	motorY->Stop();
std::cout << "Na MotorY" << std::endl;
	
	
std::cout << "Voor MotorX" << std::endl;
	motorX->SetSpeed(200);
	motorX->Run();
	while(motorX->GetState().find("overloaded") == std::string::npos) { std::cout << ""; }
	std::cout << std::endl;
	motorX->Stop();
std::cout << "Na MotorX" << std::endl;

	while(true);*/
}
