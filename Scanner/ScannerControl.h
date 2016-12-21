#ifndef SCANNERCONTROL_H_
#define SCANNERCONTROL_H_

#include "IModule.hpp"
#include "../maze_parser/MazeMessage.hpp"

using std::vector;

class ScannerControl : public IModule
{
	private:
	
	public:
		int Run(maze_parser::MazeMessage** msg);
};

#endif
