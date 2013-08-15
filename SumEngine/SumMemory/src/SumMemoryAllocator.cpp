#include "SumMemoryAllocator.h"

// Disable negation code for max request
#pragma warning (push)
#pragma warning( disable: 4146)

namespace SumMemory
{
	MemoryAllocator* MemoryAllocator::instance = 0;

	MemoryAllocator::MemoryAllocator()
	{ 
		_criticalSection.enter();
		_criticalSection.leave();
	}

	//************************************************************************************************
	// Initialization
	//************************************************************************************************
	void MemoryAllocator::init()
	{
		__int64 a = ALLOC_ALIGNMENT;
		__int64 b = CHUNK_ALIGN_MASK;

		// Bin definitions
		__int64 d = NUM_SMALL_BINS;
		__int64 e = NUM_LARGE_BINS;
		__int64 f = SMALL_BIN_SHIFT;
		__int64 g = LARGE_BIN_SHIFT;
		__int64 h = SMALL_BIN_WIDTH;

		// Chunk sizes and requirements
		__int64 i = CHUNK_SIZE;
		__int64 j = MIN_CHUNK_SIZE;

		__int64 k = CHUNK_OVERHEAD;
		__int64 l = MIN_LARGE_SIZE;
		__int64 m = MAX_SMALL_SIZE;
		__int64 n = MAX_SMALL_REQUEST;

		__int64 o = MAX_REQUEST;
		__int64 p = MIN_REQUEST;
		unsigned int q = MIN_CHUNK_SIZE;
		unsigned int r = -MIN_CHUNK_SIZE;
		unsigned int s = r << 2;
		unsigned int t = q << 2;
		unsigned int u = ~q;
		unsigned int v = 0 - q;
		unsigned int w = 1 - q;

		// Initialize critical section
		_criticalSection = CriticalSection();

		// Initialize the memory state
		_memState.initState();
	}

	//************************************************************************************************
	// Basic algorithm:
	//     If a small request (< 256 bytes minus per-chunk overhead):
	//       1. If one exists, use a remainderless chunk in associated smallbin.
	//          (Remainderless means that there are too few excess bytes to
	//          represent as a chunk.)
	//       2. If it is big enough, use the dv chunk, which is normally the
	//          chunk adjacent to the one used for the most recent small request.
	//       3. If one exists, split the smallest available chunk in a bin,
	//          saving remainder in dv.
	//       4. If it is big enough, use the top chunk.
	//       5. If available, get memory from system and use it
	//     Otherwise, for a large request:
	//       1. Find the smallest available binned chunk that fits, and use it
	//          if it is better fitting than dv chunk, splitting if necessary.
	//       2. If better fitting than any binned chunk, use the dv chunk.
	//       3. If it is big enough, use the top chunk.
	//       4. If request size >= mmap threshold, try to directly mmap this chunk.
	//       5. If available, get memory from system and use it
	//************************************************************************************************
	MPtr MemoryAllocator::alloc(SIZE_T size)
	{
		//TEMP
		return malloc(size);
		//END TEMP

		// The final allocated address
		MPtr allocAddress = 0;

		// The first thing we must do is lock the shared resources
		_criticalSection.enter();

		// Check for a small request
		if(size < MAX_SMALL_REQUEST)
		{
			// Pad the requested size to find the needed chunk size for this request
			SIZE_T paddedSize = (size < MIN_REQUEST) ? MIN_CHUNK_SIZE : size + CHUNK_OVERHEAD;

			// Process as a small request
			allocAddress = smallAlloc(paddedSize);
		}
		// Check for a large request
		else if(size < MAX_REQUEST)
		{
			SIZE_T paddedSize = size + CHUNK_OVERHEAD;

			allocAddress = largeAlloc(paddedSize);
		}
		else
		{
			// ERROR
		}

		// Final processing on the chunk
		MPtr finalAddress = chunkToMem(allocAddress);
		
		// Leave the critical section
		_criticalSection.leave();

		// Return the allocated address
		return finalAddress;
	}

