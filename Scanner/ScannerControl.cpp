#include "ScannerControl.h"

int ScannerControl::Run(maze_parser::MazeMessage** msg)
{
	readConfigFile();
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
			
			indexY++;
			
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

void ScannerControl::setMotor(MotorDriver* motor, bool forward)
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

void ScannerControl::readConfigFile()
{
    /*
	int x;
	int y;
	int z;
	int sensor;
	Config config;
	
	config.readFile("settings.conf");
	
	if(config.lookupValue("MotorX", x)
		&& config.lookupValue("MotorY", y)
		&& config.lookupValue("MotorZ", z)
		&& config.lookupValue("Sensor", sensor))
	{
		motorX = new MotorDriver("/sys/class/tacho-motor/motor" + x + "/");
		motorY = new MotorDriver("/sys/class/tacho-motor/motor" + y + "/");
		motorZ = new MotorDriver("/sys/class/tacho-motor/motor" + z + "/");
		scanner = new Scanner("/sys/class/lego-sensor/sensor" + sensor + "/"); 
	}
     */
}
