#include "Timer.h"


Timer::Timer()
{
	startTicks = 0;
	pauseTicks = 0;

	paused = false, started = false;
}

Timer::~Timer()
{
}
//Start ticks
void Timer::start()
{
	started = true;
	paused = false;
	this->startTicks = SDL_GetTicks();
	this->pauseTicks = 0;
}

//Get ticks
Uint32 Timer::getTicks()
{
	Uint32 time = 0;
	if (started)
	{
		if (paused)
		{
			time = pauseTicks;
		}
		else
		{
			time = SDL_GetTicks() - this->startTicks;
		}
	}
	return time;
}