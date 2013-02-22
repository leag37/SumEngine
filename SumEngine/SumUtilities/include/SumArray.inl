/**************************************************************************************************
* Title: SumArray.inl
* Author: Gael Huber
* Description: A standard array container with auto-resizing capabilities.
**************************************************************************************************/

/**************************************************************************************************
* Default constructor (default capacity is 4)
**************************************************************************************************/
template <typename Type>
Array<Type>::Array(void) 
	: count(0), capacity(4)
{ 
	data = new Type[4];
}

/**************************************************************************************************
* Constructor given an initial capacity
**************************************************************************************************/
template <typename Type>
Array<Type>::Array(SUINT capacity)
	: count(0), capacity(capacity)
{
	data = new Type[capacity];
}

/**************************************************************************************************
* Copy constructor
**************************************************************************************************/
template <typename Type>
Array<Type>::Array(const Array<Type>& rhs) {
	// Declare variables
	count = rhs.getCount();
	capacity = rhs.getCapacity();
	data = new Type[capacity];

	// Fill the array
	for(SUINT i = 0; i < count; ++i) {
		data[i] = rhs[i];
	}
}

/**************************************************************************************************
* Destructor
**************************************************************************************************/
template <typename Type>
Array<Type>::~Array(void) {
	delete[] data;
}

/**************************************************************************************************
* Assignment operator
**************************************************************************************************/
template <typename Type>
const Array<Type>& Array<Type>::operator=(const Array<Type>& rhs) {
	// Self-assignment prevention
	if(this == &rhs)
		return *this;
	
	// Delete any existing data if this array cannot hold the data
	if(capacity < rhs.getCapacity())
	{
		delete[] data;
		data = 0;
		capacity = rhs.getCapacity();
		data = new Type[capacity];
	}

	// Set counts and allocate new space for array
	count = rhs.getCount();

	// Populate the array
	for(SUINT i = 0; i < count; ++i) {
		data[i] = rhs[i];
	}

	return *this;
}

/**************************************************************************************************
* Equivalence operator
**************************************************************************************************/
template <typename Type>
const bool Array<Type>::operator==(const Array<Type>& rhs) const {
	// First check length
	if(count != rhs.getCount())
		return false;
	
	// Iterate through and return false if not equal
	for(SUINT i = 0; i < count; ++i) {
		if(data[i] != rhs[i])
			return false;
	}

	return true;
}

/**************************************************************************************************
* Non-equivalence operator
**************************************************************************************************/
template <typename Type>
const bool Array<Type>::operator!=(const Array<Type>& rhs) const {
	// If lengths are different, they are are not equal
	if(count != rhs.getCount())
		return true;

	// Iterate through, is anything is not equal, inequivalence is true
	for(SUINT i = 0; i < count; ++i) {
		if(data[i] != rhs[i])
			return true;
	}

	return false;
}

/**************************************************************************************************
* Pushes an element onto the front of the array
**************************************************************************************************/
template <typename Type>
void Array<Type>::push_front(const Type& val) {
	// First check whether the adding the new element will go beyond capacity
	if(count + 1 > capacity) {
		// We must increase the capacity and move everything over to that array, we will take care of
		// data shift at the same time
		capacity *= 2;
		Type* tData = new Type[capacity];

		for(SUINT i = 0; i < count; ++i) {
			tData[i + 1] = data[i];
		}

		// Delete the old array
		delete[] data;

		// Set the data equal to the new array
		data = tData;
	} else {
		// Move all data back by one
		for(SUINT i = count - 1; i != 0; --i) {
			data[i + 1] = data[i];
		}
	}

	// Add the data
	data[0] = val;

	// Increment the count
	count++;
}

/**************************************************************************************************
* Pushes an element onto the back of the array
**************************************************************************************************/
template <typename Type>
void Array<Type>::push_back(const Type& val) {
	// Check whether adding the new element will exceed the array capacity
	if(count + 1 > capacity) {
		// We must increase the capacity and move everything over to that array, we will take care of
		// data shift at the same time
		capacity *= 2;
		Type* tData = new Type[capacity];

		for(SUINT i = 0; i < count; ++i) {
			tData[i] = data[i];
		}

		// Delete the old array
		delete[] data;

		// Set the old array equal to the new array
		data = tData;
	}

	// Add the new element
	data[count++] = val;
}

