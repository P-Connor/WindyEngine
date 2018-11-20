#include "Timer.h"

Timer::Timer()
{
	timeStart = std::chrono::steady_clock::now();
}

void Timer::Reset()
{
	timeStart = std::chrono::steady_clock::now();
}

long long Timer::Value()
{
	return (std::chrono::steady_clock::now() - timeStart).count();
}
