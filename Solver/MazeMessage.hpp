#ifndef SOLVER_MAZEMESSAGE_HPP
#define SOLVER_MAZEMESSAGE_HPP

#include <string>
#include <vector>

/**
 * Contains the definition of the MazeMessage class send between modules.
 */
namespace maze_solver {

    // Using statements within the namespace to hide them from outside.
    using std::vector;
    using std::string;

    class MazeMessage {
    public:
        MazeMessage(vector<vector<string>*> *maze, vector<vector<string>*> *solution);
        ~MazeMessage();
        string toString();

        vector<vector<string>* > *Maze;
        vector<vector<string>* > *Solution;
    };
}


#endif // SOLVER_MAZEMESSAGE_HPP
