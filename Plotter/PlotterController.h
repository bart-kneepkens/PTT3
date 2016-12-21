#ifndef PLOTTERCONTROLLER_H
#define PLOTTERCONTROLLER_H

#include "Plotter.h"
#include "MazeMessage.hpp"
#include "PlotInstruction.h"

enum MazeObject
{
	Maze,
	Solution
};

class PlotterController
{
public:
	PlotterController(std::string Path_To_Motors);
	~PlotterController();
	void Run(MazeMessage maze, MazeObject objectToDraw);
	void Stop (bool forceful);
	PlotterStatus GetStatus() const;

private:
	PlotterStatus currentStatus;
	Plotter* plotter;
	std::vector<PlotInstruction> instructions;

	unsigned int movementModifier = 1;
	unsigned int linesPerVertical = 6;

	void parseMazeMessageToMovementInstructions(std::vector<std::vector<char>*>* toDraw);
	void draw(std::vector<PlotInstruction> instructions);

};

#endif