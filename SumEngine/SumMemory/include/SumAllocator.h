//*************************************************************************************************
// Title: SumAllocator.h
// Author: Gael Huber
// Description: Entry point for allocator framework.
//*************************************************************************************************
#ifndef __SUMALLOCATOR_H__
#define __SUMALLOCATOR_H__

#include "MemoryAllocator.h"

static void* operator new (size_t size)
{
	return SumMemory::MemoryAllocator::getInstancePtr()->allocate(size);
}

static void operator delete(void* ptr)
{
	SumMemory::MemoryAllocator::getInstancePtr()->free(ptr);
}

// Create the memory allocators
static void CreateAllocators()
{
}

// Destroy the memory allocator
static void DestroyAllocators()
{
}

#endif