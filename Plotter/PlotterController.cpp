#include "PlotterController.h"

const std::string path = "/sys/class/tacho-motor";


PlotterController::PlotterController()
{
	plotter = new Plotter(path);
	drawSolutionDirection = None;
}

PlotterController::~PlotterController()
{}

void PlotterController::parseMazeMessageToMovementInstructions(std::vector<std::vector<char>*>* toDraw)
{
std::cout << "Message received, parsing vector of size: " << (*toDraw).size() << std::endl;
	if (toDraw != NULL)
	{
		for(int i = 0; i < toDraw->size(); i++)
		{
			std::vector<char>* row = toDraw->at(i); 
			
			bool draw = false;
			bool prevDraw = false;
			int distance = 0;

			for (int Xaxis = 0; Xaxis < row->size(); Xaxis++)
			{
				if (row->at(Xaxis) == '#')
				{
					draw = true;
std::cout << "#";
				}
				else 
				{
					draw = false;
std::cout << " ";
				}

				if (draw != prevDraw)
				{
std::cout << "New instruction generated\n";
					PlotInstruction* newInstruction = new PlotInstruction(!draw, distance*movementModifier);
					instructions.push_back(*newInstruction);
					distance = 0;
				}

				distance++;
				prevDraw = draw;
			}

			plot(&instructions);
			
		}
	}
}

int PlotterController::Run(maze_parser::MazeMessage** msg)
{
	if (msg != NULL)
	{
		if ((**msg).Scan != NULL)
		{
			std::vector<std::vector<char>*>* Scanned = (*msg)->Scan;
			parseMazeMessageToMovementInstructions((**msg).Scan);
		}
	}
		// case Solution:
		// 	parseMazeMessageToMovementInstructions(*msg->maze.Solution);
	return 0;
}

int PlotterController::Run(std::vector<std::vector<char>*>* maze)
{
	parseMazeMessageToMovementInstructions(maze);
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
std::cout << "Attempting to plot run instruction\n";
	for (int i = 0; i < linesPerVertical; i++)
	{
std::cout << "Reading through instructions: " + instructions->size();
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

				plotter->SetX(plotter->GetMotorX()+instructions->at(oscillator).GetDistance(), 100, true);
			}
std::cout << "Line drawn;";
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
				plotter->SetX(plotter->GetMotorX()-instructions->at(oscillator).GetDistance(), 100, false);
			}
		}

std::cout << "\n Starting Next Line\n";
		plotter->SetY(plotter->GetMotorY()+(fraction*movementModifier), 100,true);

	}
}