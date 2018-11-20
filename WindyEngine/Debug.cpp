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
	ifstream.open("WinLog.txt");
	while (ifstream >> num) {
		sum += num;
		count++;
	}
	ofstream << "Average: " << sum / count;
	ifstream.close();
	
	ofstream.close();
}
