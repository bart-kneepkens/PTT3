#ifndef SOLVER_MESSAGELISTENER_HPP
#define SOLVER_MESSAGELISTENER_HPP

#include "maze_parser/MazeMessage.hpp"

namespace maze_solver {
    void onMessageReceived(maze_parser::MazeMessage message);
}

#endif  // SOLVER_MESSAGELISTENER_HPP
