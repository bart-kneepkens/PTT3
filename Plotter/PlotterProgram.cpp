#include "PlotterController.h"
//#include "../maze_parser/MazeMessage.hpp"
#include "Plotter.h"
#include <iostream>

#include "../Generic Module Client/IModule.hpp"

#include "../Scanner/MotorDriver.h"
#include <unistd.h>

std::vector<std::vector<char>*>* vecMaze = new std::vector<std::vector<char>*>();

std::vector<std::vector<char>*>* vecSol;

char OneLine[1][10] = {' ','#',' ','#','#','#','#','#','#',' '};

char maze[10][10] =
	{
		{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{' ','#',' ','#','#','#','#','#','#',' '},
		{' ','#',' ','#',' ',' ',' ',' ','#',' '},
		{' ','#',' ','#','#','#',' ','#','#',' '},
		{' ','#',' ',' ',' ',' ',' ','#','#',' '},
		{' ','#','#','#','#',' ','#','#','#',' '},
		{' ','#',' ',' ','#',' ','#',' ','#',' '},
		{' ','#',' ','#','#',' ','#',' ','#',' '},
		{' ','#',' ',' ',' ',' ',' ',' ','#',' '},
		{' ','#','#',' ','#','#','#','#','#',' '}	
	};

char solution[10][10] = 
{
	{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ','*',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ','*',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ','*',' ',' ',' ',' ',' ',' ',' '},
	{' ',' ','*','*','*','*',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ','*',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ','*',' ',' ',' ',' '},
	{' ',' ',' ',' ',' ','*',' ',' ',' ',' '},
	{' ',' ',' ','*','*','*',' ',' ',' ',' '},
	{' ',' ',' ','*',' ',' ',' ',' ',' ',' '}	
};

void ArrayToVector(char in[10][10])
{
	//std::vector<std::vector<char>*> temp;
	for(int i = 0; i < 10; i++)
	{
		std::vector<char>* row = new std::vector<char>();
		for(int j = 0; j < 10; j++)
		{
std::cout << in[i][j];
			row->push_back(in[i][j]);
		}
std::cout << "size of row: " << row->size();
		vecMaze->push_back(row);
std::cout << std::endl;
	}
	//vecMaze = &temp;
	return;
}

PlotterController* plotter;

int main()
{
	//X-MAX 2400
	//Y-MAX 3400
	std::cout << "Starting" << std::endl;
	plotter = new PlotterController();
	ArrayToVector(maze);
	//vecSol = ArrayToVector(solution);

	std::cout << "Array converted\n";

	std::cout << "Vector is: " << vecMaze->size() << " big\n";

	if (vecMaze != NULL)
	{
		for (int i = 0; i < vecMaze->size(); i++)
		{
			//std::cout << "size of t: " << row.size();
			for (int j = 0; j < 10; j++)
			{
				std::cout << vecMaze->at(i)->at(j);
			}

			std::cout << std::endl;
		}
	}

	std::cout << "Plotter Ready\n" << std::endl;

	plotter->Run(vecMaze);


}