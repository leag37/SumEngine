//*************************************************************************************************
// Title: SumAlign.h
// Author: Gael Huber
// Description: Tip for aligned allocation.
//*************************************************************************************************
#ifndef __SUMALIGN_H__
#define __SUMALIGN_H__

#include "SumMemoryAllocator.h"

namespace SumMemory
{

	// Memory aligned malloc
	static inline void* aligned_alloc(size_t size, int alignment) {
		const int pointerSize = sizeof(void*);
		const int requestedSize = size + alignment - 1 + pointerSize;
		void* raw = MemoryAllocator::getInstancePtr()->allocate(requestedSize);
		void* start = (char*) raw + pointerSize;
		void* aligned = (void*)(((unsigned int)((char*)start + alignment - 1)) & ~(alignment - 1));
		*(void**)((char*)aligned - pointerSize) = raw;
		return aligned;
	}

	// Memory-aligned free
	static inline void aligned_free(void* mem) {
		void* raw = *(void**)((char*)mem - sizeof(void*));
		MemoryAllocator::getInstancePtr()->free(raw);
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