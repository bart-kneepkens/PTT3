#include "PlotInstruction.h"

PlotInstruction::PlotInstruction(bool draw, unsigned int distance)
	: shouldDraw(draw),
	  distance(distance)
{}

bool PlotInstruction::ShouldDraw() const
{
	return shouldDraw;
}
unsigned int PlotInstruction::GetDistance() const
{
	return distance;
}