//*************************************************************************************************
// Title: SumMemory.h
// Author: Gael Huber
// Description: Entry point for allocator framework.
//*************************************************************************************************
#ifndef __SUMMEMORY_H__
#define __SUMMEMORY_H__

#include "SumUnaligned.h"
#include "SumAlign.h"

// Create the memory allocators
SUMINLINE static void CreateAllocators()
{
}

// Destroy the memory allocator
SUMINLINE static void DestroyAllocators()
{
}

// Safe deletion macro
#ifndef SafeDelete
#define SafeDelete(x) { if(x) delete x; x = 0; }
#endif

#endif