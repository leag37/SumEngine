// Title: SumMemoryState.h
// Author: Gael Huber
// Description: Manages the chunk state for a particular section of memory
// 
// Treebins are pointers to the roots of trees holding a range of
//    sizes. There are 2 equally spaced treebins for each power of two
//    from TREE_SHIFT to TREE_SHIFT+16. The last bin holds anything
//    larger.

#ifndef __SUMMEMORYSTATE_H__
#define __SUMMEMORYSTATE_H__

#include "SumMemoryChunk.h"
#include "SumPlatform.h"

class MemoryState
{
public:
	// Constructor
	MemoryState();

	// Destructor
	~MemoryState();

	// Initialize the memory state
	void initState();

	// Get the small bin at a given index
	MChunkPtr smallBinAt(SIZE_T index);

	// Get the large bin at a given index
	TChunkPtr largeBinAt(SIZE_T index);

	// Check whether the small bin at this index is valid
	SIZE_T isSmallBinValid(SIZE_T index);

	// Check whether the large bin at this index is valid
	SIZE_T isLargeBinValid(SIZE_T index);

	// Mark the small bin as valid
	void markSmallBin(SIZE_T index);

	// Clear the small bin map
	void clearSmallBin(SIZE_T index);

	// Get the small bin index for a given size
	SIZE_T getSmallBinIndex(SIZE_T size);

	// Get the large bin index for a given size
	SIZE_T getLargeBinIndex(SIZE_T size);

	// Unlink a small chunk at a given index
	MChunkPtr unlinkSmallChunkAt(MChunkPtr chunk, SIZE_T index);

	// Link a small chunk to a given bin
	void linkSmallChunkAt(MChunkPtr base, MChunkPtr bin, SIZE_T index);

private:
	// Small bins
	MChunkPtr _sBins[(NUM_SMALL_BINS + 1) * 2];

	// Large bins
	TChunkPtr _lBins[NUM_LARGE_BINS];

	// Bit map of available small bins
	SIZE_T _sMap;

	// Bit map of available large bins
	SIZE_T _lMap;

	// Designated victim chunk
	MChunkPtr _designatedVictim;

	// Size of designated victim
	SIZE_T _dvSize;
};

#endif // __SUMMEMORYSTATE_H__