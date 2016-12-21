#ifndef PLOTTER_H
#define PLOTTER_H

#include "../Scanner/MotorDriver.h"

class Plotter
{
public:
	Plotter(std::string Path_To_Motors);
	~Plotter();
	void SetX(int destination, int speed);
	void SetY(int destination, int speed);
	
	int GetStatus();

	void StartPlot();
	void EndPlot();

	int GetMotorX();
	int GetMotorY();
private:
	MotorDriver* motorX;
	MotorDriver* motorY;
	MotorDriver* motorPen;

	unsigned int currentY = 0;
	unsigned int currentX = 0;
	unsigned int prevX = 0;
	unsigned int prevY = 0;

	int GetPosition(MotorDriver*);
	int GetSpeed(MotorDriver*);

};

#endif