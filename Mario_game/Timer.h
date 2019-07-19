#pragma once
#include <SDL.h>

class Timer
{
public:

	Timer();

	void resetTimer();
	void pauseTimer();
	void startTimer();

	bool isTimerRunning();

	unsigned int updateTimer();

private:

	bool paused;
	unsigned int lastTicksValue, elapsedTime;
};