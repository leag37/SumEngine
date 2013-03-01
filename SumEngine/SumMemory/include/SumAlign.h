//*************************************************************************************************
// Title: SumAlign.h
// Author: Gael Huber
// Description: Tip for aligned allocation.
//
// TODO: Switch over to using SumEngine platform variables
//*************************************************************************************************
#ifndef __SUMALIGN_H__
#define __SUMALIGN_H__

#include "SumMemoryAllocator.h"

namespace SumMemory
{
	// Memory aligned malloc
	SUMINLINE static void* aligned_alloc(size_t size, SUINT alignment) {
		// Sizeof a pointer to store actual return address
		SUINT pointerSize = sizeof(SUINT*);

		// Total request size
		SUINT requestSize = size + alignment + pointerSize;

		// Allocate memory
		void* addr = MemoryAllocator::getInstancePtr()->allocate(requestSize);

		// The base return address must be at least POINTERSIZE away from the raw address
		SCHAR* base = static_cast<SCHAR*>(addr) + pointerSize;

		// The base alignment address is <alignment size> bytes forward from the base address
		base += alignment - 1;

		// The acutal aligned address is the new base & ~(align - 1) to ensure all addresses must be alligned properly
		base = reinterpret_cast<SCHAR*>(reinterpret_cast<SUINT>(base) & ~(alignment - 1));

		// Now that we have our aligned address, save the raw address
		SUINT* save = reinterpret_cast<SUINT*>(base - pointerSize);
		*save = reinterpret_cast<SUINT>(addr);

		// Return the aligned address
		return static_cast<void*>(base);
	}

	// Memory-aligned free
	SUMINLINE static void aligned_free(void* mem) {
		// Get the size of a pointer
		//SUINT pointerSize = sizeof(SUINT*);

		// Get the original address of the memory
		SUINT* saved = reinterpret_cast<SUINT*>(mem) - 1;
		void* addr = reinterpret_cast<void*>(*saved);

		// Free the address
		MemoryAllocator::getInstancePtr()->free(addr);
	}
}

#define _SUM_ALIGN(T) \
	/* Non-aligned version of new */ \
	inline void* operator new(size_t size) \
	{ \
		return SumMemory::aligned_alloc(size, __alignof(T)); \
	} \
	/* Aligned version of new */ \
	inline void* operator new (size_t size, int alignment) { \
		return SumMemory::aligned_alloc(size, alignment); \
	} \
	/* Non-aligned version of new[] */ \
	inline void* operator new[] (size_t size) { \
		return SumMemory::aligned_alloc(size, __alignof(T)); \
	} \
	/* Aligned version of new[] */ \
	inline void* operator new[] (size_t size, int alignment) { \
		return SumMemory::aligned_alloc(size, alignment); \
	} \
	/* Aligned version of delete */ \
	inline void operator delete(void* mem) { \
		SumMemory::aligned_free(mem); \
	} \
	/* Aligned version of free */ \
	inline void operator delete[] (void* mem) { \
		SumMemory::aligned_free(mem); \
	} 



#endif