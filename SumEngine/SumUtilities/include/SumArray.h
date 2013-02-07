//*************************************************************************************************
// Title: SumArray.h
// Author: Gael Huber
// Description: A standard array container with auto-resizing capabilities.
//
// TODO: Add const accessor functions
//*************************************************************************************************
#ifndef __SUMARRAY_H__
#define __SUMARRAY_H__

#include "SumInclude.h"

template <typename Type>
class Array {
public:
	// Iterator belonging to this class
	class Iterator;

public:
	Array(void);	// Default constructor (default capacity is 4)
	Array(SUINT capacity);	// Constructor given an initial capacity
	Array(const Array<Type>& rhs);	// Copy constructor
	~Array(void);	// Destructor

	const Array<Type>& operator=(const Array<Type>& rhs);	// Assignment operator
	const bool operator==(const Array<Type>& rhs) const;	// Equivalence operator
	const bool operator!=(const Array<Type>& rhs) const;	// Non-equivalence operator

	void push_front(const Type& val);	// Pushes an element onto the front of the array
	void push_back(const Type& val);	// Pushes an element onto the back of the array
	void push_copy_front(const Type val);	// Pushes a copy of an element onto the front of the array
	void push_copy_back(const Type val);	// Pushes a copy of an element onto the back of the array
	const Type pop_front(void);	// Pops an element from the front of the array
	const Type pop_back(void);		// Pops an element from the back of the array
	void insert(const Type& val, const SUINT index);	// Insert a piece of data at a particular index
	void insert_copy(const Type val, const SUINT index);	// Insert a copy of data at a particular index
	void splice(const SUINT index, const SUINT length);		// Splice length objects from the array starting at position index
	void splice(const Type& val);	// Splice the first copy data
	void splice(const Type& val, const SUINT length);		// Splice length objects from the array starting at the first occurence of data
	void splice_all(const Type& val);	// Splice all instances of data
	const bool find(const Type& val, SUINT& index) const;	// Return the first index at which data is found (if not found return false)
	Type& operator[](const SUINT index) const;	// Returns the item at requested array position
	const SUINT getCount(void) const;		// Returns the number of elements in the array
	const SUINT getCapacity(void) const;	// Returns the capacity of the array
	Iterator begin(void) const;		// Returns an iterator pointing to the first value in the array
	Iterator end(void) const;	// Returns an iterator pointing to the ending value in the array
	void clear(void);	// Clears the contents of the container
	Type* getPtrToCopy(void) const;		// Returns a pointer to a copy of the data as a standard array

private:
	Type* data;		// Contains the array of data
	SUINT count;		// Number of objects currently in the array
	SUINT capacity;	// Current capacity of the array
};

/**************************************************************************************************
* Iterator for the array
**************************************************************************************************/
template <class Type>
class Array<Type>::Iterator {
public:
	// Default constructor
	Iterator(void);

	// Constructor given pointer to element in array
	Iterator(Type* data);

	// Copy constructor
	Iterator(const Iterator& rhs);

	// Destructor
	~Iterator(void);

	// Return the data referenced
	Type& operator*(void) const;

	// Return a pointer to the class object
	Type* operator->(void) const;

	// Pre-increment
	Iterator& operator++(void);
	
	// Post-increment
	Iterator operator++(int rhs);

	// Pre-decrement
	Iterator& operator--(void);

	// Post-decrement
	Iterator operator--(int rhs);

	// Increment by integer
	Iterator& operator+=(int rhs);

	// Return this + integer
	Iterator operator+(int rhs) const;

	// Decrement by integer
	Iterator& operator-=(int rhs);

	// Return this - integer
	Iterator operator-(int rhs) const;

	// Return difference of iterators
	int operator-(const Iterator& rhs) const;

	// Return the data held
	Type& operator[](int rhs) const;

	// Equivanlence operator
	bool operator==(const Iterator& rhs) const;

	// Non-equivalence
	bool operator!=(const Iterator& rhs) const;

	// Less than operator
	bool operator<(const Iterator& rhs) const;

	// Greater than operator
	bool operator>(const Iterator& rhs) const;

	// Less than or equals operator
	bool operator<=(const Iterator& rhs) const;

	// Greater than or equals operator
	bool operator>=(const Iterator& rhs) const;

private:
	Type* data;	// Pointer to data held within the array
};

#include "SumArray.inl"
#include "SumArrayIterator.inl"

#endif