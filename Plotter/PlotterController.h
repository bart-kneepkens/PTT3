#ifndef PLOTTERCONTROLLER_H
#define PLOTTERCONTROLLER_H

#include "Plotter.h"
#include "../maze_parser/MazeMessage.hpp"
#include "PlotInstruction.h"
#include "../Module/IModule.hpp"
#include "PlotterStatus.h"

enum MazeObject
{
	Maze,
	Solution
};

class PlotterController :public IModule
{
public:
	PlotterController(std::string Path_To_Motors);
	~PlotterController();

	int Run(maze_parser::MazeMessage** msg);
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