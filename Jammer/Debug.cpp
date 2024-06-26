#include "Debug.h"

#include <iostream>

using namespace Jammer;

constexpr const char* logFileName = "log.txt";
bool gHasWrittenToFile = false;

void Debug::Log(const String& message_, const String& fileName_, int lineNumber_){
	std::cout << message_ << " [" << fileName_ << ":" << lineNumber_ << "]" << std::endl;
}

void Debug::LogWarning(const String& message_, const String& fileName_, int lineNumber_){
	std::cout << "WARNING: " << message_ << " [" << fileName_ << ":" << lineNumber_ << "]" << std::endl;
}

void Debug::LogError(const String& message_, const String& fileName_, int lineNumber_){
	std::cout << "ERROR: " << message_ << " [" << fileName_ << ":" << lineNumber_ << "]" << std::endl;
}