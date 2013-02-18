/**************************************************************************************************
* Title: SumString.cpp
* Author: Gael Huber
* Description: Defines various methods for creating strings.
**************************************************************************************************/
#include "SumString.h"

/**************************************************************************************************
* Default constructor
**************************************************************************************************/
String::String(void)
	: s(0), length(0), maxLength(0), capacity(1)
{
	// Declare a character array of length 1
	s = new char[capacity];
	s[0] = '\0';
}

/**************************************************************************************************
* Constructor passing in const char* to define string
**************************************************************************************************/
String::String(const char* str) 
	: s(0), length(0), maxLength(0), capacity(0)
{
	// Determine the length
	length = strLen(str);

	// Declare a new array of the appropriate length by calculating the capacity
	_determineCapacity();
	
	// Declare space for the string
	s = new char[capacity];
	maxLength = capacity - 1;

	// Populate the string
	for(int i = 0; i < length; ++i) {
		s[i] = str[i];
	}

	// Terminate the string
	s[length] = '\0';
}

/**************************************************************************************************
* Constructor passing in const char* and length to define string
**************************************************************************************************/
String::String(const char* str, int l) 
	: s(0), length(0), maxLength(0), capacity(0)
{
	// Ensure the length specified is smaller than the actual length of the string, otherwise we will
	// assign the whole string
	int tLen = strLen(str);
	if(l < tLen) {
		length = l;
	} else {
		length = tLen;
	}

	// Determine the capacity
	_determineCapacity();

	// Max length is capacity-1
	maxLength = capacity - 1;

	// Allocate space
	s = new char[capacity];

	// Populate the string
	for(int i = 0; i < length; ++i) {
		s[i] = str[i];
	}

	// Terminate the string
	s[length] = '\0';
}

/**************************************************************************************************
* Constructor passing in one character
**************************************************************************************************/
String::String(const char c) 
	: s(0), length(1), maxLength(3), capacity(4)
{
	// Declare the array and add the character
	s = new char[capacity];
	s[0] = c;
	s[1] = '\0';
}

/**************************************************************************************************
* Constructor with a default capacity
**************************************************************************************************/
String::String(int c)
	: s(0), length(0), maxLength(c - 1), capacity(c)
{
	// Declare new array
	s = new char[capacity];
	s[0] = '\0';
}

/**************************************************************************************************
* Copy-constructor
**************************************************************************************************/
String::String(const String& rhs)
{
	// Get a pointer to the string in rhs
	const char* str = rhs.c_str();

	// Determine the length
	length = strLen(str);

	// Declare a new array of the appropriate length by calculating the capacity
	_determineCapacity();
	
	// Declare space for the string
	s = new char[capacity];
	maxLength = capacity - 1;

	// Populate the string
	for(int i = 0; i < length; ++i) {
		s[i] = str[i];
	}

	// Terminate the string
	s[length] = '\0';
}

/**************************************************************************************************
* Destructor
**************************************************************************************************/
String::~String(void) {
	// Free space previously allocated for s
	delete[] s;
}

/**************************************************************************************************
* Assignment
**************************************************************************************************/
const String& String::operator=(const String& rhs) {
	// Self-assignment guard
	if(&rhs == this) {
		return *this;
	}

	// Free memory
	delete[] s;

	// Get a pointer to the string in rhs
	const char* str = rhs.c_str();

	// Determine the length
	length = strLen(str);

	// Declare a new array of the appropriate length by calculating the capacity
	_determineCapacity();
	
	// Declare space for the string
	s = new char[capacity];
	maxLength = capacity - 1;

	// Populate the string
	for(int i = 0; i < length; ++i) {
		s[i] = str[i];
	}

	// Terminate the string
	s[length] = '\0';

	// Return this
	return *this;
}

/**************************************************************************************************
* Assignment
**************************************************************************************************/
const String& String::operator=(const char* rhs) {
	// Free memory
	delete[] s;

	// Determine the length
	length = strLen(rhs);

	// Declare a new array of the appropriate length by calculating the capacity
	_determineCapacity();
	
	// Declare space for the string
	s = new char[capacity];
	maxLength = capacity - 1;

	// Populate the string
	for(int i = 0; i < length; ++i) {
		s[i] = rhs[i];
	}

	// Terminate the string
	s[length] = '\0';

	// Return this
	return *this;
}

/**************************************************************************************************
* Equivalence
**************************************************************************************************/
const bool String::operator==(const String& rhs) const {
	// Test lengths
	if(rhs.getLength() != length) {
		return false;
	}

	// Test individual letters
	for(int i = 0; i < length; ++i) {
		if(s[i] != rhs[i]) {
			return false;
		}
	}

	// Passed tests so return true
	return true;
}

