/**************************************************************************************************
* Title: SumString.h
* Author: Gael Huber
* Description: Defines various methods for creating strings.
//
// TODO: Switch over comment structures to follow new standard
// TODO: Switch variable declarations and getters to follow new standard
// TODO: Switch file to using inline file to help optimize string operations
// TODO: Add const accessor functions
**************************************************************************************************/
#ifndef __SUMSTRING_H__
#define __SUMSTRING_H__

#include <assert.h>
#include "SumInclude.h"
#include "SumArray.h"

class String {
public:
	// Iterator for the string object
	class Iterator;

public:
	String(void);	// Default constructor
	String(const char* str);	// Constructor passing in const char* to define string
	String(const char* str, int l);	// Constructor passing in const char* and length to define string
	String(const char c);	// Constructor passing in one character
	String(int c);	// Allocate with a default capacity
	String(const String& rhs);	// Copy constructor
	~String(void);	// Destructor

	const String& operator=(const String& rhs);		// Assignment
	const String& operator=(const char* rhs);		// Assignment
	const bool operator==(const String& rhs) const;	// Equivalence
	const bool operator==(const char* rhs) const;	// Equivalence
	const bool operator==(const wchar_t* rhs) const;	// Equivalence
	const bool operator!=(const String& rhs) const;	// Non-equivalence
	const bool operator!=(const char* rhs) const;	// Non-quivalence
	const bool operator<(const String& rhs) const;	// Less than
	const bool operator<(const char* rhs) const;	// Less than
	const bool operator<=(const String& rhs) const;	// Less than or equal
	const bool operator<=(const char* rhs) const;	// Less than or equal
	const bool operator>(const String& rhs) const;	// Greater than
	const bool operator>(const char* rhs) const;	// Greater than
	const bool operator>=(const String& rhs) const;	// Greater than or equal
	const bool operator>=(const char* rhs) const;	// Greater than or equal

	const Iterator begin(void) const;	// Return an iterator to the beginning of the string
	Iterator begin(void);				// Return a non-const iterator to the beginning of the string
	const Iterator end(void) const;		// Return an iterator to the end of the string
	Iterator end(void);					// Return a non-const iterator to the end of the string
	
	const int getLength(void) const;		// Return the length of the string
	const int getMaxLength(void) const;	// Return the maximum length of the string
	const int getCapacity(void) const;		// Return the capacity of the string
	void clear(void);	// Clear the string
	const bool getEmpty(void) const;	// Test whether the string is empty

	char& operator[](const int index) const;	// Get character in string with array accessor
	const char& at(const int index) const;		// Returns a character in the string
	char& at(const int index);					// Returns a character in the string

