#ifndef SOLVER_IMODULEIN_HPP
#define SOLVER_IMODULEIN_HPP

#include "../maze_parser/MazeMessage.hpp"

class IModuleIN {
public:
    IModuleIN() {};
    virtual ~IModuleIN() {};

    virtual maze_parser::MazeMessage* Run() = 0;
};

#endif //SOLVER_IMODULEIN_HPP
