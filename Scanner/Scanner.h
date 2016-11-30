#ifndef SCANNER_H
#define SCANNER_H

#include <fstream>
#include <string.h>
#include <iostream>
#include <cstdlib>

class Scanner
{
	private:
		char* systemAddress;
		void Read(const char* parameterFile, char* output);
		int Read(const char* parameterFile);
		void Write(const char* parameterFile, const char* value);
		
	public:
		Scanner(char* address);
		void SetMode(char* mode);
		char* GetMode();
		int GetValue();
};

#endif
