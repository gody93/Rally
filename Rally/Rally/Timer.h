#pragma once
#include "Globals.h"
class Timer
{
public:
	Timer();
	//Start ticks
	void start();
	//Get ticks
	Uint32 getTicks();
	~Timer();

private:
	Uint32 startTicks;
	Uint32 pauseTicks;
	
	bool paused, started;
};

