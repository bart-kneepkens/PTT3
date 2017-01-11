#ifndef PLOTTERCONTROLLER_H
#define PLOTTERCONTROLLER_H

#include "Plotter.h"
#include "../maze_parser/MazeMessage.hpp"
#include "PlotInstruction.h"
#include "../Module/IModule.hpp"
#include "PlotterStatus.h"

enum DrawDirection
{
	Up,
	Down,
	Right,
	Left,
	None,
	End
};

typedef struct SolutionStruct
{
	unsigned int X;
	unsigned int Y;	
}SolutionStruct;

class PlotterController :public IModule
{
public:
	PlotterController();
	~PlotterController();

	int Run(maze_parser::MazeMessage** msg);
	void Stop (bool forceful);
	PlotterStatus GetStatus() const;

private:
	PlotterStatus currentStatus;
	DrawDirection drawSolutionDirection;
	Plotter* plotter;
	std::vector<PlotInstruction>* instructions;
	SolutionStruct sStruct;

	unsigned int movementModifier = 1;
	unsigned int linesPerVertical = 6;

	void parseMazeMessageToMovementInstructions(std::vector<std::vector<char>*>* toDraw);
	void plot(std::vector<PlotInstruction>* instructions);
	void parseSolutionMsg(std::vector<std::vector<char>*>* solution);
	DrawDirection getNextSegment(std::vector<std::vector<char>*>* solution, SolutionStruct* sol, DrawDirection from);

};

#endif