/**************************************************************************************************
* Pushes a copy of an element onto the front of the array
**************************************************************************************************/
template <typename Type>
void Array<Type>::push_copy_front(const Type val) {
	// First check whether the adding the new element will go beyond capacity
	if(count + 1 > capacity) {
		// We must increase the capacity and move everything over to that array, we will take care of
		// data shift at the same time
		capacity *= 2;
		Type* tData = new Type[capacity];

		for(SUINT i = 0; i < count; ++i) {
			tData[i + 1] = data[i];
		}

		// Delete the old array
		delete[] data;

		// Set the data equal to the new array
		data = tData;
	} else {
		// Move all data back by one
		for(SUINT i = count - 1; i != 0; --i) {
			data[i + 1] = data[i];
		}
	}

	// Add the data
	data[0] = val;

	// Increment the count
	count++;
}

/**************************************************************************************************
* Pushes a copy of an element onto the back of the array
**************************************************************************************************/
template <typename Type>
void Array<Type>::push_copy_back(const Type val) {
	// Check whether adding the new element will exceed the array capacity
	if(count + 1 > capacity) {
		// We must increase the capacity and move everything over to that array, we will take care of
		// data shift at the same time
		capacity *= 2;
		Type* tData = new Type[capacity];

		for(SUINT i = 0; i < count; ++i) {
			tData[i] = data[i];
		}

		// Delete the old array
		delete[] data;

		// Set the old array equal to the new array
		data = tData;
	}

	// Add the new element
	data[count++] = val;
}

/**************************************************************************************************
* Pops an element from the front of the array
**************************************************************************************************/
template <typename Type>
const Type Array<Type>::pop_front(void) {
	// Pull the value to return
	Type toReturn = data[0];
	
	// Move everything forward
	for(SUINT i = 1; i < count; ++i) {
		data[i - 1] = data[i];
	}

	// Decrement count
	count--;

	// Return the value
	return toReturn;
}

/**************************************************************************************************
* Pops an element from the back of the array
**************************************************************************************************/
template <typename Type>
const Type Array<Type>::pop_back(void) {
	// Decremement count and return last element in array
	return data[--count];
}

/**************************************************************************************************
* Insert a piece of data at a particular index
**************************************************************************************************/
template <typename Type>
void Array<Type>::insert(const Type& val, const SUINT index) {
	// Is it even possible to insert
	assert(index < count); 

	// Check whether adding the new element will exceed the array capacity
	if(count + 1 > capacity) {
		// We must increase the capacity and move everything over to that array, we will take care of
		// data shift at the same time
		capacity *= 2;
		Type* tData = new Type[capacity];

		for(SUINT i = 0; i < count; ++i) {
			if(i < index) {
				// Standard move
				tData[i] = data[i];
			} else {
				// Shift while setting again
				tData[i + 1] = data[i];
			}
		}

		// Delete the old array
		delete[] data;

		// Set the old array equal to the new array
		data = tData;
	} else {
		// We don't need to expand the capacity of the array, so just shift everything back
		for(SUINT i = count; i >= index; --i) {
			data[i + 1] = data[i];
		}
	}

	// Add the new element
	data[index] = val;

	// Increment count
	count++;
}

/**************************************************************************************************
* Insert a copy of data at a particular index
**************************************************************************************************/
template <typename Type>
void Array<Type>::insert_copy(const Type val, const SUINT index) {
	// Is it even possible to insert
	assert(index < count); 

	// Check whether adding the new element will exceed the array capacity
	if(count + 1 > capacity) {
		// We must increase the capacity and move everything over to that array, we will take care of
		// data shift at the same time
		capacity *= 2;
		Type* tData = new Type[capacity];

		for(SUINT i = 0; i < count; ++i) {
			if(i < index) {
				// Standard move
				tData[i] = data[i];
			} else {
				// Shift while setting again
				tData[i + 1] = data[i];
			}
		}

		// Delete the old array
		delete[] data;

		// Set the old array equal to the new array
		data = tData;
	} else {
		// We don't need to expand the capacity of the array, so just shift everything back
		for(SUINT i = count; i >= index; --i) {
			data[i + 1] = data[i];
		}
	}

	// Add the new element
	data[index] = val;

	// Increment count
	count++;
}

