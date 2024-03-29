#include "gtest/gtest.h"
#include "MazeSolver.hpp"
#include <vector>

using std::vector;

maze_solver::MazeSolver solver;

/** 
* Tests whether Run returns 1 if 'msg' parameter is null. 
*/
TEST(MazeSolverTest, test_msg_param_null_1) {
	int result = solver.Run(NULL);
	EXPECT_EQ(result, 1);
}

/** 
* Tests whether Run returns 1 if the value of 'msg' parameter is null. 
*/
TEST(MazeSolverTest, test_msg_param_null_2) {
    maze_parser::MazeMessage* msgPtr = NULL;
	maze_parser::MazeMessage** msgPtrPtr = &msgPtr;

	int result = solver.Run(msgPtrPtr);

	EXPECT_EQ(result, 1);
}

/** 
* Tests whether Run returns 1 and doesn't add a solution to a MazeMessage 
* if its Scan is null. 
*/
TEST(MazeSolverTest, test_scan_null) {
	maze_parser::MazeMessage *ptr = new maze_parser::MazeMessage();

	int result = solver.Run(&ptr);

	EXPECT_EQ(result, 1);
	EXPECT_TRUE(ptr->Solution == NULL);
	
	delete ptr;
}

/** 
* Tests whether Run returns 1 and doesn't add a solution to a MazeMessage 
* if its Scan is empty. 
*/
TEST(MazeSolverTest, test_scan_empty) {
	vector<vector<char>*>* scan = new vector<vector<char>*>() ;
	maze_parser::MazeMessage *ptr = new maze_parser::MazeMessage(scan);

	int result = solver.Run(&ptr);

	EXPECT_EQ(result, 1);
	EXPECT_TRUE(ptr->Solution == NULL);

	delete ptr;
}

/** 
* Tests whether Run returns 0 and adds a solution to a MazeMessage
* if its Scan is a valid maze (it can be solved). Also tests whether
* the generated Solution is filled in (correctly).
*/
TEST(MazeSolverTest, test_scan_valid) {
	// Build small, valid maze.
    vector<vector<char>*>* scan = new vector<vector<char>*>();

	vector<char> *row1 = new vector<char>();
	vector<char> *row2 = new vector<char>();
	vector<char> *row3 = new vector<char>();

	row1->push_back('#');
	row1->push_back(' ');
	row1->push_back('#');

	row2->push_back('#');
	row2->push_back(' ');
	row2->push_back(' ');

	row3->push_back('#');
	row3->push_back('#');
	row3->push_back('#');

	scan->push_back(row1);
	scan->push_back(row2);
	scan->push_back(row3);

	maze_parser::MazeMessage *ptr = new maze_parser::MazeMessage(scan);

	int result = solver.Run(&ptr);

	EXPECT_EQ(result, 0);
	EXPECT_FALSE(ptr->Solution == NULL);

	// Check whether solution is filled in (correctly).
	EXPECT_EQ((ptr)->Solution->at(0)->at(0), ' ');
	EXPECT_EQ((ptr)->Solution->at(0)->at(1), '*');
	EXPECT_EQ((ptr)->Solution->at(0)->at(2), ' ');
	EXPECT_EQ((ptr)->Solution->at(1)->at(0), ' ');
	EXPECT_EQ((ptr)->Solution->at(1)->at(1), '*');
	EXPECT_EQ((ptr)->Solution->at(1)->at(2), '*');
	EXPECT_EQ((ptr)->Solution->at(2)->at(0), ' ');
	EXPECT_EQ((ptr)->Solution->at(2)->at(1), ' ');
	EXPECT_EQ((ptr)->Solution->at(2)->at(2), ' ');

	delete ptr;
}

/** 
* Tests whether Run returns 1 and does not add a solution to a MazeMessage 
* if its Scan is invalid (there are no walls). 
*/
TEST(MazeSolverTest, test_scan_nowalls) {
    // Build small, invalid maze.
    vector<vector<char>*>* scan = new vector<vector<char>*>();

	vector<char> *row1 = new vector<char>();
	vector<char> *row2 = new vector<char>();
	vector<char> *row3 = new vector<char>();

	row1->push_back(' ');
	row1->push_back(' ');
	row1->push_back(' ');

	row2->push_back(' ');
	row2->push_back(' ');
	row2->push_back(' ');

	row3->push_back(' ');
	row3->push_back(' ');
	row3->push_back(' ');

	scan->push_back(row1);
	scan->push_back(row2);
	scan->push_back(row3);

	maze_parser::MazeMessage *ptr = new maze_parser::MazeMessage(scan);

	int result = solver.Run(&ptr);

	EXPECT_EQ(result, 1);
	EXPECT_TRUE((ptr)->Solution == NULL);

	delete ptr;
}

/** 
* Tests whether Run returns 1 and does not add a solution to a MazeMessage 
* if its Scan is invalid (there are not at least 2 openings). 
*/
TEST(MazeSolverTest, test_scan_no_openings) {
    // Build small, invalid maze.
    vector<vector<char>*>* scan = new vector<vector<char>*>();

	vector<char> *row1 = new vector<char>();
	vector<char> *row2 = new vector<char>();
	vector<char> *row3 = new vector<char>();

	row1->push_back('#');
	row1->push_back(' ');
	row1->push_back('#');

	row2->push_back('#');
	row2->push_back(' ');
	row2->push_back('#');

	row3->push_back('#');
	row3->push_back('#');
	row3->push_back('#');

	scan->push_back(row1);
	scan->push_back(row2);
	scan->push_back(row3);

	maze_parser::MazeMessage *ptr = new maze_parser::MazeMessage(scan);

	int result = solver.Run(&ptr);

	EXPECT_EQ(result, 1);
	EXPECT_TRUE(ptr->Solution == NULL);

	delete ptr;
}

/** 
* Tests whether Run returns 1 and does not add a solution to a MazeMessage 
* if its Scan is invalid (there is no solution). 
*/
TEST(MazeSolverTest, test_scan_no_solution) {
    // Build small, invalid maze.
    vector<vector<char>*>* scan = new vector<vector<char>*>();

	vector<char> *row1 = new vector<char>();
	vector<char> *row2 = new vector<char>();
	vector<char> *row3 = new vector<char>();

	row1->push_back('#');
	row1->push_back(' ');
	row1->push_back('#');

	row2->push_back('#');
	row2->push_back('#');
	row2->push_back('#');

	row3->push_back('#');
	row3->push_back(' ');
	row3->push_back('#');

	scan->push_back(row1);
	scan->push_back(row2);
	scan->push_back(row3);

	maze_parser::MazeMessage *ptr = new maze_parser::MazeMessage(scan);

	int result = solver.Run(&ptr);

	EXPECT_EQ(result, 1);
	EXPECT_TRUE(ptr->Solution == NULL);

	delete ptr;
}
