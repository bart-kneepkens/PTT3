#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H

#include <fstream>
#include <string.h>
#include <iostream>
#include <cstdlib>

class MotorDriver
{
	private:
		char* systemAddress;
		void Read(const char* parameterFile, char* output);
		int Read(const char* parameterFile);
		void Write(const char* parameterFile, const char* value);
		void Write(const char* parameterFile, int value);
	public:
		MotorDriver(char* address);
		void SetPolarity(char* value);
		int GetPolarity();
		void SetPosition(int value);
		int GetPosition();
		void SetSpeed(int value);
		int GetSpeed();
		void Run();
		void Stop();
		void RunToRelPos();
		void Reset();
};

#endif
