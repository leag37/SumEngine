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

	for(SUINT i = 0; i < NUM_LARGE_BINS; ++i)
	{
		TChunkPtr* bin = reinterpret_cast<TChunkPtr*>(largeBinAt(i));

		// Set circular reference of each bin
		*bin = 0;
	}

	// Initialize binmaps
	_sMap = 0;
	_lMap = 0;

	// Initialize designated victim
	_designatedVictim = 0;
	_dvSize = 0;
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
	return _lMap & (1 << index);
}

//*************************************************************************************************
// Mark the small bin as valid
//*************************************************************************************************
void MemoryState::markSmallBin(SIZE_T index)
{
	_sMap |= (1 << index);
}

//*************************************************************************************************
// Mark the large bin as valid
//*************************************************************************************************
void MemoryState::markLargeBin(SIZE_T index)
{
	_lMap |= (1 << index);
}

//*************************************************************************************************
// Clear the small bin map
//*************************************************************************************************
void MemoryState::clearSmallBin(SIZE_T index)
{
	_sMap &= ~(1 << index);
}

//*************************************************************************************************
// Clear the large bin map
//*************************************************************************************************
void MemoryState::clearLargeBin(SIZE_T index)
{
	_lMap &= ~(1 << index);
}

//*************************************************************************************************
// Get the small map value for a bin index
//*************************************************************************************************
SIZE_T MemoryState::getSmallMap(SIZE_T index)
{
	return _sMap >> index;
}

//*************************************************************************************************
// Get the large map value for a bin index
//*************************************************************************************************
SIZE_T MemoryState::getLargeMap(SIZE_T index)
{
	return _lMap >> index;
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
	// Find the bin shift
	SIZE_T shiftVal = size >> LARGE_BIN_SHIFT;
	SIZE_T index = 0;
	if(shiftVal == 0)
	{
		index = 0;
	}
	else if(shiftVal > 0xFFFF)
	{
		index = NUM_LARGE_BINS - 1;
	}
	else
	{
		SUINT k;
		ReverseBitScan(&k, shiftVal);
		index = (SIZE_T)((k << 1) + ((size >> (k + (LARGE_BIN_SHIFT - 1)) & 1)));
	}
	return index;
}

//*************************************************************************************************
// Find the smallest available bin of >= index
//*************************************************************************************************
SIZE_T MemoryState::findSmallestBin(SIZE_T index)
{
	// Shift the map over to run ctz on minimum set
	SIZE_T map = _sMap >> index;

	// Run ctz and re-increment to find absolute index
	SIZE_T bit = 0;
	ForwardBitScan(&bit, map);
	bit += index;
	return bit;
}

//*************************************************************************************************
// Unlink a small chunk at a given index
//*************************************************************************************************
MChunkPtr MemoryState::unlinkSmallChunkAt(MChunkPtr base, SIZE_T index)
{
	// Grab the "next" chunk pointer
	MChunkPtr candidate = base->next;

	// Remove candidate
	MChunkPtr next = candidate->next;
	base->next = next;
	next->prev = base;

	// Check for clearing in use marker
	if(base == next)
	{
		clearSmallBin(index);
	}

	// We have successfully chosen our candidate, return for further processing
	return candidate;
}

//*************************************************************************************************
// Unlink a large chunk at a given index
//*************************************************************************************************
TChunkPtr MemoryState::unlinkLargeChunkAt(TChunkPtr bin, SIZE_T index)
{
	TChunkPtr candidate = bin;

	// Check for parentage

	return candidate;
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

	// Link bin to base and next
	bin->prev = base;
	bin->next = next;

	// Link base and next to bin
	base->next = bin;
	next->prev = bin;

	// Set this bin as in use
	markSmallBin(index);
}

//*************************************************************************************************
// Link a large chunk to a given bin
//*************************************************************************************************
void MemoryState::linkLargeChunkAt(TChunkPtr base, TChunkPtr bin, SIZE_T index)
{
	// Find our head
	TChunkPtr head = base;
	TChunkPtr node = 0;

	// Initialize bin
	bin->next = 0;
	bin->prev = 0;
	bin->child[0] = 0;
	bin->child[1] = 0;
	bin->parent = 0;

	// If head is valid, we are good to go
	if(head == 0)
	{
		// Empty tree, insert new head value
		base = bin;
	}
	else
	{
		// Tree is populated with at least one value, find point of insertion
		for(;;)
		{
			// Insertion node is less, go left
			if(bin->size < head->size)
			{
				if(head->child[0] == 0)
				{
					// New child
					head->child[0] = bin;
					bin->parent = head;
					break;
				}

				// Insert into next node
				head = head->child[0];
			}
			else if(bin->size > head->size)
			{
				if(head->child[1] == 0)
				{
					// New child
					head->child[1] = bin;
					bin->parent = head;
					break;
				}

				// Search next node if we did not insert as a new child
				head = head->child[1];
			}
			else 
			{
				// Equivalent node, insert as next value
				TChunkPtr next = head->next; 

				// Link bin
				bin->prev = head;
				bin->next = next;

				// Link head and next
				head->next = bin;
				next->prev = bin;
			}
		}
	}

	// Set bin as in use
	markLargeBin(index);
}

//*************************************************************************************************
// Select a chunk from this tree for a given size
//*************************************************************************************************
void MemoryState::fetchLargeBinForSize(TChunkPtr base, TChunkPtr* candidate, SIZE_T size)
{
	// Assign the head of this branch
	TChunkPtr head = base;
	
	// Find smallest available child of head
	for(;;)
	{
		// Check left
		if(head->child[0] != 0 && size < head->size)
		{
			head = head->child[0];
		}
		// Check right
		else if(head->child[1] != 0 && size > head->size)
		{
			head = head->child[1];
		}
		// Check self
		else
		{
			*candidate = head;
			break;
		}
	}
}

//*************************************************************************************************
// Check whether  value will fit into the DV
//*************************************************************************************************
SBOOL MemoryState::checkDvForSize(SIZE_T size)
{
	return size <= _dvSize;
}

//*************************************************************************************************
// Carve out a chunk and save the designated victim
//*************************************************************************************************
void MemoryState::carveChunk(MChunkPtr base, MChunkPtr* dv, SIZE_T size)
{
	// Carve portion out of candidate chunk
	SCHAR* cdv = reinterpret_cast<SCHAR*>(base);
	SCHAR* newMem = cdv + size;
	*dv = reinterpret_cast<MChunkPtr>(newMem);
	(*dv)->size = base->size - size;
	base->size = size;
}

//*************************************************************************************************
// Replace the current DV
//*************************************************************************************************
void MemoryState::replaceDV(MChunkPtr dv, SBOOL freePrevious)
{
	if(_designatedVictim != 0 && freePrevious == true)
	{
		SIZE_T dvIndex = getSmallBinIndex(_dvSize);
		MChunkPtr bin = smallBinAt(dvIndex);
		linkSmallChunkAt(bin, _designatedVictim, dvIndex);
	}

	_designatedVictim = dv;
	_dvSize = dv->size;
}

//*************************************************************************************************
// Return the designated victim
//*************************************************************************************************
MChunkPtr MemoryState::getDV()
{
	return _designatedVictim;
}

//*************************************************************************************************
// Return the DV size
//*************************************************************************************************
SIZE_T MemoryState::getDVSize()
{
	return _dvSize;
}

//*************************************************************************************************
// Unlink the designated victim from the state
//*************************************************************************************************
MChunkPtr MemoryState::unlinkDVForUse()
{
	MChunkPtr chunk = _designatedVictim;

	_designatedVictim = 0;
	_dvSize = 0;

	return chunk;
}