/**************************************************************************************************
* Equivalence
**************************************************************************************************/
const bool String::operator==(const char* rhs) const {
	// Test lengths
	if(strLen(rhs) != length) {
		return false;
	}

	// Test individual letters
	for(int i = 0; i < length; ++i) {
		if(s[i] != rhs[i]) {
			return false;
		}
	}

	// Passed tests so return true
	return true;
}

/**************************************************************************************************
* Non-equivalence
**************************************************************************************************/
const bool String::operator!=(const String& rhs) const {
	return !(*this == rhs);
}

/**************************************************************************************************
* Non-equivalence
**************************************************************************************************/
const bool String::operator!=(const char* rhs) const {
	return !(*this == rhs);
}

/**************************************************************************************************
* Less than
**************************************************************************************************/
const bool String::operator<(const String& rhs) const 
{
	// Iterate through each string while they are valid
	int checkLength;
	if(length < rhs.getLength()) {
		checkLength = length;
	} else {
		checkLength = rhs.getLength();
	}
	
	// Iterate while they are equivalent
	for(int i = 0; i < checkLength; ++i) {
		// If we are less than, we know that we must meet conditions so return true
		if(s[i] < rhs[i]) 
		{
			return true;
		}
		// Otherwise, we could be equal so if greater return false
		else if(s[i] > rhs[i])
		{
			return false;
		}
	}

	// We made it this far without failing tests, so we must now check lengths. 
	// If this.length < rhs.length, we know that rhs must be greater than this, so we may return true.
	// In all other situations return false.
	return length < rhs.getLength();
}

/**************************************************************************************************
* Less than
**************************************************************************************************/
const bool String::operator<(const char* rhs) const 
{
	// Iterate through each string while they are valid
	SINT sLength = strLen(rhs);
	SINT checkLength = sLength;
	if(length < checkLength) {
		checkLength = length;
	}
	
	// Iterate while they are equivalent
	for(SINT i = 0; i < checkLength; ++i) {
		// If greater than or equal to, return false
		if(s[i] < rhs[i]) 
		{
			return true;
		}
		else if(s[i] > rhs[i])
		{
			return false;
		}
	}

	return length < sLength;
}

/**************************************************************************************************
* Less than or equal
**************************************************************************************************/
const bool String::operator<=(const String& rhs) const 
{
	// Iterate through each string while they are valid
	int checkLength;
	if(length < rhs.getLength()) {
		checkLength = length;
	} else {
		checkLength = rhs.getLength();
	}
	
	// Iterate while they are equivalent
	for(int i = 0; i < checkLength; ++i) {
		// If we are less than, we know that we must meet conditions so return true
		if(s[i] < rhs[i]) 
		{
			return true;
		}
		// Otherwise, we could be equal so if greater return false
		else if(s[i] > rhs[i])
		{
			return false;
		}
	}

	// We made it this far without failing tests, so we must now check lengths. 
	// If this.length < rhs.length, we know that rhs must be greater than this, so we may return true.
	// In all other situations return false.
	return length <= rhs.getLength();	
}

/**************************************************************************************************
* Less than or equal
**************************************************************************************************/
const bool String::operator<=(const char* rhs) const 
{
	// Iterate through each string while they are valid
	SINT sLength = strLen(rhs);
	SINT checkLength = sLength;
	if(length < checkLength) {
		checkLength = length;
	}
	
	// Iterate while they are equivalent
	for(SINT i = 0; i < checkLength; ++i) {
		// If greater than or equal to, return false
		if(s[i] < rhs[i]) 
		{
			return true;
		}
		else if(s[i] > rhs[i])
		{
			return false;
		}
	}

	return length <= sLength;
}

/**************************************************************************************************
* Greater than
**************************************************************************************************/
const bool String::operator>(const String& rhs) const {
	// Iterate through each string while they are valid
	int checkLength;
	if(length < rhs.getLength()) {
		checkLength = length;
	} else {
		checkLength = rhs.getLength();
	}
	
	// Iterate while they are equivalent
	for(int i = 0; i < checkLength; ++i) {
		// If we are less than, we know that we must meet conditions so return true
		if(s[i] > rhs[i]) 
		{
			return true;
		}
		// Otherwise, we could be equal so if greater return false
		else if(s[i] < rhs[i])
		{
			return false;
		}
	}

	// We made it this far without failing tests, so we must now check lengths. 
	// If this.length < rhs.length, we know that rhs must be greater than this, so we may return true.
	// In all other situations return false.
	return length > rhs.getLength();
}