/**************************************************************************************************
* Splice length objects from the array starting at position index
**************************************************************************************************/
template <typename Type>
void Array<Type>::splice(const SUINT index, const SUINT length) {
	// Ensure we can access the array
	assert(index < count);

	// Shift everything back by requested index
	for(SUINT i = index + length; i < count; ++i) {
		data[i - length] = data[i];
	}

	// Decrement count
	count -= length;
}

/**************************************************************************************************
* Splice the first copy data
**************************************************************************************************/
template <typename Type>
void Array<Type>::splice(const Type& val) {
	// Try to find the value
	for(SUINT i = 0; i < count; ++i) {
		// If they are equal, splice it from the array
		if(data[i] == val) {
			for(SUINT j = i; j < count; ++j) {
				data[j] = data[j + 1];
			}
			// Break out of the array
			i = count--;
		}
	}
}

/**************************************************************************************************
* Splice length objects from the array starting at the first occurence of data
**************************************************************************************************/
template <typename Type>
void Array<Type>::splice(const Type& val, const SUINT length) {
	// Try to find the value to splice
	for(SUINT i = 0; i < count; ++i) {
		// If the value is found, splice the given length
		if(data[i] == val) {
			for(SUINT j = i + length; j < count; ++j) {
				data[j - length] = data[j];
			}

			// If the length is greater than the remaining count, just set count to current value
			if(length > count - i) {
				count = i;
			} else {
				// Otherwise, decremement length from count
				count -= length;
			}
		}
	}
}

/**************************************************************************************************
* Splice all instances of data
**************************************************************************************************/
template <typename Type>
void Array<Type>::splice_all(const Type& val) {
	// Try to find the value
	for(SUINT i = 0; i < count; ++i) {
		// If they are equal, splice it from the array
		if(data[i] == val) {
			for(SUINT j = i; j < count; ++j) {
				data[j] = data[j + 1];
			}
			// Decrement count and repeat the ith value
			count--;
			i--;
		}
	}
}

/**************************************************************************************************
* Return the first index at which data is found (if not found return false)
**************************************************************************************************/
template <typename Type>
const bool Array<Type>::find(const Type& val, SUINT& index) const {
	// Try to find the value
	for(SUINT i = 0; i < count; ++i) {
		// If we find the value, set the index and return true
		if(data[i] == val) {
			index = i;
			return true;
		}
	}

	// Nothing is found, so return false
	return false;
}

/**************************************************************************************************
* Returns the item at requested array position
**************************************************************************************************/
template <typename Type>
Type& Array<Type>::operator[](const SUINT index) const {
	return data[index];
}

/**************************************************************************************************
* Returns the number of elements in the array
**************************************************************************************************/
template <typename Type>
const SUINT Array<Type>::getCount(void) const { 
	return count;
}

/**************************************************************************************************
* Returns the capacity of the array
**************************************************************************************************/
template <typename Type>
const SUINT Array<Type>::getCapacity(void) const {
	return capacity;
}

/**************************************************************************************************
* Returns an iterator pointing to the first value in the array
**************************************************************************************************/
template <typename Type>
inline typename Array<Type>::Iterator Array<Type>::begin(void) const {
	return Iterator(data);
}

/**************************************************************************************************
* Returns an iterator pointing to the ending value in the array
**************************************************************************************************/
template <typename Type>
inline typename Array<Type>::Iterator Array<Type>::end(void) const {
	return Iterator(data + count);
}

/**************************************************************************************************
* Clears the contents of the container
**************************************************************************************************/
template <typename Type>
void Array<Type>::clear(void) {
	Iterator e = end();
	for(Iterator itr = begin(); itr != e; ++itr) {
		*itr = *e;
	}
	count = 0;
}

/**************************************************************************************************
* Returns a pointer to a copy of the data as a standard array
**************************************************************************************************/
template <typename Type>
Type* Array<Type>::getPtrToCopy(void) const {
	// Initialize a new array of proper size
	Type* arr = new Type[count];

	// Copy the data
	for(int i = 0; i < count; ++i) {
		arr[i] = data[i];
	}

	// Return the new array
	return arr;
}

//*************************************************************************************************
// Resize the array to exactly fit the count
//*************************************************************************************************
template <typename Type>
void Array<Type>::resize()
{
	// Reset capacity
	capacity = count;

	// Create new space
	Type* newData = new Type[capacity];

	// Copy data
	for(SUINT i = 0; i < count; ++i) 
	{
		newData[i] = data[i];	
	}

	// Delete old data
	delete[] data;

	// Set new data
	data = newData;
}
