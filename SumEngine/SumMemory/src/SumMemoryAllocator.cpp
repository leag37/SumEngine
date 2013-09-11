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
		//return malloc(size);
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
		SUINT smallBits = _memState.getSmallMap(binIndex);

		// Check for valid remainderless bin
		if((smallBits & 0x3U) != 0)
		{
			// Since we have a valid remainderless bin, we can now proceed directly into allocating and choosing this bin
			//-------------------
			binIndex += ~smallBits & 1;

			// Get the small bin at this index
			MChunkPtr bin = _memState.smallBinAt(binIndex);

			// Unlink this chunk from the current memory list
			MChunkPtr candidate = _memState.unlinkSmallChunkAt(bin, binIndex);

			// Convert this chunk into a memory address
			return reinterpret_cast<MPtr>(candidate);
		}

		// Check for dv chunk
		if(_memState.checkDvForSize(size))
		{
			// Check whether DV is best fit or whether we need to carve from the DV
			int a = 0;
			MChunkPtr candidate = 0;
			if(_memState.getDVSize() < size + MIN_CHUNK_SIZE)
			{
				// Remainderless chunk
				candidate = _memState.unlinkDVForUse();
			}
			else
			{
				// Carve a piece out of the chunk
				candidate = _memState.getDV();
				MChunkPtr dv = 0;
				_memState.carveChunk(candidate, &dv, size);

				// Assign our new dv (as we are just overriding our previous DV, we do not want to free it
				_memState.replaceDV(dv, false);
			}

			return reinterpret_cast<MPtr>(candidate);
		}

		// Find smallest available chunk
		SIZE_T newIndex = _memState.findSmallestBin(binIndex);
		// This will never assign to bin 0
		if(newIndex > binIndex)
		{
			// Get the small bin at this index
			MChunkPtr bin = _memState.smallBinAt(newIndex);

			// Unlink this chunk from the current memory list
			MChunkPtr candidate = _memState.unlinkSmallChunkAt(bin, newIndex);

			// Now we must carve out a piece of this chunk as DV if this is not a best fit
			if(candidate->size >= size + MIN_CHUNK_SIZE)
			{
				MChunkPtr dv = 0;
				_memState.carveChunk(candidate, &dv, size);

				// Assign our new dv
				_memState.replaceDV(dv);
			}

			return reinterpret_cast<MPtr>(candidate);
		}

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
		// Get our large bin index
		//SUINT binIndex = _memState.getLargeBinIndex(size);

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
		//free(ptr);
		//return;
		//END TEMP

		// Early return on 0
		if(ptr == 0)
		{
			return;
		}

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
			int a = 0;
		}

		// Free the lock
		_criticalSection.leave();
	}
}

#pragma warning (pop)