/**************************************************************************************************
* Greater than
**************************************************************************************************/
const bool String::operator>(const char* rhs) const {
	// Iterate through each string while they are valid
	SINT sLength = strLen(rhs);
	SINT checkLength = sLength;
	if(length < checkLength) {
		checkLength = length;
	}
	
	// Iterate while they are equivalent
	for(SINT i = 0; i < checkLength; ++i) {
		// If greater than or equal to, return false
		if(s[i] > rhs[i]) 
		{
			return true;
		}
		else if(s[i] < rhs[i])
		{
			return false;
		}
	}

	return length > sLength;
}

/**************************************************************************************************
* Greater than or equal
**************************************************************************************************/
const bool String::operator>=(const String& rhs) const {
	// Iterate through each string while they are valid
	int checkLength;
	if(length < rhs.getLength()) {
		checkLength = length;
	} else {
		checkLength = rhs.getLength();
	}
	
	// Iterate while they are equivalent
	for(int i = 0; i < checkLength; ++i) {
		// If we are less than, we know that we must meet conditions so return true
		if(s[i] > rhs[i]) 
		{
			return true;
		}
		// Otherwise, we could be equal so if greater return false
		else if(s[i] < rhs[i])
		{
			return false;
		}
	}

	// We made it this far without failing tests, so we must now check lengths. 
	// If this.length < rhs.length, we know that rhs must be greater than this, so we may return true.
	// In all other situations return false.
	return length >= rhs.getLength();
}

/**************************************************************************************************
* Greater than or equal
**************************************************************************************************/
const bool String::operator>=(const char* rhs) const 
{
	// Iterate through each string while they are valid
	SINT sLength = strLen(rhs);
	SINT checkLength = sLength;
	if(length < checkLength) {
		checkLength = length;
	}
	
	// Iterate while they are equivalent
	for(SINT i = 0; i < checkLength; ++i) {
		// If greater than or equal to, return false
		if(s[i] > rhs[i]) 
		{
			return true;
		}
		else if(s[i] < rhs[i])
		{
			return false;
		}
	}

	return length >= sLength;
}

/**************************************************************************************************
* Return an iterator to the beginning of the string
**************************************************************************************************/
const String::Iterator String::begin(void) const {
	return Iterator(s);
}

/**************************************************************************************************
* Return a non-const iterator to the beginning of the string 
**************************************************************************************************/
String::Iterator String::begin(void) {
	return Iterator(s);
}

/**************************************************************************************************
* Return an iterator to the end of the string
**************************************************************************************************/
const String::Iterator String::end(void) const {
	return Iterator(s + length);
}

/**************************************************************************************************
* Return a non-const iterator to the end of the string 
**************************************************************************************************/
String::Iterator String::end(void) {
	return Iterator(s + length);
}

/**************************************************************************************************
* Return the length of the string
**************************************************************************************************/
const int String::getLength(void) const {
	return length;
}

/**************************************************************************************************
* Return the maximum length of the string
**************************************************************************************************/
const int String::getMaxLength(void) const {
	return maxLength;
}

/**************************************************************************************************
* Return the capacity of the string
**************************************************************************************************/
const int String::getCapacity(void) const {
	return capacity;
}

/**************************************************************************************************
* Clear the string
**************************************************************************************************/
void String::clear(void) {
	//  Empty out the string. We can achieve this by only placing a null-terminating character at the 
	// start of the string.
	if(s) {
		delete[] s;
		capacity = 1;
		length = 0;
		maxLength = 0;
		s = new char[capacity];
		s[0] = '\0';
	}
}

/**************************************************************************************************
* Test whether the string is empty
**************************************************************************************************/
const bool String::getEmpty(void) const {
	return (length) ? false : true;
}

/**************************************************************************************************
* Get character in string with array accessor
**************************************************************************************************/
char& String::operator[](const int index) const {
	assert(index < length);
	return *(s + index);
}

/**************************************************************************************************
* Returns a character in the string
**************************************************************************************************/
const char& String::at(const int index) const {
	assert(index < length);
	return *(s + index);
}

/**************************************************************************************************
* Returns a character in the string
**************************************************************************************************/
char& String::at(const int index) {
	assert(index < length);
	return *(s + index);
}

/**************************************************************************************************
* Append to the string
**************************************************************************************************/
String& String::operator+=(const String& str) {
	return append(str);
}

/**************************************************************************************************
* Append to the string
**************************************************************************************************/
String& String::operator+=(const char* str) {
	return append(str);
}

/**************************************************************************************************
* Append to the string
**************************************************************************************************/
String& String::operator+=(const char c) {
	return append(c);
}

/**************************************************************************************************
* Return the appended string
**************************************************************************************************/
String String::operator+(const String& str) {
	String toReturn = String(*this);
	toReturn += str;
	return toReturn;
}

