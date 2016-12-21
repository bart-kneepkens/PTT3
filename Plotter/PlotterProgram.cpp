#include "PlotterController.h"
#include "../maze_parser/MazeParser.hpp"
#include <iostream>

#include "../Module/IModule.hpp"

std::vector<std::vector<char>> testScan;

char array[10][10] =
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

std::vector<std::vector<char>> ArrayToVector(char in[10][10])
{
	std::vector<std::vector<char>> temp;
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			temp[i][j] = in[i][j];

			std::cout << in[i][j];
		}

		std::cout << std::endl;
	}

	return temp;
}

int main()
{
	testScan = ArrayToVector(array);
}