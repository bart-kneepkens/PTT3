#ifndef SIMPLEMAZEPRINTER_H_
#define SIMPLEMAZEPRINTER_H_

#include <iostream>
#include <fstream>

#include "../Generic Module Client/IModule.hpp"

class SimpleMazePrinter : public IModule {
    public:
        SimpleMazePrinter();

        ~SimpleMazePrinter();

        int Run(maze_parser::MazeMessage** msg);
};

#endif // SIMPLEMAZEPRINTER_H_
