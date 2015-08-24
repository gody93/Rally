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

void Timer::start()
{
	started = true;
	paused = false;
	startTicks = SDL_GetTicks();
	pauseTicks = 0;
}

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
			time = SDL_GetTicks() - startTicks;
		}
	}
	return time;
}