/**************************************************************************************************
* Return the appended string
**************************************************************************************************/
String String::operator+(const char* str) {
	String toReturn = String(*this);
	toReturn += str;
	return toReturn;
}

/**************************************************************************************************
* Return the appended string
**************************************************************************************************/
String String::operator+(const char c) {
	String toReturn = String(*this);
	toReturn += c;
	return toReturn;
}

/**************************************************************************************************
* Append to the string
**************************************************************************************************/
String& String::append(const String& str) {
	// Grow the array while we need the space
	while(length + str.getLength() > maxLength) {
		_grow();
	}

	// Append the string to the end
	const char* cs = str.c_str();
	for(int i = 0; i < str.getLength(); ++i) {
		s[length++] = cs[i];
	}
	s[length] = '\0';

	// Return this
	return *this;
}

/**************************************************************************************************
* Append to the string
**************************************************************************************************/
String& String::append(const char* str) {
	// Find the length
	int len = strLen(str);

	// Grow the array while we need the space
	while(length + len > maxLength) {
		_grow();
	}

	// Append the string to the end
	for(int i = 0; i < len; ++i) {
		s[length++] = str[i];
	}
	s[length] = '\0';

	// Return this
	return *this;
}

/**************************************************************************************************
* Append to the string
**************************************************************************************************/
String& String::append(const char c) {
	// Grow if adding will exceed maximum capacity
	if(length == maxLength) {
		_grow();
	}

	// Append the character to the string
	s[length++] = c;
	s[length] = '\0';

	// Return this
	return *this;
}

/**************************************************************************************************
* Append to the string
**************************************************************************************************/
void String::push_back(const char c) {
	// Grow if adding will exceed maximum capacity
	if(length == maxLength) {
		_grow();
	}

	// Append the character to the string
	s[length++] = c;
	s[length] = '\0';
}

/**************************************************************************************************
* Insert into the string at a specified position
**************************************************************************************************/
void String::insert(const String& str, int i) {
	// Ensure that we are inserting at a valid position
	assert(i < length);

	// Calculate the amount by which we will need to right-shift our string about i
	int shiftLength = str.getLength();

	// Grow the array if inserting will cause an overflow
	while(length + shiftLength > maxLength) {
		_grow();
	}

	// Shift the contents of the string back by length
	for(int index = length; index >= i; --index) {
		s[index + shiftLength] = s[index];
	}

	// Insert the new string
	for(int index = 0; index < shiftLength; ++index) {
		s[i + index] = str[index];
	}

	// Set the new length
	length += shiftLength;
}

/**************************************************************************************************
* Insert into the string at a specified position for a specified length
**************************************************************************************************/
void String::insert(const String& str, int i, int l) {
	// Ensure that we are inserting at a valid position
	assert(i < length);

	// If l is more than string length, clamp it
	if(l > str.getLength()) {
		l = str.getLength();
	}

	// Calculate the amount by which we will need to right-shift our string about i
	int shiftLength = l;

	// Grow the array if inserting will cause an overflow
	while(length + shiftLength > maxLength) {
		_grow();
	}

	// Shift the contents of the string back by length
	for(int index = length; index >= i; --index) {
		s[index + shiftLength] = s[index];
	}

	// Insert the new string
	for(int index = 0; index < shiftLength; ++index) {
		s[i + index] = str[index];
	}

	// Set the new length
	length += shiftLength;
}

/**************************************************************************************************
* Insert into the string at a specified position
**************************************************************************************************/
void String::insert(const char* str, int i) {
		// Ensure that we are inserting at a valid position
	assert(i < length);

	// Calculate the amount by which we will need to right-shift our string about i
	int shiftLength = strLen(str);

	// Grow the array if inserting will cause an overflow
	while(length + shiftLength > maxLength) {
		_grow();
	}

	// Shift the contents of the string back by length
	for(int index = length; index >= i; --index) {
		s[index + shiftLength] = s[index];
	}

	// Insert the new string
	for(int index = 0; index < shiftLength; ++index) {
		s[i + index] = str[index];
	}

	// Set the new length
	length += shiftLength;
}

/**************************************************************************************************
* Insert into the string at a specified position for a specified length
**************************************************************************************************/
void String::insert(const char* str, int i, int l) {
	// Ensure that we are inserting at a valid position
	assert(i < length);

	// If l is more than string length, clamp it
	if(l > strLen(str)) {
		l = strLen(str);
	}

	// Calculate the amount by which we will need to right-shift our string about i
	int shiftLength = l;

	// Grow the array if inserting will cause an overflow
	while(length + shiftLength > maxLength) {
		_grow();
	}

	// Shift the contents of the string back by length
	for(int index = length; index >= i; --index) {
		s[index + shiftLength] = s[index];
	}

	// Insert the new string
	for(int index = 0; index < shiftLength; ++index) {
		s[i + index] = str[index];
	}

	// Set the new length
	length += shiftLength;
}

