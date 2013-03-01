//*************************************************************************************************
// Title: SumCriticalSection.h
// Author: Gael Huber
// Description: Represents a critical section used in synchronization.
//*************************************************************************************************
#ifndef __SUMCRITICALSECTION_H__
#define __SUMCRITICALSECTION_H__

#include "SumPlatform.h"
#include <Windows.h>

class CriticalSection {
public:
	// Constructor
	SUMINLINE CriticalSection(void) 
	{
		InitializeCriticalSectionAndSpinCount(&criticalSection, 0x00000400);
	}

	// Constructor
	SUMINLINE CriticalSection(DWORD spinCount)
	{
		InitializeCriticalSectionAndSpinCount(&criticalSection, spinCount);
	}

	// Destructor
	SUMINLINE ~CriticalSection(void)
	{
		DeleteCriticalSection(&criticalSection);
	}

	// Enter the critical section
	SUMINLINE void enter(void)
	{
		EnterCriticalSection(&criticalSection);
	}

	// Leave the critical section
	SUMINLINE void leave(void)
	{
		LeaveCriticalSection(&criticalSection);
	}

private:
	CRITICAL_SECTION criticalSection;	// Object representing the critical section. This is part of windows header.
};

#endif