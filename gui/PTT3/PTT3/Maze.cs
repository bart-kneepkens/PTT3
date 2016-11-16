using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PTT3
{
    // The point of this class is to encapsulate the maze, so it becomes easier to (de)serialize from and to JSON.
    class Maze
    {
        public int[,] maze;
    }
}
