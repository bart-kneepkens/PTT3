#include "MotorDriver.h"

MotorDriver::MotorDriver(char* address)
	: systemAddress(address)
	{}
	
void MotorDriver::SetPolarity(char* value)
{
	MotorDriver::Write("/polarity", value);
}

int MotorDriver::GetPolarity()
{
	char buffer[256];
	MotorDriver::Read("/polarity", buffer);
	std::cout << buffer << std::endl;
}

void MotorDriver::SetPosition(int value)
{
	MotorDriver::Write("/position_sp", value);
}

int MotorDriver::GetPosition()
{
	return MotorDriver::Read("/position");
}

void MotorDriver::SetSpeed(int value)
{
	MotorDriver::Write("/speed_sp", value);
}

int MotorDriver::GetSpeed()
{
	return MotorDriver::Read("/speed");
}

void MotorDriver::Run()
{
	MotorDriver::Write("/command", "run-forever");
}

void MotorDriver::Stop()
{
	MotorDriver::Write("/command", "stop");
}

void MotorDriver::RunToRelPos()
{
	MotorDriver::Write("/command", "run-to-rel-pos");
}

void MotorDriver::Reset()
{
	MotorDriver::Write("/command", "reset");
}

void MotorDriver::Read(const char* parameterFile, char* output)
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

int MotorDriver::Read(const char* parameterFile)
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

void MotorDriver::Write(const char* parameterFile, const char* value)
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

void MotorDriver::Write(const char* parameterFile, int value)
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
