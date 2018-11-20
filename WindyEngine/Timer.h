#pragma once
#include <chrono>

class Timer {

public:
	Timer();
	
	void ResetTimer();
	long long GetValue();

private:
	std::chrono::steady_clock::time_point timeStart;

};