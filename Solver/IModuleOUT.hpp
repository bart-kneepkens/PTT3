#ifndef SOLVER_IMODULEOUT_HPP
#define SOLVER_IMODULEOUT_HPP

#include "../maze_parser/MazeMessage.hpp"

class IModuleOUT {
public:
    IModuleOUT() {};
    virtual ~IModuleOUT() {};

    virtual void Run(maze_parser::MazeMessage& msg) = 0;
};

#endif //SOLVER_IMODULEOUT_HPP
