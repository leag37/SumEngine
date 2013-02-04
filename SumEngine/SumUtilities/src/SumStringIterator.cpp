/**************************************************************************************************
* Title: SumStringIterator.cpp
* Author:
* Description: Iterator for string object
**************************************************************************************************/
#include "SumString.h"

/**************************************************************************************************
* Default constructor
**************************************************************************************************/
String::Iterator::Iterator(void) 
	: c(0)
{ }

/**************************************************************************************************
* Constructor that binds the character it points to
**************************************************************************************************/
String::Iterator::Iterator(char* ch) 
	: c(ch)
{ }

/**************************************************************************************************
* Copy-constructor
**************************************************************************************************/
String::Iterator::Iterator(const Iterator& rhs) 
	: c(reinterpret_cast<char*>(reinterpret_cast<unsigned int>(&*rhs)))
{ }

/**************************************************************************************************
* Destructor
**************************************************************************************************/
String::Iterator::~Iterator(void) {
	c = 0;
}

/**************************************************************************************************
* Assignment
**************************************************************************************************/
const String::Iterator& String::Iterator::operator=(const Iterator& rhs) {
	// Self-assignment guard
	if(&rhs == this) {
		return *this;
	}

	// Assign value of iterator and return
	c = reinterpret_cast<char*>(reinterpret_cast<unsigned int>(&*rhs));
	return *this;
}

/**************************************************************************************************
* Equivalence
**************************************************************************************************/
const bool String::Iterator::operator==(const Iterator& rhs) const {
	return (**this == *rhs);
}

/**************************************************************************************************
* Non-equivalence
**************************************************************************************************/
const bool String::Iterator::operator!=(const Iterator& rhs) const {
	return !(**this == *rhs);
}

/**************************************************************************************************
* Pre-increment
**************************************************************************************************/
const String::Iterator& String::Iterator::operator++(void) {
	// Increment the pointer and return this
	++c;
	return *this;
}

/**************************************************************************************************
* Post-increment
**************************************************************************************************/
const String::Iterator String::Iterator::operator++(int rhs) {
	// Make a copy of the iterator
	Iterator toReturn = *this;

	// Increment this
	++*this;

	// Return the copy
	return toReturn;
}

/**************************************************************************************************
* Pre-decrement
**************************************************************************************************/
const String::Iterator& String::Iterator::operator--(void) {
	// Decrement the pointer and return this
	--c;
	return *this;
}

/**************************************************************************************************
* Post-decrement
**************************************************************************************************/
const String::Iterator String::Iterator::operator--(int rhs) {
	// Make a copy of hte iterator
	Iterator toReturn = *this;

	// Decrement this
	--*this;

	// Return the copy
	return toReturn;
}

/**************************************************************************************************
* Increment by
**************************************************************************************************/
const String::Iterator& String::Iterator::operator+=(int off) {
	// Increment the iterator by the specified amount
	c += off;

	// Return this
	return *this;
}

/**************************************************************************************************
* Decrement by
**************************************************************************************************/
const String::Iterator& String::Iterator::operator-=(int off) {
	// Decrement the iterator by the specified amount
	c -= off;

	// Return this
	return *this;
}

/**************************************************************************************************
* Return an iterator incremented by specified amount
**************************************************************************************************/
const String::Iterator String::Iterator::operator+(int off) const {
	// Make a copy of the iterator
	Iterator toReturn = *this;

	// Increment the copy
	toReturn += off;

	// Return the copy
	return toReturn;
}

/**************************************************************************************************
* Return an iterator decremented by specified amount
**************************************************************************************************/
const String::Iterator String::Iterator::operator-(int off) const {
	// Make a copy of the iterator
	Iterator toReturn = *this;

	// Decrement the copy
	toReturn -= off;

	// Return the copy
	return toReturn;
}

/**************************************************************************************************
* Returns difference between two iterators
**************************************************************************************************/
const int String::Iterator::operator-(const Iterator& rhs) const {
	// Calculate the difference in addresses between the two pointers and return the address
	return (c - &*rhs);
}


/**************************************************************************************************
* Return the associated value at position
**************************************************************************************************/
char& String::Iterator::operator[](int off) const {
	return c[off];
}

/**************************************************************************************************
* Return the associated value
**************************************************************************************************/
const char& String::Iterator::operator*(void) const {
	return *c;
}

/**************************************************************************************************
* Return a pointer to the associated object
**************************************************************************************************/
const char* String::Iterator::operator->(void) const {
	return &**this;
}