#include "Timer.h"

Timer::Timer()
{
	resetTimer();
}

void Timer::resetTimer()
{

	lastTicksValue = SDL_GetTicks();
	paused = true;

}

unsigned int Timer::updateTimer()
{
	if(!paused) elapsedTime = (SDL_GetTicks() - lastTicksValue);
	return elapsedTime;
}

void Timer::pauseTimer()
{
	paused = true;
}

void Timer::startTimer()
{
	paused = false;
}

bool Timer::isTimerRunning()
{
	return !paused;
}
