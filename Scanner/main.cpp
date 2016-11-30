#include "MotorDriver.h"
#include "Scanner.h"

int main(void)
{
	MotorDriver* motorX = new MotorDriver("/sys/class/tacho-motor/motor1/");
	MotorDriver* motorY = new MotorDriver("/sys/class/tacho-motor/motor0/");
	Scanner* scanner = new Scanner("/sys/class/lego-sensor/sensor0/");
	int indexX = 0;
	int indexY = 0;
	int scanValues[22][25]; // Y = 36
	int lastValue = 1;
	int speed = 0;
	
	motorX->Reset();
	motorX->SetSpeed(500);
	motorX->SetPosition(2500); //X Direction MAX 2700
	motorX->SetPolarity("normal");
	
	motorY->Reset();
	motorY->SetSpeed(100);
	scanner->SetMode("COL-REFLECT");
	
	//motor->SetPosition(3750); Y Direction
	
	while(indexY < 22)
	{
		if (indexY % 2 == 0) 
		{
			motorX->Reset();
			motorX->SetSpeed(500);
			motorX->SetPosition(2500); //X Direction MAX 2700
			motorX->SetPolarity("normal");
		}
		else motorX->SetPosition(-2500);
		
		std::cout << lastValue << "  -  " << motorY->GetSpeed() << "\n";
		
		if (lastValue != 0 && motorY->GetSpeed() == 0)
		{
			lastValue = 0;
			motorX->RunToRelPos();
			if (indexY % 2 == 0)
			{
				indexX = 0;
				while(indexX < 25)
				{
					if (motorX->GetPosition() >= (indexX * 100))
					{
						scanValues[indexY][indexX] = scanner->GetValue();
						indexX++;
					}
				}
			}
			else
			{
				motorX->Reset();
				motorX->SetSpeed(500);
				motorX->SetPosition(-2500); //X Direction MAX 2700
				motorX->RunToRelPos();
				indexX = 0;
				while(indexX < 25)
				{
					if (motorX->GetPosition() <= -(indexX * 100))
					{
						scanValues[indexY][25 - indexX] = scanner->GetValue();
						indexX++;
					}
				}
			}
			motorX->Stop();
			motorY->SetPosition(100);
			indexY++;
			
			motorY->RunToRelPos();
		}
		speed = motorY->GetSpeed();
		if (speed == 0 && lastValue != 0) lastValue = 1;
		else lastValue = speed;
		std::cout << indexY << "\n\n"; 
	}
	
	std::cout << std::endl << std::endl;
	for(int y = 0; y < 22; y++)
	{
		for(int x = 0; x < 25; x++)
		{
			if (scanValues[y][x] < 25) std::cout << "#";
			else if (scanValues[y][x] > 35) std::cout << " ";
			else std::cout << "*";
		}
		std::cout << std::endl;
	}
}
