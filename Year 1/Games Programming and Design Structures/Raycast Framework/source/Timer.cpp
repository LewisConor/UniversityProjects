//Precompiled Header File
#include <stdafx.h>

//Header File
#include "Timer.h"

//Static Variables
static std::chrono::time_point<std::chrono::system_clock> s_prevTime;
static float s_totalTime;
static float s_deltaTime;

//Resets the Timer
void Timer::ResetTimer()
{
	s_prevTime = std::chrono::system_clock::now();
	s_totalTime = 0.f;
	s_deltaTime = 0.f;
}

//Ticks the Timer every Frame
float Timer::TickTimer()
{
	auto currentTime = std::chrono::system_clock::now();
	std::chrono::duration<float> tStep = currentTime - s_prevTime;
	s_totalTime += s_deltaTime;
	s_deltaTime = tStep.count();
	s_prevTime = currentTime;
	return s_deltaTime;
}

//Gets the Current Delta Time
float Timer::GetDeltaTime()
{
	return s_deltaTime;
}

//Gets the Current Total Time
float Timer::GetTotalTime()
{
	return s_totalTime;
}