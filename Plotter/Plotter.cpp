#include "Plotter.h"

#define penUp 0
#define penDown 100

Plotter::Plotter(std::string Path_To_Motors)
{
	motorX   = new MotorDriver(Path_To_Motors + "/motor0/");
	motorY   = new MotorDriver(Path_To_Motors + "/motor1/");
	motorPen = new MotorDriver(Path_To_Motors + "/motor2/");
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

void Plotter::SetX(int destination, int speed)
{
	motorX->Reset();
	motorX->SetSpeed(speed);
	motorX->SetPosition(destination);
	motorX->SetPolarity("normal");
}
void Plotter::SetY(int destination, int speed)
{
	motorY->Reset();
	motorY->SetSpeed(speed);
	motorY->SetPosition(destination);
	motorY->SetPolarity("normal");
}

void Plotter::StartPlot()
{
	motorPen->Reset();
	motorPen->SetSpeed(100);
	motorPen->SetPosition(penDown); //This needs to change to drop pen to drawing height
	motorPen->SetPolarity("normal");
}
void Plotter::EndPlot()
{
	motorPen->Reset();
	motorPen->SetSpeed(100);
	motorPen->SetPosition(penUp); //This needs to change to drop pen to drawing height
	motorPen->SetPolarity("normal");
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
	currentX = GetPosition(MotorX);
	currentY = GetPosition(MotorY);

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
