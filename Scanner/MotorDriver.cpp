#include "MotorDriver.h"

MotorDriver::MotorDriver(std::string address)
	: systemAddress(address)
	{}
	
void MotorDriver::SetPolarity(std::string value)
{
	MotorDriver::Write("/polarity", value);
}

int MotorDriver::GetPolarity()
{
	std::string buffer;
	MotorDriver::Read("/polarity", &buffer);
	return 0;
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
	MotorDriver::Write("/stop_action", "hold");
}

std::string MotorDriver::GetState()
{
	std::string buffer;
	MotorDriver::Read("/state", &buffer);
	return buffer;
}

void MotorDriver::Read(const std::string parameterFile, std::string* output)
{
	std::string buffer;
	buffer = systemAddress + parameterFile;
	std::ifstream file(buffer.c_str());
	if (file.is_open())
	{
		// allocate memory for file content
		std::string buffer2;

		// read content of infile
		getline(file, buffer2);
		file.close();
		*output = buffer2;
	}
}

int MotorDriver::Read(const std::string parameterFile)
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

void MotorDriver::Write(const std::string parameterFile, const std::string value)
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

void MotorDriver::Write(const std::string parameterFile, int value)
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
