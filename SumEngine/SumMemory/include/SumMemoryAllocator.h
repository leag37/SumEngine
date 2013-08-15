//*************************************************************************************************
// Title: MemoryAllocator.h
// Author: Gael Huber
// Description: Primary instance of memory allocator.
//
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
//*************************************************************************************************
#ifndef __MEMORYALLOCATOR_H__
#define __MEMORYALLOCATOR_H__

#include "SumChunk.h"
#include "SumPlatform.h"
#include "SumCriticalSection.h"
#include <malloc.h>

#include "SumMemoryChunk.h"
#include "SumMemoryState.h"

namespace SumMemory
{
	class MemoryAllocator
	{
	public:
		SUMINLINE static MemoryAllocator* getInstancePtr()
		{
			if(!SumMemory::MemoryAllocator::instance)
			{
				instance = static_cast<MemoryAllocator*>(malloc(sizeof(MemoryAllocator)));
				instance->init();
			}
			return instance;
		}

		SUMINLINE static MemoryAllocator& getInstance()
		{
			if(!instance) instance = new MemoryAllocator();
			return *instance;
		}

	private:
		// Static instance
		static MemoryAllocator* instance;

	private:
		// Constructor
		MemoryAllocator();
		
	public:
		// Destructor
		~MemoryAllocator();

		// Initialization function
		void init();

		// Aligned allocation
		MPtr alignedAlloc(SIZE_T size, SIZE_T alignment);

		// Allocate a single chunk of memory
		void* alloc(SIZE_T size);

		// Free a single chunk of memory
		void memFree(MPtr ptr);

	private:
		// Attemp a small allocation
		MPtr smallAlloc(SIZE_T size);

		// Attempt a large allocation
		MPtr largeAlloc(SIZE_T size);

		// Perform a system allocation
		MPtr sysAlloc(SIZE_T size);

		// Convert a pointer to a chunk to a memory pointer
		MPtr chunkToMem(MPtr ptr);

		// Convert a pointer to memory to a pointer to a chunk
		MChunkPtr memToChunk(MPtr ptr);
	
	private:
		// Critical section
		CriticalSection _criticalSection;

		// Memory state
		MemoryState _memState;
	};
}

#endif