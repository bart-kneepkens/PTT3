#include "Scanner.h"

Scanner::Scanner(std::string address) 
	: systemAddress(address) 
	{}
	
void Scanner::SetMode(std::string mode)
{
	Scanner::Write("/mode", mode);
}

std::string Scanner::GetMode()
{
	std::string buffer;
	Scanner::Read("/mode", buffer);
	return buffer;
}

int Scanner::GetValue()
{
	return Scanner::Read("/value0");
}

void Scanner::Read(const std::string parameterFile, std::string output)
{
	std::string buffer;
	buffer = systemAddress + parameterFile;
	std::ifstream file(buffer.c_str());
	if (file.is_open())
	{
		// allocate memory for file content
		std::string buffer2;

		// read content of infile
		getline(file, buffer);
		file.close();
		output = buffer;
	}
}

int Scanner::Read(const std::string parameterFile)
{
	std::string buffer;
	int output = 0;
	buffer = systemAddress + parameterFile;
	std::ifstream file(buffer.c_str());
	if (file.is_open())
	{
		// allocate memory for file content
		std::string buffer2;

		// read content of infile
		getline(file, buffer2);
		file.close();
		output = atoi(buffer2.c_str());
	}
	return output;
}

void Scanner::Write(const std::string parameterFile, const std::string value)
{
	std::string buffer;
	buffer = systemAddress + parameterFile;
	std::ofstream file(buffer.c_str());
	if (file.is_open())
	{
		file << value;
		file.close();
	}
}
