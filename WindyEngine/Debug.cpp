#include "Debug.h"

Debug* Debug::GetInstance() {
	static Debug instance;
	return &instance;
}

void Debug::StartTimer(const size_t& timer)
{
	timers[timer] = std::chrono::steady_clock::now();
}

void Debug::EndTimer(const size_t& timer)
{
	timers[timer] = (std::chrono::steady_clock::time_point)std::chrono::duration_cast<std::chrono::milliseconds>(timers[timer] - std::chrono::steady_clock::now());
}

Debug::Debug()
{
	ofstream.open(logFileName, std::ofstream::out | std::ofstream::trunc);
}

Debug::~Debug()
{
	ofstream.close();
}
