#include <stdafx.h>
#pragma once

#ifndef __TIMER_H__
#define __TIMER_H__

class Timer
{
public:
	static void ResetTimer();
	static float TickTimer();
	static float GetDeltaTime();
	static float GetTotalTime();
};
#endif // !__TIMER_H__
