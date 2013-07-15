// Title: SumMemoryState.h
// Author: Gael Huber
// Description: Manages the chunk state for a particular section of memory

#ifndef __SUMMEMORYSTATE_H__
#define __SUMMEMORYSTATE_H__

#include "SumMemoryDefines.h"
#include "SumMemoryChunk.h"

class MemoryState
{
public:
	// Constructor
	MemoryState();

	// Destructor
	~MemoryState();

private:
	// Small bins
	MemoryChunk* _sBins[NUM_SMALL_BINS];

	// Large bins
	MemoryTreeChunk* _lBins[NUM_LARGE_BINS];

	// Bit map of available small bins
	SIZE_T _sMap;

	// Bit map of available large bins
	SIZE_T _lMap;

	// Designated victim chunk
	MemoryChunk* _designatedVictim;

	// Size of designated victim
	SIZE_T _dvSize;
};

#endif // __SUMMEMORYSTATE_H__