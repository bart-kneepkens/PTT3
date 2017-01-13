#include "PlotterController.h"
#include "../maze_parser/MazeMessage.hpp"
#include "Plotter.h"
#include <iostream>

#include "../Module/IModule.hpp"

#include "../Scanner/MotorDriver.h"
#include <unistd.h>

std::vector<std::vector<char>*>* vecMaze;
std::vector<std::vector<char>*>* vecSol;

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

std::vector<std::vector<char>*>* ArrayToVector(char in[10][10])
{
	std::vector<std::vector<char>*>* temp;
	for(int i = 0; i < 10; i++)
	{
		
		std::vector<char>* row;
		std::cout << "Converting" << std::endl;
		for(int j = 0; j < 10; j++)
		{
			std::cout << "In loop";
			row->push_back(in[i][j]);
			std::cout << "Row written ";
		}
		temp->push_back(row);
		std::cout << std::endl;
	}
	std::cout << "Array converted" << std::endl;
	return temp;
}

PlotterController* plotter;
maze_parser::MazeMessage* mazeMsg;

int main()
{
	//X-MAX 2400
	//Y-MAX 3400
	std::cout << "Starting" << std::endl;
	plotter = new PlotterController();
	vecMaze = ArrayToVector(maze);
	vecSol = ArrayToVector(solution);


	std::cout << "Things declared" << std::endl;

	for (int Y = 0; Y < vecMaze->size(); Y++)
	{
		std::vector<char>* row = vecMaze->at(Y);
		for (int X = 0; X < row->size(); X++)
		{
			std::cout << row->at(X);
		}

		std::cout << std::endl;
	}

	mazeMsg = new maze_parser::MazeMessage(vecMaze, vecSol);
	plotter->Run(&mazeMsg);


}