#include "Timer.h"

// Initialize Timer
void timer_init()
{
	// Timing
	startPerfCount = 0;
	perfCounterFrequency = 0;
	{
		LARGE_INTEGER perfCount;
		QueryPerformanceCounter(&perfCount);
		startPerfCount = perfCount.QuadPart;
		LARGE_INTEGER perfFreq;
		QueryPerformanceFrequency(&perfFreq);
		perfCounterFrequency = perfFreq.QuadPart;
	}
	currentTimeInSeconds = 0.0;
}

// Update Timer
float timer_update()
{
	double previousTimeInSeconds = currentTimeInSeconds;
	LARGE_INTEGER perfCount;
	QueryPerformanceCounter(&perfCount);

	currentTimeInSeconds = (double)(perfCount.QuadPart - startPerfCount) / (double)perfCounterFrequency;
	
	float timer_dt = (float)(currentTimeInSeconds - previousTimeInSeconds);
	if (timer_dt > (1.f / 60.f))
		timer_dt = (1.f / 60.f);

	return timer_dt;
}
