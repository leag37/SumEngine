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
	:	_data(0), _head(0), _tail(0), _size(0), _maxSize(1), _arrLength(2)
{
	_data = new Type[_arrLength];
}

//*************************************************************************************************
// Constructor specifying initial size
//*************************************************************************************************
template <typename Type>
SUMINLINE Queue<Type>::Queue(SUINT maxSize)
	:	_data(0), _head(0), _tail(0), _size(0), _maxSize(maxSize), _arrLength(maxSize + 1)
{
	// Initialize data
	_data = new Type[_arrLength];
}

//*************************************************************************************************
// Copy constructor
//*************************************************************************************************
template <typename Type>
Queue<Type>::Queue(const Queue<Type>& rhs)
	:	_head(rhs._head), _tail(rhs._tail), _size(rhs._size), _maxSize(rhs._maxSize), 
		_arrLength(rhs._arrLength)
{
	//// Initialize data
	//_data = new Type[_maxSize];

	//// Copy the data from rhs to this
	//for(SUINT i = 0; i < _maxSize; ++i)
	//{
	//	_data[i] = rhs._data[i];
	//}
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
	_head = rhs._head;
	_tail = rhs._tail;
	_size = rhs._size;
	_maxSize = rhs._maxSize;
	_arrLength = rhs._arrLength;

	// Create new array
	_data = new Type[_arrLength];
	SUINT i = rhs._head;
	while(i != _tail)
	{
		_data[i] = rhs._data[i];

		if(i == _maxSize)
		{
			i = 0;
		}
		else
		{
			++i;
		}
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

	// Walk through both queues
	SUINT i = rhs._head;
	while(i != _tail)
	{
		if(_data[i] != rhs._data[i])
		{
			return false;
		}

		if(i == _maxSize)
		{
			i = 0;
		}
		else
		{
			++i;
		}
	}

	return true;
}

//*************************************************************************************************
// Non-equivalence
//*************************************************************************************************
template <typename Type>
SBOOL Queue<Type>::operator!=(const Queue<Type>& rhs)
{
	SUINT i = rhs._head;
	while(i != _tail)
	{
		if(_data[i] != rhs._data[i])
		{
			return true;
		}

		if(i == _maxSize)
		{
			i = 0;
		}
		else
		{
			++i;
		}
	}

	return false;
}

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

	// Insert the element at the tail of the queue
	_data[_tail] = elem;

	// Handle wrap-around
	if(_tail == _maxSize)
	{
		_tail = 0;
	}
	else
	{
		++_tail;
	}

	// Increment the queue size
	++_size;
}

//*************************************************************************************************
// Dequeue an element
//*************************************************************************************************
template <typename Type>
Type Queue<Type>::dequeue()
{
	// Save return value
	Type ret = _data[_head];

	// Handle wrap-around
	if(_head == _maxSize)
	{
		_head = 0;
	}
	else
	{
		++_head;
	}

	// Decrease size
	--_size;
	
	// Return value
	return ret;
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
// Return the size of the queue
//*************************************************************************************************
template <typename Type>
SUMINLINE const SUINT Queue<Type>::size() const
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
	SUINT prevMax = _maxSize;
	_maxSize *= 2;
	_arrLength = _maxSize + 1;

	// Create a new array of data
	Type* newData = new Type[_arrLength];

	// Iterate through and copy over data
	SUINT currIndex = _head;
	for(SUINT index = 0; index < _size; ++index)
	{
		// Copy data
		newData[index] = _data[currIndex];

		// Roll-over
		if(currIndex == prevMax)
		{
			currIndex = 0;
		}
		else
		{
			++currIndex;
		}
	}

	// Set start and end
	_head = 0;
	_tail = _size;

	// Copy over the data
	delete[] _data;
	_data = newData;
}


