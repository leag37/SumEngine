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
#include "SumBitUtils.h"

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

	// Mark the large bin as valid
	void markLargeBin(SIZE_T index);

	// Clear the small bin map
	void clearSmallBin(SIZE_T index);

	// Clear the large bin map
	void clearLargeBin(SIZE_T index);

	// Get the small bin index for a given size
	SIZE_T getSmallBinIndex(SIZE_T size);

	// Get the large bin index for a given size
	SIZE_T getLargeBinIndex(SIZE_T size);

	// Get the small map value for a bin index
	SIZE_T getSmallMap(SIZE_T index);

	// Get the large map value for a bin index
	SIZE_T getLargeMap(SIZE_T index);

	// Find the smallest available bin of >= index
	SIZE_T findSmallestBin(SIZE_T index);

	// Unlink a small chunk at a given index
	MChunkPtr unlinkSmallChunkAt(MChunkPtr base, SIZE_T index);

	// Unlink a large chunk at a given index
	TChunkPtr MemoryState::unlinkLargeChunkAt(TChunkPtr bin, SIZE_T index);

	// Link a small chunk to a given bin
	void linkSmallChunkAt(MChunkPtr base, MChunkPtr bin, SIZE_T index);

	// Link a large chunk to a given bin
	void linkLargeChunkAt(TChunkPtr base, TChunkPtr bin, SIZE_T index);

	// Select a chunk from this tree for a given size
	void fetchLargeBinForSize(TChunkPtr base, TChunkPtr* candidate, SIZE_T size);

	SBOOL checkDvForSize(SIZE_T size);

	// Carve out a chunk and save the designated victim
	void carveChunk(MChunkPtr base, MChunkPtr* dv, SIZE_T size);

	// Replace the current DV
	void replaceDV(MChunkPtr dv, SBOOL freePrevious = true);

	// Return the designated victim
	MChunkPtr getDV();

	// Return the DV size
	SIZE_T getDVSize();

	// Unlink the designated victim from the state
	MChunkPtr unlinkDVForUse();

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