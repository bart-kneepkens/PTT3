#include "ScannerControl.h"

int ScannerControl::Run(maze_parser::MazeMessage** msg)
{
	int indexX = 0;
	int indexY = 0;
	vector<vector<char>*>* scanValues; // Y = 36
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
			
			vector<char>* tempValues;
			
			while(indexX < xSize)
			{
				if (motorX->GetPosition() >= (indexX * scanSize) || motorX->GetPosition() <= -(indexX * scanSize))
				{
					if (indexY % 2 == 0) 
					{
						tempValues->push_back(scanner->GetValue());
					}
					else 
					{
						tempValues->insert(0, scanner->GetValue());
					}
					indexX++;
				}
			}
			
			scanValues->push_back(tempValue);
			
			motorX->Stop();
			motorY->SetPosition(yStepSize);
			
			indexY++;
			
			motorY->RunToRelPos();
		}
		speed = motorY->GetSpeed();
		if (speed == 0 && lastValue != 0) lastValue = 1;
		else lastValue = speed;
	}
}
