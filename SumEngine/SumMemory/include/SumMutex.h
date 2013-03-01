//*************************************************************************************************
// Title: SumMutex.h
// Author: Gael Huber
// Description: Wrapper for a mutex object
//*************************************************************************************************
#ifndef __SUMMUTEX_H__
#define __SUMMUTEX_H__

#include "SumPlatform.h"
#include <Windows.h>

class Mutex
{
public:
	// Constructor
	SUMINLINE Mutex()
	{
		_mutex = CreateMutex(NULL, FALSE, NULL);
	}

	// Destructor
	SUMINLINE ~Mutex()
	{
		WaitForSingleObject(_mutex, INFINITE);
		CloseHandle(_mutex);
	}

	// Enter the mutex
	SUMINLINE void enter()
	{
		WaitForSingleObject(_mutex, INFINITE);
	}

	// Leave the mutex
	SUMINLINE void leave()
	{
		ReleaseMutex(_mutex);
	}

private:
	// Mutex handle
	HANDLE _mutex;
};

#endif