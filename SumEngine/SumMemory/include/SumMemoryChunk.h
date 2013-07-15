//*************************************************************************************************
// Title: SumMemoryChunk.h
// Author: Gael Huber
// Description: A class that defines various memory chunks
//*************************************************************************************************
#ifndef __SUMMEMORYCHUNK_H__
#define __SUMMEMORYCHUNK_H__

#include "SumMemoryDefines.h"

// Basic chunk used for small request allocations
//
// An in use chunk looks like this:
//	Chunk	+++++++++++++++++++++++++++++++
//			| Size of previous chunk
//			+++++++++++++++++++++++++++++++
//			| Size of this chunk
//	Mem		+++++++++++++++++++++++++++++++
//			| Mem
//			+++++++++++++++++++++++++++++++
// Chunk
//
// A free chunk looks like this:
// Chunk	+++++++++++++++++++++++++++++++
//			| Size of previous chunk
//			+++++++++++++++++++++++++++++++
//			| Size of this chunk
// Mem		+++++++++++++++++++++++++++++++
//			| Pointer to next chunk in list
//			+++++++++++++++++++++++++++++++
//			| Pointer to previous chunk in list
//			+++++++++++++++++++++++++++++++
//			| Unused bytes
//			+++++++++++++++++++++++++++++++
// Chunk

struct MemoryChunk
{
	// Size of the previous chunk (if it is free)
	SIZE_T prevChunk;

	// Size of this chunk/bits that are currently in use
	SIZE_T size;

	// Pointer to the next free chunk
	MemoryChunk* next;

	// Pointer to the previous memory chunk
	MemoryChunk* prev;
};

// Larger allocation request chunks. These chunks are organized in a tree fashion (but must be
// fundamentally compatible with standard chunks)
struct MemoryTreeChunk
{
	// Size of the previous chunk (if it is free)
	SIZE_T prevChunk;

	// Size of this chunk
	SIZE_T size;

	// Pointer to the next free chunk in the list
	MemoryTreeChunk* next;

	// Pointer to the previous memory chunk in the list
	MemoryTreeChunk* prev;

	// Two child nodes of this bin
	MemoryTreeChunk* child[2];

	// Parent node of this bin
	MemoryTreeChunk* parent;

	// Bin index
	SIZE_T index;
};

#endif // __SUMMEMORYCHUNK_H__