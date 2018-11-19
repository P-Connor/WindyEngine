#pragma once
#include <fstream>
#include <string>
#include <chrono>

/*Singleton class for logging to an output file
and timing different functions. Access using "WinLog" */
class Debug {

public:
	static Debug* GetInstance();

	template <class T>
	void Log(const T&);

	//Initializes a timer at a specified index from 0-9
	void StartTimer(const size_t&);
	//Ends a timer at a specified index from 0-9
	void EndTimer(const size_t&);

private:
	Debug();
	~Debug();

	const std::string logFileName = "WinLog.txt";
	std::ofstream ofstream;

	std::chrono::steady_clock::time_point timers[10];
};

template<class T>
void Debug::Log(const T& val)
{
	ofstream << ": " << val << std::endl;
}

#define WinLog (*Debug::GetInstance())
