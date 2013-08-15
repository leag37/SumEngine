//*************************************************************************************************
// Title: SumMemoryChunk.h
// Author: Gael Huber
// Description: A class that defines various memory chunks
//*************************************************************************************************
#ifndef __SUMMEMORYCHUNK_H__
#define __SUMMEMORYCHUNK_H__

// size_t definitions
#define SIZE_T size_t
#define SIZE_T_ZERO ((SIZE_T)0u)
#define SIZE_T_ONE ((SIZE_T)1u)
#define SIZE_T_TWO ((SIZE_T)2u)
#define SIZE_T_FOUR ((SIZE_T)4u)
#define SIZE_T_SIZE sizeof(SIZE_T)
#define SIZE_T_BITSIZE (SIZE_T_SIZE << 3)
#define TWO_SIZE_T_SIZES (SIZE_T_SIZE << 1)
#define FOUR_SIZE_T_SIZES (SIZE_T_SIZE << 2)


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

// Alignment
#define ALLOC_ALIGNMENT ((SIZE_T)(2 * sizeof(void*)))
#define CHUNK_ALIGN_MASK (ALLOC_ALIGNMENT - SIZE_T_ONE)

// Bin definitions
#define NUM_SMALL_BINS 32u
#define NUM_LARGE_BINS 32u
#define SMALL_BIN_SHIFT 3u
#define LARGE_BIN_SHIFT 8u
#define SMALL_BIN_WIDTH (SIZE_T_ONE << SMALL_BIN_SHIFT)

// Chunk sizes and requirements
#define CHUNK_SIZE (sizeof(MemoryChunk))
#define MIN_CHUNK_SIZE ((CHUNK_SIZE + CHUNK_ALIGN_MASK) & ~CHUNK_ALIGN_MASK)

#define CHUNK_OVERHEAD TWO_SIZE_T_SIZES
#define MIN_LARGE_SIZE (SIZE_T_ONE << LARGE_BIN_SHIFT)
#define MAX_SMALL_SIZE (MIN_LARGE_SIZE - SIZE_T_ONE)
#define MAX_SMALL_REQUEST (MAX_SMALL_SIZE - CHUNK_ALIGN_MASK - CHUNK_OVERHEAD)

#define MAX_REQUEST ((-MIN_CHUNK_SIZE) << 2)

#define MIN_REQUEST (MIN_CHUNK_SIZE - CHUNK_OVERHEAD - SIZE_T_ONE)

// Other definitions
typedef void* MPtr;
typedef struct MemoryChunk MChunk;
typedef struct MemoryChunk* MChunkPtr;
typedef struct MemoryTreeChunk TChunk;
typedef struct MemoryTreeChunk* TChunkPtr;

#endif // __SUMMEMORYCHUNK_H__