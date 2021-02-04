#pragma once
#include <chrono>

class Timer {

public:
	Timer();
	
	void Reset();
	const long long& Value();

private:
	std::chrono::steady_clock::time_point timeStart;

};