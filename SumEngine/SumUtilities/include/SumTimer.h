//*************************************************************************************************
// Title: SumTimer.h
// Author: Gael Huber
// Description: Simple game timer
//*************************************************************************************************
#ifndef __SUMTIMER_H__
#define __SUMTIMER_H__

#include "SumInclude.h"

class Timer {
public:
	// Constructor
	Timer();

	// Destructor
	~Timer();

	// Query for total time in seconds
	float totalTime() const;

	// Query for delta time in seconds
	float deltaTime() const;

	// Reset the timer
	void reset();

	// Start the timer
	void start();

	// Stop the timer
	void stop();

	// Simulate a timer tick
	void tick();

private:
	// Seconds per count
	double _secondsPerCount;

	// Current delta time
	double _deltaTime;

	// Time at timer reset
	__int64 _baseTime;

	// Time spent paused
	__int64 _pausedTime;

	// Stop time
	__int64 _stopTime;

	// Previous tick time
	__int64 _prevTime;

	// Current tick time
	__int64 _currTime;

	// Is the time currently stopped?
	bool _stopped;
};

#endif