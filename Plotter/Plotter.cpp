#include "Plotter.h"
#include <unistd.h>
#include <iostream>

#define penUp 50
#define penDown 0

Plotter::Plotter(std::string Path_To_Motors)
{
	motorX   = new MotorDriver(Path_To_Motors + "/motor1/");
	motorY   = new MotorDriver(Path_To_Motors + "/motor0/");
	motorPen = new MotorDriver(Path_To_Motors + "/motor2/");

	motorX->Reset();
	motorY->Reset();
	motorPen->Reset();

	SetX(0, 100, true); //Reset both motors to 0 origin. Hold the motor off their rail until they are at the origin.
	SetY(0, 100, true); 
	motorX->RunToRelPos();
	motorY->RunToRelPos();


	motorPen->SetSpeed(500);
	motorPen->SetPosition(100);
	motorPen->SetPolarity("normal");
	motorPen->RunToRelPos();
	sleep(2);
	motorPen->SetPosition(-100);
	motorPen->RunToRelPos();
}

Plotter::~Plotter()
{
	delete motorX;
	motorX = NULL;

	delete motorY;
	motorY = NULL;

	delete motorPen;
	motorPen = NULL;
}

void Plotter::SetX(int destination, int speed, bool inverse)
{
	motorX->Reset();
	motorX->SetSpeed(speed);
	motorX->SetPosition(destination);
	switch (inverse)
	{
		case true:
		motorX->SetPolarity("inversed");

		case false:
		motorX->SetPolarity("normal");
	}
	motorX->RunToRelPos();
}
void Plotter::SetY(int destination, int speed, bool inverse)
{
	motorY->Reset();
	motorY->SetSpeed(speed);
	motorY->SetPosition(destination);
	switch (inverse)
	{
		case true:
		motorY->SetPolarity("inversed");

		case false:
		motorY->SetPolarity("normal");
	}
	motorY->RunToRelPos();
}

void Plotter::StartPlot()
{
std::cout << "Plot Start\n";
	motorPen->SetSpeed(500);
	motorPen->SetPosition(penUp); //This needs to change to drop pen to drawing height
	motorPen->SetPolarity("inverse");
	motorPen->RunToRelPos();
}
void Plotter::EndPlot()
{
std::cout << "Plot End\n";
	motorPen->SetSpeed(500);
	motorPen->SetPosition(-penUp); //This needs to change to drop pen to drawing height
	motorPen->SetPolarity("normal");
	motorPen->RunToRelPos();
}

int Plotter::GetPosition(MotorDriver* motor)
{
	return motor->GetPosition();
}

int Plotter::GetSpeed(MotorDriver* motor)
{
	return motor->GetSpeed();
}

int Plotter::GetStatus()
{
	currentX = GetPosition(motorX);
	currentY = GetPosition(motorY);

	int result = 0;

	if(currentX != prevX || currentY != prevY)
	{
		result = 1;

		if(GetPosition(motorPen) >= penDown)
		{
			result = 2;
		}
	}

	return result;
}

int Plotter::GetMotorX()
{
	return GetPosition(motorX);
}

int Plotter::GetMotorY()
{
	return GetPosition(motorY);
}
