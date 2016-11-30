#include "Scanner.h"

Scanner::Scanner(char* address) 
	: systemAddress(address) 
	{}
	
void Scanner::SetMode(char* mode)
{
	Scanner::Write("/mode", mode);
}

char* Scanner::GetMode()
{
	char buffer[256];
	Scanner::Read("/mode", buffer);
	return buffer;
}

int Scanner::GetValue()
{
	return Scanner::Read("/value0");
}

void Scanner::Read(const char* parameterFile, char* output)
{
	char buffer[256];
	strncpy(buffer, systemAddress, sizeof(buffer));
	strncat(buffer, parameterFile, sizeof(buffer));
	std::ifstream file;

	file.open(buffer, std::ifstream::binary);
	if (file.is_open())
	{
		file.seekg (0,file.end);
		long size = file.tellg();
		file.seekg (0);

		// allocate memory for file content
		char* buffer = new char[size];

		// read content of infile
		file.read (buffer,size);
		file.close();
		output = buffer;
	}
}

int Scanner::Read(const char* parameterFile)
{
	char buffer[256];
	int output = 0;
	strncpy(buffer, systemAddress, sizeof(buffer));
	strncat(buffer, parameterFile, sizeof(buffer));
	std::ifstream file;

	file.open(buffer, std::ifstream::binary);
	if (file.is_open())
	{
		file.seekg (0,file.end);
		long size = file.tellg();
		file.seekg (0);

		// allocate memory for file content
		char* buffer = new char[size];

		// read content of infile
		file.read (buffer,size);
		file.close();
		output = atoi(buffer);
	}
	return output;
}

void Scanner::Write(const char* parameterFile, const char* value)
{
	char buffer[256];
	strncpy(buffer, systemAddress, sizeof(buffer));
	strncat(buffer, parameterFile, sizeof(buffer));
	std::ofstream file;
	file.open(buffer);
	if (file.is_open())
	{
		file << value;
		file.close();
	}
}
