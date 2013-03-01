//*************************************************************************************************
// Title: SumTimer.cpp
// Author: Gael Huber
// Description: Simple game timer
//*************************************************************************************************
#include "SumTimer.h"

//*************************************************************************************************
// Constructor
//*************************************************************************************************
Timer::Timer()
	:	_secondsPerCount(0.0), _deltaTime(-1.0), _baseTime(0), _pausedTime(0), _prevTime(0),
		_currTime(0), _stopped(false)
{
	// Initialize seconds per performance counter tick
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	_secondsPerCount = 1.0 / static_cast<double>(countsPerSec);
}

//*************************************************************************************************
// Destructor
//*************************************************************************************************
Timer::~Timer()
{ }

//*************************************************************************************************
// Query for total time in seconds
//*************************************************************************************************
float Timer::totalTime() const
{
	// If we are stopped, do not count the timer that has passed since we stopped. Moreover, if we
	// previously had a pause, subtract paused time from the stopped time to ensure paused time
	// does not inadvertently get counted.
	if(_stopped) {
		return static_cast<float>(((_stopTime - _pausedTime) - _baseTime) * _secondsPerCount);
	}

	// Otherwise, return total time running
	return static_cast<float>(((_currTime - _pausedTime) - _baseTime) * _secondsPerCount);
}

//*************************************************************************************************
// Query for delta time in seconds
//*************************************************************************************************
float Timer::deltaTime() const 
{
	return static_cast<float>(_deltaTime);
}

//*************************************************************************************************
// Reset the timer
//*************************************************************************************************
void Timer::reset()
{
	// Query current time
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	// Initialize times
	_baseTime = currTime;
	_prevTime = currTime;
	_stopTime = 0;
	_stopped = false;
}

//*************************************************************************************************
// Start the timer
//*************************************************************************************************
void Timer::start()
{
	// Get current time
	__int64 startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

	// Accumlate current paused time
	if(_stopped) {
		_pausedTime += (startTime - _stopTime);
		_prevTime = startTime;
		_stopTime = 0;
		_stopped = false;
	}
}

//*************************************************************************************************
// Stop the timer
//*************************************************************************************************
void Timer::stop()
{
	// If the timer is not already stopped, query the time and mark it
	if(!_stopped) {
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		_stopTime = currTime;
		_stopped = true;
	}
}

//*************************************************************************************************
// Simulate a timer tick
//*************************************************************************************************
void Timer::tick()
{
	// If stopped, no delta time
	if(_stopped) {
		_deltaTime = 0.0;
		return;
	}

	// Otherwise, query the time
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	_currTime = currTime;

	// Time difference
	_deltaTime = (_currTime - _prevTime) * _secondsPerCount;

	// Prepare for next frame
	_prevTime = _currTime;

	// Force a non-negative value
	if(_deltaTime < 0.0) {
		_deltaTime = 0.0;
	}
}