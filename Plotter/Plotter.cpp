#include "Plotter.h"

Plotter::Plotter(std::string Path_To_Motors)
{
	motorX   = new MotorDriver(Path_To_Motors + "/motor0/");
	motorY   = new MotorDriver(Path_To_Motors + "/motor1/");
	motorPen = new MotorDriver(Path_To_Motors + "/motor2/");
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
	motorPen->SetPosition(100); //This needs to change to drop pen to drawing height
	motorPen->SetPolarity("normal");
}
void Plotter::EndPlot()
{
	motorPen->Reset();
	motorPen->SetSpeed(100);
	motorPen->SetPosition(0); //This needs to change to drop pen to drawing height
	motorPen->SetPolarity("normal");
}

