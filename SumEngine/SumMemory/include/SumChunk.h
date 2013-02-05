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
// Memory offset size for storing size of particular pointer
#define MEM_OFFSET sizeof(SUINT)

	// Struct that acts as a data pointer
	struct SUMEXPORT Chunk
	{
		SCHAR* ptr;	// Pointer to memory chunk with embedded data containing pointer to next chunk in list
		SUINT chunkSize;	// Size of this memory chunk
	
		// Default constructor
		SUMINLINE Chunk()
			: ptr(0), chunkSize(0)
		{ }

		// Copy constructor
		SUMINLINE Chunk(const Chunk& rhs)
			:	ptr(rhs.ptr), chunkSize(rhs.chunkSize)
		{ }

		// Constructor specifying data points
		SUMINLINE Chunk(SCHAR* iPtr, SUINT iChunkSize)
			: ptr(iPtr), chunkSize(iChunkSize)
		{
			if(ptr)	static_cast<SCHAR*>(ptr) = 0;
		}

		// Returns the next available chunk
		SUMINLINE void* pop()
		{
			// Get the top-most pointer
			SCHAR* n = ptr;

			// Get the pointer value of th next pointer
			SCHAR* nPtr = ptr - MEM_OFFSET;

			// Set the head to the value stored in the data segment of the old head
			ptr = reinterpret_cast<SCHAR*>(*reinterpret_cast<SUINT*>(nPtr));
			return n;
		}

		// Pushes a pointer of memory onto this stack
		SUMINLINE void push(void* iPtr)
		{
			// Get the offset position of the pointer being pushed onto the chunk
			// iPtr = 4; nPtr = 0
			// Actual pointer returned on allocation is iPtr
			void* nPtr = reinterpret_cast<void*>(reinterpret_cast<SCHAR*>(iPtr) - MEM_OFFSET);

			// Link nPtr to current pointer
			*static_cast<SUINT*>(nPtr) = reinterpret_cast<SUINT>(ptr);

			// Set ptr to iPtr, this is our new head
			ptr = reinterpret_cast<SCHAR*>(iPtr);
		}
	};
}

#endif