#include "SumMemoryState.h"

//*************************************************************************************************
// Constructor
//*************************************************************************************************
MemoryState::MemoryState()
{

}

//*************************************************************************************************
// Destructor
//*************************************************************************************************
MemoryState::~MemoryState()
{

}

//*************************************************************************************************
// Initialize the state
//*************************************************************************************************
void MemoryState::initState()
{
	// Initilize the bins
	for(SUINT i = 0; i < NUM_SMALL_BINS; ++i)
	{
		MChunkPtr bin = smallBinAt(i);

		// Set each bin to have circular references
		bin->next = bin;
		bin->prev = bin;
	}

	// Initialize binmaps
	_sMap = 0;
	_lMap = 0;
}

//*************************************************************************************************
// Get the small bin at a given index
//*************************************************************************************************
MChunkPtr MemoryState::smallBinAt(SIZE_T index)
{
	return reinterpret_cast<MChunkPtr>(&_sBins[index << 1]);
}

//*************************************************************************************************
// Get the large bin at a given index
//*************************************************************************************************
TChunkPtr MemoryState::largeBinAt(SIZE_T index)
{
	return reinterpret_cast<TChunkPtr>(&_lBins[index]);
}

//*************************************************************************************************
// Check whether the small bin at this index is valid
//*************************************************************************************************
SIZE_T MemoryState::isSmallBinValid(SIZE_T index)
{
	// Shift the bin map
	return _sMap & (1 << index);
}

//*************************************************************************************************
// Check whether the large bin at this index is valid
//*************************************************************************************************
SIZE_T MemoryState::isLargeBinValid(SIZE_T index)
{
	return 0;
}

//*************************************************************************************************
// Mark the small bin as valid
//*************************************************************************************************
void MemoryState::markSmallBin(SIZE_T index)
{
	_sMap |= (1 << index);
}

//*************************************************************************************************
// Clear the small bin map
//*************************************************************************************************
void MemoryState::clearSmallBin(SIZE_T index)
{
	_sMap &= ~(1 << index);
}

//*************************************************************************************************
// Get the small bin index for a given size
//*************************************************************************************************
SIZE_T MemoryState::getSmallBinIndex(SIZE_T size)
{
	// Shift the size by the small bin shift
	SIZE_T index = size >> SMALL_BIN_SHIFT;
	return index;
}

//*************************************************************************************************
// Get the large bin index for a given size
//*************************************************************************************************
SIZE_T MemoryState::getLargeBinIndex(SIZE_T size)
{
	return 0;
}

//*************************************************************************************************
// Unlink a small chunk at a given index
//*************************************************************************************************
MChunkPtr MemoryState::unlinkSmallChunkAt(MChunkPtr chunk, SIZE_T index)
{
	// Grab the "next" chunk pointer
	MChunkPtr next = chunk->next;

	// TODO: Unlink this chunk

	return 0;
}

//*************************************************************************************************
// Link a small chunk to a given bin
//*************************************************************************************************
void MemoryState::linkSmallChunkAt(MChunkPtr base, MChunkPtr bin, SIZE_T index)
{
	// Two options:
	// 1) List is empty -- add bin as next and prev for base
	// 2) List is not empty -- add bin as prev to base->next and next to base

	// Grab "next" bin as this is a forward insertion
	MChunkPtr next = base->next;

	// Insert forward links
	next->prev = bin;
	bin->next = next;

	// Insert backward links
	bin->prev = base;
	base->next = bin;

	// Set this bin as in use
	markSmallBin(index);
}
