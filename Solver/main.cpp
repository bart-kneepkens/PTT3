#include <iostream>
#include "MazeSolver.hpp"
#include "MazeParser.hpp"

using namespace maze_solver;    // Forgive me Father for I have sinned.
using std::vector;

/*vector<vector<char> > * mock_maze = new vector<vector<char> >({
    {'#', ' ', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', ' ', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#'},
    {'#', '#' ,'#' ,'#' ,'#' ,'#' ,'#' ,' ', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', ' ', '#'}
});*/

vector<vector<std::string>> * mock_maze = new vector<vector<std::string> >({
    {"#", " ", "#", "#", "#", "#", "#", "#", "#", "#"},
    {"#", " ", "#", "#", "#", "#", "#", "#", "#", "#"},
    {"#", " ", " ", " ", " ", " ", " ", " ", "#", "#"},
    {"#", "#" ,"#" ,"#" ,"#" ,"#" ,"#" ," ", " ", "#"},
    {"#", " ", " ", " ", " ", " ", " ", "#", " ", "#"},
    {"#", " ", " ", " ", " ", " ", " ", "#", " ", "#"},
    {"#", " ", " ", " ", " ", " ", " ", "#", " ", "#"},
    {"#", " ", " ", " ", " ", " ", " ", "#", " ", "#"},
    {"#", " ", " ", " ", " ", " ", " ", "#", " ", "#"},
    {"#", "#", "#", "#", "#", "#", "#", "#", " ", "#"}});

MazeMessage * msg = new MazeMessage(mock_maze, mock_maze);

int main() {

    std::string json = maze_solver::mazeMessageToJson(*msg, false, false);
    MazeMessage *newMsg = maze_solver::jsonToMazeMessage(json, false, false);
    //std::cout << *(newMsg->Maze) << std::endl;
    //std::cout << newMsg->Solution << std::endl;

    //std::cout << newMsg->Maze->at(0) << std::endl;
    std::cout << maze_solver::mazeMessageToJson(*newMsg, false, false) << std::endl;

    //json dick;
    //dick["maze"] = *mock_maze;
    //std::cout << dick.dump() << std::endl;


    /*
     vector<vector<char>> *maze = new vector<vector<char>> ({
     {'1', '1', '0', '1', '1', '1'},
     {'1', '0', '0', '0', '0', '1'},
     {'1', '1', '0', '1', '0', '1'},
     {'1', '0', '0', '0', '1', '1'},
     {'1', '0', '1', '0', '0', '1'},
     {'1', '1', '1', '0', '1', '1'}});
     
     vector<vector<char>> *solution = new vector<vector<char>> ({
     {'0', '0', '1', '0', '0', '0'},
     {'0', '0', '1', '0', '0', '0'},
     {'0', '0', '1', '0', '0', '0'},
     {'0', '0', '1', '1', '0', '0'},
     {'0', '0', '0', '1', '0', '0'},
     {'0', '0', '0', '1', '0', '0'}});
     
     //vector<vector<int>> *fog = new vector<vector<int>>({{1, 1, 1}, {1, 1, 1}});
     
     //std::cout << *solution->at(0).at(0) << std::endl;
     
     maze_solver::MazeMessage message = maze_solver::MazeMessage(maze, solution);
     std::string asJson = maze_solver::mazeMessageToJson(message, true);
     std::cout << asJson << std::endl;
     
     //const nlohmann::json j = {"maze", maze};
     //nlohmann::json::array
     //std::string str = j.dump(4);
     //std::cout << str << std::endl;
     
     //std::cout << maze_solver::allToJson(maze, maze, true).dump(2) << std::endl;
     
     return 0;
     */
    
    //maze_solver::MazeMessage mes = maze_solver::MazeMessage(&mock_maze, NULL);
    
    //maze_solver::MazeSolver solv = maze_solver::MazeSolver();
    
    //solv.solve(&mes);
    
    return 0;
}

