//*************************************************************************************************
// Title: SumUnaligned.h
// Author: Gael Huber
// Description: Standard allocation strategy for SumEngine
//*************************************************************************************************
#ifndef __SUMUNALIGNED_H__
#define __SUMUNALIGNED_H__

#include "SumInclude.h"
#include "SumMemoryAllocator.h"

#ifdef SUMMEMORY

SUMINLINE extern void* operator new (size_t size)
{
	return SumMemory::MemoryAllocator::getInstancePtr()->allocate(size);
}

SUMINLINE extern void operator delete(void* ptr)
{
	SumMemory::MemoryAllocator::getInstancePtr()->free(ptr);
}

SUMINLINE extern void* operator new[] (size_t size) 
{
	return SumMemory::MemoryAllocator::getInstancePtr()->allocate(size);
}

SUMINLINE extern void operator delete[] (void* ptr) 
{
	SumMemory::MemoryAllocator::getInstancePtr()->free(ptr);
} 

#endif

#endif