/**************************************************************************************************
* Insert into the string at a specified position
**************************************************************************************************/
void String::insert(const char c, int i) {
	// Ensure that we are inserting at a valid position
	assert(i < length);

	// Grow the array if inserting will cause an overflow
	if(length + 1 > maxLength) {
		_grow();
	}

	// Shift the contents of the string back by length
	for(int index = length; index >= i; --index) {
		s[index + 1] = s[index];
	}

	// Insert the new character
	s[i + 1] = c;
	
	// Set the new length
	++length;
}

/**************************************************************************************************
* Erase specified contents of the string
**************************************************************************************************/
void String::erase(int i, int l) {
	// First check whether i is a valid index
	assert(i < length);

	// Next check whether length to erase will terminate string, if that is the case, set i to null
	// terminator and return
	if(i + l > length) {
		length = i;
		s[i] = '\0';
		return;
	}

	// For all other instances, shift all other characters back
	for(int index = i + l; index <= length; ++index) {
		s[index - l] = s[index];		
	}

	// Fit length
	length-= l;
}

/**************************************************************************************************
* Erase specified contents of the string
**************************************************************************************************/
void String::erase(const String& str) {
	// First we need to find the matching contents
	int pos = find(str);
	
	// If the contents exist, erase them
	if(pos != -1) {
		erase(pos, str.getLength());
	}
}

/**************************************************************************************************
* Erase specified contents of the string
**************************************************************************************************/
void String::erase(const Iterator itr, int l) {
	// Clamp length
	if(&*itr + l > s + length) {
		l = s + length - &*itr;
	}
	
	// Pull index of iterator
	int index = &*itr - s;

	// Iterate through and shift remaining characters forward
	for(int i = index + l; i <= length; ++i) {
		s[i - l] = s[i];
	}

	// Update length
	length -= l;
}

/**************************************************************************************************
* Erase specified contents of the string
**************************************************************************************************/
void String::erase(const Iterator first, Iterator last) {
	// Find the index of each iterator
	int firstIndex = &*first - s;
	int lastIndex = &*last - s;
	
	// Calculate the length between the two iterators
	int len = (&*last - s) - firstIndex;
	int end = length - len;

	// Iterate through and shift contents of string
	for(int i = firstIndex; i <= end; ++i) {
		s[i] = s[i + len];
	}

	// Update length
	length -= len;
}

/**************************************************************************************************
* Replace part of the string
**************************************************************************************************/
void String::replace(int i, int l, const String& str) {
	// Check whether the index is valid
	assert(i < length);
	
	// Does l need to be clamped?
	if(i + l > maxLength) {
		l = maxLength - i;
	}

	// Grow the array while the projected length is greater than current max
	while(length - l + str.getLength() > maxLength) {
		_grow();
	}

	// Shift contents to right of replacement. We must check whether we are doing a right shift or a 
	// left shift.
	if(l > str.getLength()) {
		// Left shift
		for(int index = i + l; index <= length; ++index) {
			s[index - l + str.getLength()] = s[index];
		}
	} else if(l < str.getLength()) {
		// Right shift
		for(int index = length; index >= i + l; --index) {
			s[index - l + str.getLength()] = s[index];
		}
	}

	// Copy the replacement string
	for(int index = 0; index < str.getLength(); ++index) {
		s[i + index] = str[index];
	}

	// Calculate new length
	length = length + str.getLength() - l;
}

/**************************************************************************************************
* Replace part of the string
**************************************************************************************************/
void String::replace(const Iterator itr1, const Iterator itr2, const String& str) {
	// Calculate starting index
	int i = &*itr1 - s;
	
	// Calculate the length between the two iterators
	int l = (&*itr2 - s) - i;
	
	// Does l need to be clamped?
	if(i + l > maxLength) {
		l = maxLength - i;
	}

	// Grow the array while the projected length is greater than current max
	while(length - l + str.getLength() > maxLength) {
		_grow();
	}

	// Shift contents to right of replacement. We must check whether we are doing a right shift or a 
	// left shift.
	if(l > str.getLength()) {
		// Left shift
		for(int index = i + l; index <= length; ++index) {
			s[index - l + str.getLength()] = s[index];
		}
	} else if(l < str.getLength()) {
		// Right shift
		for(int index = length; index >= i + l; --index) {
			s[index - l + str.getLength()] = s[index];
		}
	}

	// Copy the replacement string
	for(int index = 0; index < str.getLength(); ++index) {
		s[i + index] = str[index];
	}

	// Calculate new length
	length = length + str.getLength() - l;
}

