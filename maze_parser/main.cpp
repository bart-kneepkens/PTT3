#include <iostream>
#include "MazeParser.hpp"

int main(){
	maze_parser::MazeMessage msg = maze_parser::MazeMessage();
	std::string js = maze_parser::mazeMessageToJson(msg);
	//std::cout << js << std::endl;
	
	std::string fullMaze = "{\r\n\t\"scan\": [\r\n\t\t[\"#\", \" \", \"#\", \"#\", \"#\", \"#\", \"#\", \"#\", \"#\", \"#\"],\r\n\t\t[\"#\", \" \", \"#\", \"#\", \"#\", \"#\", \"#\", \"#\", \"#\", \"#\"],\r\n\t\t[\"#\", \" \", \" \", \" \", \" \", \" \", \" \", \" \", \"#\", \"#\"],\r\n\t\t[\"#\", \"#\", \"#\", \"#\", \"#\", \"#\", \"#\", \" \", \" \", \"#\"],\r\n\t\t[\"#\", \" \", \" \", \" \", \" \", \" \", \" \", \"#\", \" \", \"#\"],\r\n\t\t[\"#\", \" \", \" \", \" \", \" \", \" \", \" \", \"#\", \" \", \"#\"],\r\n\t\t[\"#\", \" \", \" \", \" \", \" \", \" \", \" \", \"#\", \" \", \"#\"],\r\n\t\t[\"#\", \" \", \" \", \" \", \" \", \" \", \" \", \"#\", \" \", \"#\"],\r\n\t\t[\"#\", \" \", \" \", \" \", \" \", \" \", \" \", \"#\", \" \", \"#\"],\r\n\t\t[\"#\", \"#\", \"#\", \"#\", \"#\", \"#\", \"#\", \"#\", \" \", \"#\"]\r\n\t],\r\n\t\"solution\": [\r\n\t\t[\"*\", \" \", \"*\", \"*\", \"*\", \"*\", \"*\", \"*\", \"*\", \"*\"],\r\n\t\t[\"*\", \" \", \"*\", \"*\", \"*\", \"*\", \"*\", \"*\", \"*\", \"*\"],\r\n\t\t[\"*\", \" \", \" \", \" \", \" \", \" \", \" \", \" \", \"*\", \"*\"],\r\n\t\t[\"*\", \"*\", \"*\", \"*\", \"*\", \"*\", \"*\", \" \", \" \", \"*\"],\r\n\t\t[\"*\", \" \", \" \", \" \", \" \", \" \", \" \", \"*\", \" \", \"*\"],\r\n\t\t[\"*\", \" \", \" \", \" \", \" \", \" \", \" \", \"*\", \" \", \"*\"],\r\n\t\t[\"*\", \" \", \" \", \" \", \" \", \" \", \" \", \"*\", \" \", \"*\"],\r\n\t\t[\"*\", \" \", \" \", \" \", \" \", \" \", \" \", \"*\", \" \", \"*\"],\r\n\t\t[\"*\", \" \", \" \", \" \", \" \", \" \", \" \", \"*\", \" \", \"*\"],\r\n\t\t[\"*\", \"*\", \"*\", \"*\", \"*\", \"*\", \"*\", \"*\", \" \", \"*\"]\r\n\t]\r\n}\r\n";
	
	maze_parser::MazeMessage* fullMessage = maze_parser::jsonToMazeMessage(fullMaze);
	
	std::cout << maze_parser::mazeMessageToJson(*fullMessage) << std::endl;
}
