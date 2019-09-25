#include "Debug.h"

Debug* Debug::GetInstance() {
	static Debug instance;
	return &instance;
}

Debug::Debug()
{
	ofstream.open(logFileName, std::ofstream::out | std::ofstream::trunc);
}

Debug::~Debug()
{
	long long sum = 0, count = 0, num;
	std::ifstream ifstream;
	ifstream.open(logFileName);
	while (ifstream >> num) {
		sum += num;
		count++;
	}
	ofstream << "Average: " << (double)sum / count;
	ifstream.close();
	
	ofstream.close();
}
