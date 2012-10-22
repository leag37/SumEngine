//*************************************************************************************************
// Title: Chunk.h
// Author: Gael Huber
// Description: Defines a simple chunk of memory
//*************************************************************************************************
#ifndef __CHUNK_H__
#define __CHUNK_H__

#include "SumPlatform.h"
#include <assert.h>

namespace SumMemory
{
	// Struct that acts as a data pointer
	struct _SUMEXPORT Chunk
	{
		SCHAR* ptr;	// Pointer to memory chunk with embedded data containing pointer to next chunk in list
		SUINT chunkSize;	// Size of this memory chunk
	
		// Default constructor
		Chunk()
			: ptr(0), chunkSize(0)
		{ }

		// Constructor specifying data points
		Chunk(SCHAR* iPtr, SUINT iChunkSize)
			: ptr(iPtr), chunkSize(iChunkSize)
		{
			if(ptr)	static_cast<SCHAR*>(ptr) = 0;
		}

		// Returns the next available chunk
		void* pop()
		{
			SCHAR* n = ptr;
			ptr = reinterpret_cast<SCHAR*>(*ptr);
			return n;
		}

		// Pushes a pointer of memory onto this stack
		void push(void* iPtr)
		{
			void* nPtr = reinterpret_cast<void*>(reinterpret_cast<SCHAR*>(iPtr) - 4);
			*static_cast<SUINT*>(iPtr) = reinterpret_cast<SUINT>(ptr);
			ptr = reinterpret_cast<SCHAR*>(nPtr);
		}
	};
}

#endif