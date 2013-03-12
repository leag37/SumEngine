//*************************************************************************************************
// Title: SumQueue.h
// Author: Gael Huber
// Description: Implementation of a FIFO queue
//
// TODO: Implement an iterator and a const iterator
//*************************************************************************************************
#ifndef __SUMQUEUE_H__
#define __SUMQUEUE_H__

#include "SumInclude.h"

template <typename Type>
class Queue
{
public:
	// Constructor
	Queue();

	// Constructor specifying initial size
	Queue(SUINT maxSize);

	// Copy constructor
	Queue(const Queue<Type>& rhs);

	// Destructor
	~Queue();

	// Assignment operator
	Queue<Type>& operator=(const Queue<Type>& rhs);

	// Equivalence
	SBOOL operator==(const Queue<Type>& rhs);

	// Non-equivalence
	SBOOL operator!=(const Queue<Type>& rhs);

	// Enqueue an element
	void enqueue(Type elem);

	// Dequeue an element
	Type dequeue();

	// Clear the queue
	void clear();

	// Return the size of the queue
	SUINT size();

	// Return the size of the queue
	const SUINT size() const;

	// Return the max size of the queue
	SUINT maxSize();

private:
	// Grow the queue
	void grow();

private:
	// Array of elements
	Type* _data;

	// Start index
	SUINT _head;

	// End index
	SUINT _tail;

	// Size of the queue
	SUINT _size;

	// Max size of the queue
	SUINT _maxSize;

	// Array length is always _maxSize + 1
	SUINT _arrLength;
};

#include "SumQueue.inl"

#endif