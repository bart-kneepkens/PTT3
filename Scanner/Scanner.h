#ifndef SCANNER_H
#define SCANNER_H

#include <fstream>
#include <string>
#include <string.h>
#include <iostream>
#include <cstdlib>

class Scanner
{
	private:
		std::string systemAddress;
		void Read(const std::string parameterFile, const std::string output);
		int Read(const std::string parameterFile);
		void Write(const std::string parameterFile, const std::string value);
		
	public:
		Scanner(std::string address);
		void SetMode(std::string mode);
		std::string GetMode();
		int GetValue();
};

#endif
