#include "Timer.h"

Timer::Timer()
{
	timeStart = std::chrono::steady_clock::now();
}

void Timer::ResetTimer()
{
	timeStart = std::chrono::steady_clock::now();
}

long long Timer::GetValue()
{
	return (std::chrono::steady_clock::now() - timeStart).count();
}