/**************************************************************************************************
* Replace part of the string
**************************************************************************************************/
void String::replace(int i1, int l1, const String& str, int i2, int l2) {
	// Check whether the index is valid
	assert(i1 < length);
	assert(i2 < str.getLength());
	
	// Does l need to be clamped?
	if(i1 + l1 > maxLength) {
		l1 = maxLength - i1;
	}
	if(i2 + l2 > str.getLength()) {
		l2 = str.getMaxLength() - i2;
	}

	// Grow the array while the projected length is greater than current max
	while(length - l1 + l2 > maxLength) {
		_grow();
	}

	// Shift contents to right of replacement. We must check whether we are doing a right shift or a 
	// left shift.
	if(l1 > l2) {
		// Left shift
		for(int index = i1 + l1; index <= length; ++index) {
			s[index - l1 + l2] = s[index];
		}
	} else if(l1 < l2) {
		// Right shift
		for(int index = length; index >= i1 + l1; --index) {
			s[index - l1 + l2] = s[index];
		}
	}

	// Copy the replacement string
	for(int index = 0; index < l2; ++index) {
		s[i1 + index] = str[i2 + index];
	}

	// Calculate new length
	length = length + l2 - l1;
}

/**************************************************************************************************
* Replace part of the string
**************************************************************************************************/
void String::replace(int i, int l1, const char* str, int l2) {
	// Check whether the index is valid
	assert(i < length);
	
	// Does l need to be clamped?
	if(i + l1 > maxLength) {
		l1 = maxLength - i;
	}
	if(l2 > strLen(str)) {
		l2 = strLen(str);
	}

	// Grow the array while the projected length is greater than current max
	while(length - l1 + l2 > maxLength) {
		_grow();
	}

	// Shift contents to right of replacement. We must check whether we are doing a right shift or a 
	// left shift.
	if(l1 > l2) {
		// Left shift
		for(int index = i + l1; index <= length; ++index) {
			s[index - l1 + l2] = s[index];
		}
	} else if(l1 < l2) {
		// Right shift
		for(int index = length; index >= i + l1; --index) {
			s[index - l1 + l2] = s[index];
		}
	}

	// Copy the replacement string
	for(int index = 0; index < l2; ++index) {
		s[i + index] = str[index];
	}

	// Calculate new length
	length = length + l2 - l1;
}

/**************************************************************************************************
* Replace part of the string
**************************************************************************************************/
void String::replace(const Iterator itr1, const Iterator itr2, const char* str, int l) {
	// Calculate starting index
	int i = &*itr1 - s;
	
	// Calculate the length between the two iterators
	int len = (&*itr2 - s) - i;
	
	// Does l need to be clamped?
	if(i + len > maxLength) {
		len = maxLength - i;
	}

	// Grow the array while the projected length is greater than current max
	int strlen = strLen(str);
	strlen = (l > strlen) ? strlen : l;
	while(length - len + strlen > maxLength) {
		_grow();
	}

	// Shift contents to right of replacement. We must check whether we are doing a right shift or a 
	// left shift.
	if(len > strlen) {
		// Left shift
		for(int index = i + len; index <= length; ++index) {
			s[index - len + strlen] = s[index];
		}
	} else if(len < strlen) {
		// Right shift
		for(int index = length; index >= i + len; --index) {
			s[index - len + strlen] = s[index];
		}
	}

	// Copy the replacement string
	for(int index = 0; index < strlen; ++index) {
		s[i + index] = str[index];
	}

	// Calculate new length
	length = length + strlen - len;
}

/**************************************************************************************************
* Replace part of the string
**************************************************************************************************/
void String::replace(int i, int l, const char* str) {
	// Check whether replacement index is valid
	assert(i < l);

	// Cap l if length to replace is longer than end of string
	if(i + l > maxLength) {
		l = maxLength - i;
	}

	// Calculate length of string to insert
	int l2 = strLen(str);

	// Grow the array while the projected length is greater than current max
	while(length - l + l2 > maxLength) {
		_grow();
	}

	// Shift contents to right of replacement. We must check whether we are doing a right shift or a 
	// left shift.
	if(l > l2) {
		// Left shift
		for(int index = i + l; index <= length; ++index) {
			s[index - l + l2] = s[index];
		}
	} else if(l < l2) {
		// Right shift
		for(int index = length; index >= i + l; --index) {
			s[index - l + l2] = s[index];
		}
	}

	// Copy the replacement string
	for(int index = 0; index < l2; ++index) {
		s[i + index] = str[index];
	}

	// Calculate new length
	length = length + l2 - l;
}