	//************************************************************************************************
	// Allocate a small amount of space
	// If a small request (< 256 bytes minus per-chunk overhead):
	//   1. If one exists, use a remainderless chunk in associated smallbin. (Remainderless means that
	//		there are too few excess bytes to represent as a chunk.)
	//   2. If it is big enough, use the dv chunk, which is normally the chunk adjacent to the one 
	//		used for the most recent small request.
	//   3. If one exists, split the smallest available chunk in a bin, saving remainder in dv.
	//   4. If it is big enough, use the top chunk.
	//   5. If available, get memory from system and use it
	//************************************************************************************************
	MPtr MemoryAllocator::smallAlloc(SIZE_T size)
	{
		// Get the bin for this size
		SUINT binIndex = _memState.getSmallBinIndex(size);

		// Check for valid remainderless bin
		if(_memState.isSmallBinValid(binIndex))
		{
			// Since we have a valid remainderless bin, we can now proceed directly into allocating and choosing this bin
			//-------------------

			// Get the small bin at this index
			MChunkPtr bin = _memState.smallBinAt(binIndex);

			// Unlink this chunk from the current memory list
			MChunkPtr candidate = _memState.unlinkSmallChunkAt(bin, binIndex);

			// Convert this chunk into a memory address
			return reinterpret_cast<MPtr>(bin);
		}

		// Check for dv chunk

		// Find smallest available chunk

		// Perform a system allocation
		return sysAlloc(size);
	}

	//************************************************************************************************
	// Allocate a large amount of space
	// Otherwise, for a large request:
	//   1. Find the smallest available binned chunk that fits, and use it if it is better fitting 
	//		than dv chunk, splitting if necessary.
	//   2. If better fitting than any binned chunk, use the dv chunk.
	//   3. If it is big enough, use the top chunk.
	//   4. If request size >= mmap threshold, try to directly mmap this chunk.
	//   5. If available, get memory from system and use it
	//************************************************************************************************
	MPtr MemoryAllocator::largeAlloc(SIZE_T size)
	{
		// Perform a system allocation
		return sysAlloc(size);
	}

	//************************************************************************************************
	// Perform a system allocation
	//************************************************************************************************
	MPtr MemoryAllocator::sysAlloc(SIZE_T size)
	{
		// Allocate a chunk of given size (overhead already included at this stage)
		MPtr mem = malloc(size);

		// Convert to a chunk
		MChunkPtr bin = reinterpret_cast<MChunkPtr>(mem);
		bin->size = size;

		return mem;
	}

	//************************************************************************************************
	// Convert a pointer to a chunk to a memory pointer
	//************************************************************************************************
	MPtr MemoryAllocator::chunkToMem(MPtr ptr)
	{
		return reinterpret_cast<MPtr>(reinterpret_cast<SCHAR*>(ptr) + TWO_SIZE_T_SIZES);
	}

	//************************************************************************************************
	// Convert a pointer to memory to a pointer to a chunk
	//************************************************************************************************
	MChunkPtr MemoryAllocator::memToChunk(MPtr ptr)
	{
		return reinterpret_cast<MChunkPtr>(reinterpret_cast<SCHAR*>(ptr) - TWO_SIZE_T_SIZES);
	}

	//************************************************************************************************
	// Free a given chunk of memory.
	// Ideally, this will also consolidate all memory chunks to maintain the least amount of memory
	//	fragmentation possible.
	//************************************************************************************************
	void MemoryAllocator::memFree(MPtr ptr)
	{
		//TEMP
		free(ptr);
		return;
		//END TEMP

		// Convert this address to a memory chunk
		MChunkPtr bin = memToChunk(ptr);

		// Acquire lock
		_criticalSection.enter();

		// Assess whether we want to add this to a small bin or a large bin
		if(bin->size < MAX_SMALL_SIZE)
		{
			// Find the appropriate bin
			SUINT binIndex = _memState.getSmallBinIndex(bin->size);

			// Now we must append this to the appropriate small bin
			MChunkPtr candidate = _memState.smallBinAt(binIndex);

			// Now that we have the "head" bin for this small index, we must pin the new bin to the 
			// candidate small bin
			_memState.linkSmallChunkAt(candidate, bin, binIndex);
		}
		else
		{
			// Large bin
		}

		// Free the lock
		_criticalSection.leave();
	}
}

#pragma warning (pop)
