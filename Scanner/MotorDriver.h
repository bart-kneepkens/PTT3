#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H

#include <fstream>
#include <string>
#include <string.h>
#include <iostream>
#include <cstdlib>

class MotorDriver
{
	private:
		std::string systemAddress;
		void Read(const std::string parameterFile, std::string* output);
		int Read(const std::string parameterFile);
		void Write(const std::string parameterFile, const std::string value);
		void Write(const std::string parameterFile, int value);
	public:
		MotorDriver(std::string address);
		void SetPolarity(std::string value);
		int GetPolarity();
		void SetPosition(int value);
		int GetPosition();
		void SetSpeed(int value);
		int GetSpeed();
		void Run();
		void Stop();
		void RunToRelPos();
		void Reset();
		std::string GetState();
};

#endif