/**************************************************************************************************
* Replace part of the string
**************************************************************************************************/
void String::replace(const Iterator itr1, const Iterator itr2, const char* str) {
	// Calculate starting index
	int i = &*itr1 - s;
	
	// Calculate the length between the two iterators
	int len = (&*itr2 - s) - i;
	
	// Does l need to be clamped?
	if(i + len > maxLength) {
		len = maxLength - i;
	}

	// Grow the array while the projected length is greater than current max
	int strlen = strLen(str);
	while(length - len + strlen > maxLength) {
		_grow();
	}

	// Shift contents to right of replacement. We must check whether we are doing a right shift or a 
	// left shift.
	if(len > strlen) {
		// Left shift
		for(int index = i + len; index <= length; ++index) {
			s[index - len + strlen] = s[index];
		}
	} else if(len < strlen) {
		// Right shift
		for(int index = length; index >= i + len; --index) {
			s[index - len + strlen] = s[index];
		}
	}

	// Copy the replacement string
	for(int index = 0; index < strlen; ++index) {
		s[i + index] = str[index];
	}

	// Calculate new length
	length = length + strlen - len;
}

/**************************************************************************************************
* Replace part of the string
**************************************************************************************************/
void String::replace(int i, int l, const char c, int times = 1) {
	// Make sure that index is within bounds
	assert(i < length);

	// Clamp length of string to replace
	if(i + l > maxLength) {
		l = maxLength - i;
	}

	// Grow the array while the projected length is greater than current max
	while(length - l + times > maxLength) {
		_grow();
	}

	// Shift contents to right of replacement. We must check whether we are doing a right shift or a 
	// left shift.
	if(l > times) {
		// Left shift
		for(int index = i + l; index <= length; ++index) {
			s[index - l + times] = s[index];
		}
	} else if(l < times) {
		// Right shift
		for(int index = length; index >= i + l; --index) {
			s[index - l + times] = s[index];
		}
	}

	// Copy the replacement string
	for(int index = 0; index < times; ++index) {
		s[i + index] = c;
	}

	// Calculate new length
	length = length + times - l;
}

/**************************************************************************************************
* Replace part of the string
**************************************************************************************************/
void String::replace(const Iterator itr1, const Iterator itr2, const char c, int times = 1) {
	// Calculate starting index
	int i = &*itr1 - s;
	
	// Calculate the length between the two iterators
	int len = (&*itr2 - s) - i;
	
	// Does l need to be clamped?
	if(i + len > maxLength) {
		len = maxLength - i;
	}

	// Grow the array while the projected length is greater than current max
	while(length - len + times > maxLength) {
		_grow();
	}

	// Shift contents to right of replacement. We must check whether we are doing a right shift or a 
	// left shift.
	if(len > times) {
		// Left shift
		for(int index = i + len; index <= length; ++index) {
			s[index - len + times] = s[index];
		}
	} else if(len < times) {
		// Right shift
		for(int index = length; index >= i + len; --index) {
			s[index - len + times] = s[index];
		}
	}

	// Copy the replacement string
	for(int index = 0; index < times; ++index) {
		s[i + index] = c;
	}

	// Calculate new length
	length = length + times - len;
}

/**************************************************************************************************
* Set the contents of the string to equal the character array (this will NOT resize the string)
**************************************************************************************************/
void String::set(const char* c) {
	int len = capacity < strLen(c) ? capacity : strLen(c);
	for(int i = 0; i < len; ++i) {
		s[i] = c[i];
	}
	s[len] = '\0';
	length = len;
}

/**************************************************************************************************
* Resize the array to fit if it is too large
**************************************************************************************************/
void String::resize(void) {
	// Find out desired length cap
	_determineCapacity();

	// Create a new array
	char* copy = new char[capacity];

	// Copy the data to the new array
	for(int i = 0; i < length; ++i) {
		copy[i] = s[i];
	}
	s[length] = '\0';

	// Delete the old array
	delete[] s;

	// Set pointer to the new array
	s = copy;
}

/**************************************************************************************************
* Swap contents with another string
**************************************************************************************************/
void String::swap(String& str) {
	// Swap values
	String tmp = *this;
	*this = str;
	str = tmp;
}

/**************************************************************************************************
* Returns true if this contains requested string
**************************************************************************************************/
const int String::find(const String& str) const {
	// Set loop limit, only need to go through until the last possible match start
	int lim = (length >= str.getLength()) ? length - str.getLength() + 1 : 0;

	// Loop through all possible match starts
	for(int i = 0; i < lim; ++i) {
		// Check whether there is a match possibility
		if(s[i] == str[static_cast<int>(0)]) {
			// Verify contains statement
			bool valid = true;
			for(int j = 1; j < str.getLength(); ++j) {
				// Check for non-containing
				if(s[i+j] != str[j]) {
					valid = false;
					j = str.getLength();
				}
			}

			// Check validity
			if(valid) {
				// Return true on valid contains
				return i;
			}
		}
	}

	// Return false as the requested string is not contained
	return -1;
}

