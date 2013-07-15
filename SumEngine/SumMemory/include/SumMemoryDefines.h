//*************************************************************************************************
// Title: SumMemoryDefines.h
// Author: Gael Huber
// Description: Definitions required for proper memory allocation and various constants used to
//	make life easier.
//*************************************************************************************************
#ifndef __SUMMEMORYDEFINE_H__
#define __SUMMEMORYDEFINE_H__

// size_t definitions
#define SIZE_T size_t
#define SIZE_T_ZERO ((SIZE_T)0u)
#define SIZE_T_ONE ((SIZE_T)1u)
#define SIZE_T_TWO ((SIZE_T)2u)
#define SIZE_T_THREE ((SIZE_T)3u)
#define SIZE_T_FOUR ((SIZE_T)4u)
#define SIZE_T_SIZE sizeof(SIZE_T)
#define SIZE_T_SIZE_TWO sizeof(2u * SIZE_T_SIZE)

// Alignment
#define ALLOC_ALIGNMENT ((SIZE_T)2u * sizeof(void*))

// Chunk sizes and requirements
#define MIN_SMALL_REQUEST 8u
#define MAX_SMALL_REQUEST 256u

#define CHUNK_ALIGN_MASK 
#define CHUNK_PADDING SIZE_T_SIZE_TWO

// Bin definitions
#define NUM_SMALL_BINS 32u
#define NUM_LARGE_BINS 32u

#endif // __SUMMEMORYDEFINE_H__