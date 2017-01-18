#include "gtest/gtest.h"
#include "MazeSolver.hpp"

maze_parser::MazeSolver solver;

/** 
* Tests whether Run returns 1 if 'msg' parameter is null. 
*/
TEST(MazeSolverTest, test_msg_param_null_1) {
    
}

/** 
* Tests whether Run returns 1 if the value of 'msg' parameter is null. 
*/
TEST(MazeSolverTest, test_msg_param_null_2) {
    
}

/** 
* Tests whether Run returns 1 and doesn't add a solution to a MazeMessage 
* if its Scan is null. 
*/
TEST(MazeSolverTest, test_scan_null) {
    
}

/** 
* Tests whether Run returns 1 and doesn't add a solution to a MazeMessage 
* if its Scan is empty. 
*/
TEST(MazeSolverTest, test_scan_empty) {
    
}

/** 
* Tests whether Run returns 0 and adds a solution to a MazeMessage
* if its Scan is a valid maze (it can be solved). 
*/
TEST(MazeSolverTest, test_scan_valid) {
    
}

/** 
* Tests whether Run returns 1 and does not add a solution to a MazeMessage 
* if its Scan is invalid (there are no walls). 
*/
TEST(MazeSolverTest, test_scan_nowalls) {
    
}

/** 
* Tests whether Run returns 1 and does not add a solution to a MazeMessage 
* if its Scan is invalid (there are not at least 2 openings). 
*/
TEST(MazeSolverTest, test_scan_no_openings) {
    
}

/** 
* Tests whether Run returns 1 and does not add a solution to a MazeMessage 
* if its Scan is invalid (there is no solution). 
*/
TEST(MazeSolverTest, test_scan_no_solution) {
    
}
