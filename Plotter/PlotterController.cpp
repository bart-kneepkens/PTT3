#include "PlotterController.h"

const std::string path = "";


PlotterController::PlotterController()
{
	plotter = new Plotter(path);
}

PlotterController::~PlotterController()
{}

void PlotterController::parseMazeMessageToMovementInstructions(std::vector<std::vector<char>*>* toDraw)
{
	if (toDraw != NULL)
	{
		for(int i = 0; i < toDraw->size(); i++)
		{
			std::vector<char>* row = toDraw->at(i); 
			if (row != NULL)
			{
				bool draw = false;
				bool prevDraw = false;
				int distance = 0;

				for (int Xaxis = 0; Xaxis < row->size(); Xaxis++)
				{
					if (row->at(Xaxis) == '#' || row->at(Xaxis) == '*')
					{
						draw = true;
					}
					else 
					{
						draw = false;
					}

					if (draw != prevDraw)
					{
						PlotInstruction* newInstruction = new PlotInstruction(!draw, distance*movementModifier);
						instructions->push_back(*newInstruction);
						distance = 0;
					}

					distance++;
					prevDraw = draw;
				}

				plot(instructions);
			}
		}
	}
}

int PlotterController::Run(maze_parser::MazeMessage** msg)
{
	parseMazeMessageToMovementInstructions((**msg).Scan);

		// case Solution:
		// 	parseMazeMessageToMovementInstructions(*msg->maze.Solution);
	return 0;
}

void PlotterController::Stop(bool forceful)
{

}

PlotterStatus PlotterController::GetStatus() const
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

PlotterStatus currStat;

void PlotterController::plot(std::vector<PlotInstruction>* instructions)
{
	for (int i = 0; i < linesPerVertical; i++)
	{
		double fraction = ((1/linesPerVertical)*i);
		int oscillator = 0;
		while (oscillator < instructions->size())
		{
			PlotInstruction inst = instructions->at(oscillator);

			currStat = GetStatus();
			if(currStat == Idle)
			{
				++oscillator;
				if (instructions->at(oscillator).ShouldDraw() == true)
				{
					plotter->StartPlot();
				}
				else
				{
					plotter->EndPlot();
				}

				plotter->SetX(plotter->GetMotorX()+instructions->at(oscillator).GetDistance(), 100);
			}

		}
		while (oscillator > 0)
		{
			PlotInstruction inst = instructions->at(oscillator);

			currStat = GetStatus();
			if(currStat == Idle)
			{
				--oscillator;
				if (instructions->at(oscillator).ShouldDraw() == true)
				{
					plotter->StartPlot();
				}
				else
				{
					plotter->EndPlot();
				}
				plotter->SetX(plotter->GetMotorX()-instructions->at(oscillator).GetDistance(), 100);
			}
		}

		plotter->SetY(plotter->GetMotorY()+(fraction*movementModifier), 100);

	}
}