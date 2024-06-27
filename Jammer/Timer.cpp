#include "Timer.h"

#include <thread>

#include "Debug.h"
#include "Math/Math.h"

using namespace Jammer;

Timer::Timer() : timeScale(1.0f), startTime(0), previousTicks(0), currentTicks(0){}

void Timer::Start(){
	if(startTime.count() != 0){
		JLOG_WARNING("Start time has been reset");
	}

	startTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
	previousTicks = startTime;
	currentTicks = startTime;
}

void Timer::Update(){
	J_BASIC_ASSERT(startTime.count() != 0);

	previousTicks = currentTicks;
	currentTicks = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());

	//This shouldn't be a problem for about 500k years, but just in case
	if(currentTicks < previousTicks){
		JLOG_WARNING("Ticks wrapped around, setting ticks to 0");
		previousTicks = std::chrono::microseconds(0); 
	}
}

void Timer::Delay(){
	std::chrono::microseconds sleepTime = GetSleepTime();

	if(sleepTime.count() > 0){
		std::this_thread::sleep_for(sleepTime);
	}
}

std::chrono::microseconds Timer::GetSleepTime() const{
	int targetFps = 60; //TODO - Configurable
	if(targetFps == 0){
		return std::chrono::microseconds(0);
	}

	std::chrono::microseconds microSecsPerFrame = std::chrono::microseconds(1000000 / targetFps);
	if(microSecsPerFrame.count() == 0){
		std::chrono::microseconds(0);
	}

	std::chrono::microseconds updatedTicks = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());

	std::chrono::microseconds sleepTime = microSecsPerFrame - (updatedTicks - currentTicks);
	if(sleepTime > microSecsPerFrame){
		return microSecsPerFrame;
	}

	return sleepTime;
}

float Timer::DeltaTime() const{
	return Math::Clamp(0.0f, 1.0f, MicroSecondsToSeconds(currentTicks - previousTicks)) * timeScale;
}