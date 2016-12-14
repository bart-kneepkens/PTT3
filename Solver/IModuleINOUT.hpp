#ifndef SOLVER_IMODULEINOUT_HPP
#define SOLVER_IMODULEINOUT_HPP

#include "../maze_parser/MazeMessage.hpp"

class IModuleINOUT {
public:
    IModuleINOUT() {};
    virtual ~IModuleINOUT() {};

    virtual maze_parser::MazeMessage* Run(maze_parser::MazeMessage& msg) = 0;
};

#endif //SOLVER_IMODULEINOUT_HPP
