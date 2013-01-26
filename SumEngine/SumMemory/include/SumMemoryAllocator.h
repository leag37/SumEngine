//*************************************************************************************************
// Title: MemoryAllocator.h
// Author: Gael Huber
// Description: Primary instance of memory allocator.
//*************************************************************************************************
#ifndef __MEMORYALLOCATOR_H__
#define __MEMORYALLOCATOR_H__

#include "SumChunk.h"
#include "SumPlatform.h"
#include <malloc.h>
#include <climits>

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

		// Allocate a single chunk of memory
		void* allocate(size_t size);

		// Free a single chunk of memory
		void free(void* ptr);
	
	private:
		// Designated victim for allocating new chunks
		Chunk _designatedVictim;

		// Array of 32 fixed-size memory bins up to 256 bytes
		Chunk _fixedSize[32];

		// Array of 32 variable-size memory bins up to 12MB
		Chunk _variableSize[32];
	};
}

#endif