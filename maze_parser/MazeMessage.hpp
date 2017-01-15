#ifndef SOLVER_MAZEMESSAGE_HPP
#define SOLVER_MAZEMESSAGE_HPP

#include <string>
#include <vector>

/**
 * Contains the definition of the MazeMessage class send between modules.
 */
namespace maze_parser {

    // Using statements within the namespace to hide them from outside.
    using std::vector;

    class MazeMessage {
    public:
        MazeMessage(vector<vector<char>*>* scan = new vector<vector<char>*>(),
                    vector<vector<char>*>* solution = new vector<vector<char>*>());

        ~MazeMessage();

        std::string toString() const;

        vector<vector <char>*>* Scan;
        vector<vector <char>*>* Solution;
    };
}


#endif // SOLVER_MAZEMESSAGE_HPP