/**************************************************************************************************
* Returns the first position where str exists (-1 otherwise)
**************************************************************************************************/
const int String::find(const char* str) const {
	// Set loop limit, only need to go through until the last possible match start
	int strlen = strLen(str);
	int lim = (length >= strlen) ? length - strlen + 1 : 0;

	// Loop through all possible match starts
	for(int i = 0; i < lim; ++i) {
		// Check whether there is a match possibility
		if(s[i] == str[0]) {
			// Verify contains statement
			bool valid = true;
			for(int j = 1; j < strlen; ++j) {
				// Check for non-containing
				if(s[i+j] != str[j]) {
					valid = false;
					j = strlen;
				}
			}

			// Check validity
			if(valid) {
				// Return true on valid contains
				return i;
			}
		}
	}

	// Return false as the requested string is not contained
	return -1;
}

/**************************************************************************************************
* Returns the first position where c exists (-1 otherwise)
**************************************************************************************************/
const int String::find(const char c) const {
	// Loop through all possible match starts
	for(int i = 0; i < length; ++i) {
		// Check whether there is a match possibility
		if(s[i] == c) {
			// Return true on valid contains
			return i;
		}
	}

	// Return false as the requested string is not contained
	return -1;
}

/**************************************************************************************************
* Return the contents as a standard C-string
**************************************************************************************************/
const char* String::c_str(void) const {
	return s;
}

/**************************************************************************************************
* Return the contents as a standard C-string upon casting
**************************************************************************************************/
String::operator const char*(void) const {
	return s;
}

/**************************************************************************************************
* Cast as an int
**************************************************************************************************/
String::operator int() const {
	return reinterpret_cast<int>(s);
}

/**************************************************************************************************
* Return a substring
**************************************************************************************************/
const String String::substring(int i, int l) const {
	assert(i < length);
	return String(&s[i], l);
}

/**************************************************************************************************
* Return a substring
**************************************************************************************************/
const String String::substring(const Iterator itr1, const Iterator itr2) const {
	return String(&*itr1, (&*itr2 - &*itr1));
}

/**************************************************************************************************
* Splits a string using the given character as a delimiter
**************************************************************************************************/
Array<String> String::split(char split) const {
	Array<String> arr;

	// Current string
	String str;
	Iterator e = end();
	for(Iterator itr = begin(); itr != e; ++itr) {
		// Check for delimiter
		if(*itr == split) {
			arr.push_back(str);
			str.clear();
		} else {
			str += *itr;
		}
	}
	if(!str.getEmpty())
	{
		arr.push_back(str);
		str.clear();
	}

	return arr;
}

/**************************************************************************************************
* Compare strings, return -1 if less than compared, 0 if equal, 1 if greater
**************************************************************************************************/
const int String::compare(const String& str) const {
	// Compare lengths
	int complen = (length < str.getLength()) ? length : str.getLength();

	// Compare each character
	for(int i = 0; i < complen; ++i) {
		if(s[i] > str[i]) {
			return 1;
		} else if(s[i] < str[i]) {
			return -1;
		}
	}

	// Successful comparison, check lengths
	if(length == str.getLength()) {
		return 0;
	} else if(length > str.getLength()) {
		return 1;
	} else {
		return -1;
	}
}

/**************************************************************************************************
* Determines the length of a string
**************************************************************************************************/
const int strLen(const char* s) {
	int count = 0;
	while(*(s++)) {
		++count;
	}
	
	return count;
}

/**************************************************************************************************
* Determine the capacity given a known length
**************************************************************************************************/
void String::_determineCapacity(void) {
	// If length is at least 1, capacity must be greater than 1
	if(length > 0) {
		// Find the next greatest power of 2 including a null-terminating character
		capacity = length;
		capacity |= capacity >> 1;
		capacity |= capacity >> 2;
		capacity |= capacity >> 4;
		capacity |= capacity >> 8;
		capacity |= capacity >> 16;
		++capacity;
	} else {
		capacity = 1;
	}
}

/**************************************************************************************************
* Increase the size of the array
**************************************************************************************************/
void String::_grow(void) {
	// Double the capacity
	capacity *= 2;
	maxLength = capacity - 1;

	// Allocate new space for the array
	char* c = new char[capacity];

	// Copy the data over
	for(int i = 0; i < length; ++i) {
		c[i] = s[i];
	}
	c[length] = '\0';

	// Free the old array
	delete[] s;

	// Assign the new array
	s = c;
}