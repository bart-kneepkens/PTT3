#include <iostream>
#include "MazeMessage.hpp"
#include "MazeSolver.hpp"

using std::vector;

std::vector<std::vector<char> > mock_maze {
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
};

int main() {
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
    
    maze_solver::MazeMessage mes = maze_solver::MazeMessage(&mock_maze, NULL);
    
    maze_solver::MazeSolver solv = maze_solver::MazeSolver();
    
    solv.solve(mes);
    
    return 0;
}

