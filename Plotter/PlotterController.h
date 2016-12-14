#ifndef PLOTTERCONTROLLER_H
#define PLOTTERCONTROLLER_H

#include "Plotter.h"
#include "MazeMessage.hpp"

enum MazeObject
{
	Maze,
	Solution
};

class PlotterController
{
public:
	PlotterController(std::string Path_To_Motors);
	~PlotterController(); //empty
	void Run(MazeMessage maze, MazeObject objectToDraw);
	void Stop (bool forceful);
	PlotterStatus GetStatus() const;

private:
	PlotterStatus currentStatus;
	Plotter* plotter;
	void plotLine();
	void drawMaze();
	void drawSolution();

};

#endif