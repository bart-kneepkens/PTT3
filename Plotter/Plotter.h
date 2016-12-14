#ifndef PLOTTER_H
#define PLOTTER_H

#include "../MotorDriver/MotorDriver.h"

class Plotter
{
public:
	Plotter(std::string Path_To_Motors);
	void SetX(int destination, int speed);
	void SetY(int destination, int speed);

	void StartPlot();
	void EndPlot();
private:
	MotorDriver* motorX;
	MotorDriver* motorY;
	MotorDriver* motorPen;
}

#endif