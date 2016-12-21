#ifndef PLOTINSTRUCTION_H
#define PLOTINSTRUCTION_H

class PlotInstruction
{
	private:
		bool shouldDraw;
		unsigned int distance;

	public:
		PlotInstruction(bool draw, unsigned int distance);
		bool ShouldDraw() const;
		unsigned int GetDistance() const;
};

#endif