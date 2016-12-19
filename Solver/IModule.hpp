#ifndef PTT3_IMODULE_HPP
#define PTT3_IMODULE_HPP

#include "../maze_parser/MazeMessage.hpp"

/**
 * Abstract parent class for modules. There are currently three types of modules defined:
 *
 * 1. IN modules (example: plotter module), which take a MazeMessage but don't return one;
 * 2. OUT modules (example: scanner module), which do not take a MazeMessage but do return one;
 * 3. INOUT modules (example: solver module), which take a MazeMessage and also return one.
 */
class IModule {
public:
    IModule() {};
    virtual ~IModule() {};

    /**
     * Takes a MazeMessage pointer to poiner (which value may be NULL), performs some logic that may or may not include the supplied
     * pointer's value, and finally places any resulting data in the MazeMessage pointer's value (if any at all).
     * Returns an exit code indicating whether the function exited normally.
     *
     * @param msg Pointer to a pointer to a MazeMessage.
     * @return 0 if the function exited normally, otherwise anything else.
     */
    virtual int Run(maze_parser::MazeMessage** msg) = 0;
};

#endif //PTT3_IMODULE_HPP
