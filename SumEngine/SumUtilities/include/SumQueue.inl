//*************************************************************************************************
// Title: SumQueue.inl
// Author: Gael Huber
// Description: Implementation of a FIFO queue
//*************************************************************************************************

//*************************************************************************************************
// Constructor
//*************************************************************************************************
template <typename Type>
SUMINLINE Queue<Type>::Queue()
	:	_data(0), _start(0), _end(0), _size(0), _maxSize(1)
{
	_data = new Type[_maxSize];
}

//*************************************************************************************************
// Constructor specifying initial size
//*************************************************************************************************
template <typename Type>
SUMINLINE Queue<Type>::Queue(SUINT maxSize)
	:	_data(0), _start(0), _end(0), _size(0), _maxSize(maxSize)
{
	// Initialize data
	_data = new Type[_maxSize];
}

//*************************************************************************************************
// Copy constructor
//*************************************************************************************************
template <typename Type>
Queue<Type>::Queue(const Queue<Type>& rhs)
	:	_start(rhs._start), _end(rhs._end), _size(rhs._size), _maxSize(rhs._maxSize)
{
	// Initialize data
	_data = new Type[_maxSize];

	// Copy the data from rhs to this
	for(SUINT i = 0; i < _maxSize; ++i)
	{
		_data[i] = rhs._data[i];
	}
}

//*************************************************************************************************
// Destructor
//*************************************************************************************************
template <typename Type>
Queue<Type>::~Queue()
{
	// Delete your data array
	SafeDeleteArray(_data);
}

//*************************************************************************************************
// Assignment operator
//*************************************************************************************************
template <typename Type>
Queue<Type>& Queue<Type>::operator=(const Queue<Type>& rhs)
{
	// Delete the array
	SafeDeleteArray(_data);

	// Copy over various data points
	_start = rhs._start;
	_end = rhs._end;
	_size = rhs._size;
	_maxSize = rhs._maxSize;

	// Create new array
	_data = new Type[_maxSize];
	for(SUINT i = 0; i < _maxSize; ++i)
	{
		_data[i] = rhs._data[i];
	}
}

//*************************************************************************************************
// Equivalence of contents (not necessarily structure)
//*************************************************************************************************
template <typename Type>
SBOOL Queue<Type>::operator==(const Queue<Type>& rhs)
{
	if(_size != rhs._size)
	{
		return false;
	}

	// TODO: ITERATOR

	return true;
}

////*************************************************************************************************
//// Non-equivalence
////*************************************************************************************************
//SBOOL operator!=(const Queue<Type>& rhs);
//
//*************************************************************************************************
// Enqueue an element
//*************************************************************************************************
template <typename Type>
void Queue<Type>::enqueue(Type elem)
{
	// First determine if we need to grow the queue
	if(_size == _maxSize)
	{
		grow();
	}

	// Increment the size of the queue
	++_size;

	// Insert the element
	_data[_end] = elem;

	// Determine a tentative insertion point
	++_end;

	// Are we wrapped around?
	if(_end == _maxSize)
	{
		_end = 0;
	}
}

//*************************************************************************************************
// Dequeue an element
//*************************************************************************************************
template <typename Type>
Type Queue<Type>::dequeue()
{
	// Save the old start and move start forward
	SUINT oldStart = _start++;

	// If start is equal to max size, wrap around
	if(_start == _maxSize)
	{
		_start = 0;
	}

	// Decrement the size
	--_size;

	// Return the dequeued value
	return _data[oldStart];
}

//*************************************************************************************************
// Clear the queue
//*************************************************************************************************
template <typename Type>
void Queue<Type>::clear()
{
	while(_size > 0)
	{
		dequeue();
	}
}

//*************************************************************************************************
// Return the size of the queue
//*************************************************************************************************
template <typename Type>
SUMINLINE SUINT Queue<Type>::size()
{
	return _size;
}

//*************************************************************************************************
// Return the max size of the queue
//*************************************************************************************************
template <typename Type>
SUMINLINE SUINT Queue<Type>::maxSize()
{
	return _maxSize;
}

//*************************************************************************************************
// Grow the queue
//*************************************************************************************************
template <typename Type>
void Queue<Type>::grow()
{
	// Increase the max size
	_maxSize *= 2;

	// Create a new array of data
	Type* newData = new Type[_maxSize];

	// Iterate through and copy over data
	SUINT currIndex = _start;
	for(SUINT index = 0; index < _size; ++index, ++currIndex)
	{
		// Roll-over
		if(currIndex == _maxSize)
		{
			currIndex = 0;
		}

		// Copy data
		newData[index] = _data[currIndex];
	}

	// Set start and end
	_start = 0;
	_end = _size - 1;

	// Copy over the data
	delete[] _data;
	_data = newData;
}


