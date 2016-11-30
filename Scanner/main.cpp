#include "MotorDriver.h"
#include "Scanner.h"

const int xSpeed = 500;
const int xPosition = 2500;
const int xSize = 25;

const int ySpeed = 100;
const int yStepSize = 100;
const int ySize = 36; // callibratie 

const int scanSize = 100;
const int blackThreshold = 25; // callibratie 
const int whiteThreshold = 35; // callibratie 

void setMotor(MotorDriver* motor, bool forward);

int main(void)
{
	MotorDriver* motorX = new MotorDriver("/sys/class/tacho-motor/motor2/"); // callibratie 
	MotorDriver* motorY = new MotorDriver("/sys/class/tacho-motor/motor0/"); // callibratie 
	Scanner* scanner = new Scanner("/sys/class/lego-sensor/sensor0/");  // callibratie 
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
				std::cout << indexX << std::endl;
			}
			
			motorX->Stop();
			motorY->SetPosition(yStepSize);
			indexY++;
			
			motorY->RunToRelPos();
		}
		speed = motorY->GetSpeed();
		if (speed == 0 && lastValue != 0) lastValue = 1;
		else lastValue = speed;
		std::cout << indexY << std::endl; 
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
