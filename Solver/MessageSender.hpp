#ifndef SOLVER_MESSAGESENDER_HPP
#define SOLVER_MESSAGESENDER_HPP

#include "maze_parser/MazeMessage.hpp"

namespace maze_solver {
    void send(maze_parser::MazeMessage mazeMessage);
}

#endif  // SOLVER_MESSAGESENDER_HPP
