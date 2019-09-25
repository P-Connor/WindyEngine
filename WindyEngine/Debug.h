#pragma once
#include <fstream>
#include <string>
#include <map>
#include "Timer.h"

/*Singleton class for logging to an output file
and timing different functions. Access using "WinDebug" */
class Debug {

public:
	static Debug* GetInstance();

	template <class T>
	void Log(const T&);

private:
	Debug();
	~Debug();

	const std::string logFileName = "Windy.log";
	std::ofstream ofstream;
};

template<class T>
void Debug::Log(const T& val)
{
	ofstream << val << std::endl;
}

#define WinDebug (*Debug::GetInstance())
