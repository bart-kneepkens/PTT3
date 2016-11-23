#include "MazeSolver.hpp"

const char mock_maze[10][11] =
{
    "# ########",
    "# ########",
    "#       ##",
    "#######  #",
    "#      # #",
    "#      # #",
    "#      # #",
    "#      # #",
    "#      # #",
    "######## #",
};

const char WALL = '#';
const char FREE = ' ';
const char PERSON = '*';

class COORD {
public:
    int X;
    int Y;
    COORD(int x = 0, int y = 0) { X = x, Y = y; }
    COORD(const COORD &coord) { X = coord.X; Y  = coord.Y; }
};

COORD startingPoint = (1,0);
COORD endingPoint = (7,8);

