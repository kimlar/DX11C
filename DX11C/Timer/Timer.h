#pragma once
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>


LONGLONG startPerfCount;
LONGLONG perfCounterFrequency;
double currentTimeInSeconds;

// Initialize Timer
void timer_init();
float timer_update();
