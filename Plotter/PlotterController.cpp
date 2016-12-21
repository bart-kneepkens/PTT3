#include "PlotterController.h"

const string path = "";


PlotterController::PlotterController()
{
	plotter = new Plotter(path);
}

PlotterController::~PlotterController()
{}

int Run(maze_parser::MazeMessage** msg)
{
	parseMazeMessageToMovementInstructions(*msg->maze.Scan);

		// case Solution:
		// 	parseMazeMessageToMovementInstructions(*msg->maze.Solution);
	return 0;
}

void PlotterController::Stop(bool forceful)
{
	
}

PlotterStatus PlotterController::GetStatus()
{
	switch (plotter->GetStatus())
	{
		case 0:
		{
			return Idle;
		}
		case 1:
		{
			return Moving;
		}
		case 2:
		{
			return Plotting;
		}
		case -1:
		{
			return Error;
		}
	}
}

void PlotterController::parseMazeMessageToMovementInstructions(std::vector<std::vector<char>*>* toDraw)
{
	if (toDraw != NULL)
	{
		for(std::vector<char> *row : toDraw)
		{
			if (row != NULL)
			{
				bool draw = false;
				bool prevDraw = false;
				int distance = 0;

				int Xaxis = 0;
				for ( ; Xaxis < row->size(); Xaxis++)
				{
					if (*(row+Xaxis) == '#' || *(row+Xaxis) == '*')
					{
						draw = true;
					}
					else 
					{
						draw = false;
					}

					if (draw != prevDraw)
					{
						instructions.push_back(new PlotInstruction(!draw, distance*movementModifier));
						distance = 0;
					}

					distance++;
					prevDraw = draw;
				}

				draw(instructions);
			}
		}
	}
}

PlotterStatus currStat;

void PlotterController::draw(std::vector<PlotInstruction> instructions)
{
	for (int i = 0; i < linesPerVertical; i++)
	{
		double fraction = ((1/linesPerVertical)*i)
		int oscillator = 0;
		while (oscillator < instructions.size())
		{
			PlotInstruction inst = instructions[oscillator];

			currStat = GetStatus();
			if(currStat == Idle)
			{
				++oscillator;
				if (instructions[oscillator].ShouldDraw() == true)
				{
					plotter->StartPlot();
				}
				else
				{
					plotter->EndPlot();
				}

				plotter->SetX(plotter->GetMotorX()+instructions[oscillator].GetDistance());

			}

		}
		while (oscillator > 0)
		{
			PlotInstruction inst = instructions[oscillator];

			currStat = GetStatus();
			if(currStat == Idle)
			{
				--oscillator;
				if (instructions[oscillator].ShouldDraw() == true)
				{
					plotter->StartPlot();
				}
				else
				{
					plotter->EndPlot();
				}
				plotter->SetX(plotter->GetMotorX()-instructions[oscillator].GetDistance())
			}

		}

		plotter->SetY(plotter->GetMotorY()+(fraction*movementModifier));

	}
}