	String& operator+=(const String& str);	// Append to the string
	String& operator+=(const char* str);		// Append to the string
	String& operator+=(const char c);		// Append to the string
	String operator+(const String& str);	// Return the appended string
	String operator+(const String& str) const;	// Return the appended string
	String operator+(const char* str);		// Return the appended string
	String operator+(const char c);			// Return the appended string
	String& append(const String& str);		// Append to the string
	String& append(const char* str);			// Append to the string
	String& append(const char c);			// Append to the string
	void push_back(const char c);			// Append to the string
	void insert(const String& str, int i);	// Insert into the string at a specified position
	void insert(const String& str, int i, int l);	// Insert into the string at a specified position for a specified length
	void insert(const char* str, int i);		// Insert into the string at a specified position
	void insert(const char* str, int i, int l);	// Insert into the string at a specified position for a specified length
	void insert(const char c, int i);		// Insert into the string at a specified position
	void erase(int i, int l);		// Erase specified contents of the string
	void erase(const String& str);		// Erase specified contents of the string
	void erase(const Iterator itr, int l);		// Erase specified contents of the string
	void erase(const Iterator first, Iterator last);		// Erase specified contents of the string
	void replace(int i, int l, const String& str);	// Replace part of the string
	void replace(const Iterator itr1, const Iterator itr2, const String& str);	// Replace part of the string
	void replace(int i1, int l1, const String& str, 
		int i2, int l2);	// Replace part of the string
	void replace(int i, int l1, const char* str, int l2);	// Replace part of the string
	void replace(const Iterator itr1, const Iterator itr2, const char* str, int l);		// Replace part of the string
	void replace(int i, int l, const char* str);	// Replace part of the string
	void replace(const Iterator itr1, const Iterator itr2, const char* str);		// Replace part of the string
	void replace(int i, int l, const char c, int times);	// Replace part of the string
	void replace(const Iterator itr1, const Iterator itr2, const char c, int times);	// Replace part of the string
	void set(const char* c);		// Set the contents of the string to equal the character array (this will NOT resize the string)
	void resize(void);	// Resize the array to fit if it is too large
	void swap(String& str);		// Swap contents with another string
	const int find(const String& str) const;	// Returns the first position where str exists (-1 otherwise)
	const int find(const char* str) const;		// Returns the first position where str exists (-1 otherwise)
	const int find(const char c) const;		// Returns the first position where c exists (-1 otherwise)
	const char* c_str(void) const;	// Return the contents as a standard C-string
	char* c_str();	// Return the contents as a character pointer
	operator const char*(void) const;	// Return the contents as a standard C-string upon casting
	operator int() const;		// Cast as an int
	const String substring(int i, int l) const;	// Return a substring
	const String substring(const Iterator itr1, const Iterator itr2) const;	// Return a substring
	Array<String> split(char split) const;	// Splits a string using the given character as a delimiter
	const int compare(const String& str) const;		// Compare strings, return -1 if less than compared, 0 if equal, 1 if greater
	void calcLength();	// Calculate the length of the string (this is to be used if this string is used as a buffer)

	// Convert a string to an int
	SINT toInt() const;
	SINT toInt();

	// Convert a string to an unsigned int
	SUINT toUInt() const;
	SUINT toUInt();

	// Convert a string to a floating point
	SFLOAT toFloat() const;
	SFLOAT toFloat();

	// Convert a string to a double
	SDOUBLE toDouble() const;
	SDOUBLE toDouble();

private:
	void _determineCapacity(void);		// Determine the capacity given a known length
	void _grow(void);		// Increase the size of the array

private:
	char* s;	// String
	int length;	// Size of string
	int maxLength;	// Maximum size of the string
	int capacity;	// Capacity of the string in terms of allocated storage
};

/**************************************************************************************************
* Iterator for string object
**************************************************************************************************/
class String::Iterator {
public:
	Iterator(void);		// Default constructor
	Iterator(char* ch);	// Constructor that binds the character it points to
	Iterator(const Iterator& rhs);	// Copy-constructor
	~Iterator(void);	// Destructor

	const Iterator& operator=(const Iterator& rhs);	// Assignment
	const bool operator==(const Iterator& rhs) const;	// Equivalence
	const bool operator!=(const Iterator& rhs) const;	// Non-equivalence
	const Iterator& operator++(void);	// Pre-increment
	const Iterator operator++(int);	// Post-increment
	const Iterator& operator--(void);	// Pre-decrement
	const Iterator operator--(int);	// Post-decrement
	const Iterator& operator+=(int off);	// Increment by
	const Iterator& operator-=(int off);	// Decrement by
	const Iterator operator+(int off) const;	// Return an iterator incremented by specified amount
	const Iterator operator-(int off) const;	// Return an iterator decremented by specified amount
	const int operator-(const Iterator& rhs) const;	// Returns difference between two iterators
	char& operator[](int off) const;	// Return the associated value at position
	const char& operator*(void) const;	// Return the associated value
	const char* operator->(void) const;	// Return a pointer to the associated object

private:
	char* c;	// Pointer to character
};

const int strLen(const char* s);	// Determines the length of a string

namespace Sum
{
	// String length
	const SUINT strlen(const wchar_t* s);
}

#include "SumString.inl"

#endif