#include "MazeParser.hpp"
#include "ArduinoJson.h"

// Implementations of global functions.

std::string maze_parser::mazeMessageToJson(MazeMessage &mazeMessage) {

    // Create JSON and return its string dump.
    std::string toReturn;

	StaticJsonBuffer<255555> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    JsonArray& scan = root.createNestedArray("scan");
    
    if (mazeMessage.Scan != 0) {
 
		for (int i = 0; i < mazeMessage.Scan->size(); i++){
			JsonArray& rowJson = scan.createNestedArray();
			
			for(int j = 0; j < mazeMessage.Scan->at(i)->size(); i++){
				rowJson.add(std::string(1, mazeMessage.Scan->at(i)->at(j)));
			}
		}
		
		/*
        for (vector<char> * row : *mazeMessage.Scan) {
            JsonArray& rowJson = scan.createNestedArray();

            for (char block : *row) {
                rowJson.add(std::string(1, block));
            }
        }*/
    }

	JsonArray& solution = root.createNestedArray("solution");
	
    if (mazeMessage.Solution != 0) {
		/*
        for (vector<char> * row : *mazeMessage.Solution) {
			JsonArray& rowJson = solution.createNestedArray();
			
            for (char block : *row) {
				rowJson.add(std::string(1, block));
            }
        }*/
        
        for (int i = 0; i < mazeMessage.Solution->size(); i++){
			JsonArray& rowJson = solution.createNestedArray();
			
			for(int j = 0; j < mazeMessage.Solution->at(i)->size(); i++){
				rowJson.add(std::string(1, mazeMessage.Solution->at(i)->at(j)));
			}
		}
    } 
	char buffer[255555];
	root.printTo(buffer, sizeof(buffer));
	
	return std::string(buffer);
}

maze_parser::MazeMessage * maze_parser::jsonToMazeMessage(std::string json) {
	
	vector<vector<char>*> *scanVec = new vector<vector<char>*>();
	vector<vector<char>*> *solutionVec = new vector<vector<char>*>();
	
	StaticJsonBuffer<255555> jsonBuffer;
	
	JsonObject& root = jsonBuffer.parseObject(json);
	
	JsonArray& scan = root["scan"];
	
	if (!root.success())
	{
		return 0;
	}
	
	for(int i = 0 ; i < 10 ; i++){
		// Every row
		//JsonArray& rowJson = scan[i];
		scanVec->push_back(new vector<char>());
		
		for(int j = 0 ; j < 10; j++ ){
			// every block
			std::string charAsString = scan[i][j].asString();
			//std::cout << charAsString << std::endl;
			
			if(charAsString[0] != 0){
				scanVec->at(i)->push_back(charAsString[0]);
			}
		}
	}
	
	JsonArray& solution = root["solution"];
	
	for(int i = 0 ; i < 10 ; i++){
		// Every row
		//JsonArray& rowJson = scan[i];
		solutionVec->push_back(new vector<char>());
		
		for(int j = 0 ; j < 10; j++ ){
			// every block
			std::string charAsString = solution[i][j].asString();
			//std::cout << charAsString << std::endl;
			
			if(charAsString[0] != 0){
				solutionVec->at(i)->push_back(charAsString[0]);
			}
		}
	}
	
	return new MazeMessage(scanVec, solutionVec);
}

