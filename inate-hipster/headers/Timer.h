#pragma once

#include <SDL.h>
#include <stdint.h>

class Timer
{
public:
	//Initializes variables
	Timer();

	~Timer();

	//The various clock actions
	void start();
	void stop();
	void pause();
	void unpause();

	//Gets the timer's time
	unsigned int getTicks();

	//Checks the status of the timer
	bool isStarted();
	bool isPaused();

private:
	//The clock time when the timer started
	unsigned int startTicks;

	//The ticks stored when the timer was paused
	unsigned int pausedTicks;

	//The timer status
	bool paused;
	bool started;
};