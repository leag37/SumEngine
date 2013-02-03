/**************************************************************************************************
* Title: SumArrayIterator.inl
* Author: Gael Huber
* Description: Defines an iterator for the array data structure
**************************************************************************************************/

/**************************************************************************************************
* Default constructor
**************************************************************************************************/
template <typename Type>
inline Array<Type>::Iterator::Iterator(void)
	: data(0)
{ }

/**************************************************************************************************
* Constructor given pointer to element in array
**************************************************************************************************/
template <typename Type>
inline Array<Type>::Iterator::Iterator(Type* data)
	: data(data)
{ }

/**************************************************************************************************
* Copy constructor
**************************************************************************************************/
template <typename Type>
inline Array<Type>::Iterator::Iterator(const Iterator& rhs)
	: data(&*rhs)
{ }

/**************************************************************************************************
* Destructor
**************************************************************************************************/
template <typename Type>
inline Array<Type>::Iterator::~Iterator(void) {
	data = 0;
}

/**************************************************************************************************
* Return the data referenced
**************************************************************************************************/
template <typename Type>
inline Type& Array<Type>::Iterator::operator*(void) const {
	return *data;
}

/**************************************************************************************************
* Return a pointer to the class object
**************************************************************************************************/
template <typename Type>
inline Type* Array<Type>::Iterator::operator->(void) const {
	return data;
}

/**************************************************************************************************
* Pre-increment
**************************************************************************************************/
template <typename Type>
inline typename Array<Type>::Iterator& Array<Type>::Iterator::operator++(void) {
	++data;
	return *this;
}
	
/**************************************************************************************************
* Post-increment
**************************************************************************************************/
template <typename Type>
inline typename Array<Type>::Iterator Array<Type>::Iterator::operator++(int rhs) {
	Iterator itr(*this);
	++data;
	return itr;
}

/**************************************************************************************************
* Pre-decrement
**************************************************************************************************/
template <typename Type>
inline typename Array<Type>::Iterator& Array<Type>::Iterator::operator--(void) {
	--data;
	return *this;
}

/**************************************************************************************************
* Post-decrement
**************************************************************************************************/
template <typename Type>
inline typename Array<Type>::Iterator Array<Type>::Iterator::operator--(int rhs) {
	Iterator itr(*this);
	--data;
	return itr;
}

/**************************************************************************************************
* Increment by integer
**************************************************************************************************/
template <typename Type>
inline typename Array<Type>::Iterator& Array<Type>::Iterator::operator+=(int rhs) {
	data += rhs;
	return *this;
}

/**************************************************************************************************
* Return this + integer
**************************************************************************************************/
template <typename Type>
inline typename Array<Type>::Iterator Array<Type>::Iterator::operator+(int rhs) const {
	return Iterator(data + rhs);
}

/**************************************************************************************************
* Decrement by integer
**************************************************************************************************/
template <typename Type>
inline typename Array<Type>::Iterator& Array<Type>::Iterator::operator-=(int rhs) {
	data -= rhs;
	return *this;
}

/**************************************************************************************************
* Return this - integer
**************************************************************************************************/
template <typename Type>
inline typename Array<Type>::Iterator Array<Type>::Iterator::operator-(int rhs) const {
	return Iterator(data - rhs);
}

/**************************************************************************************************
* Return difference of iterators
**************************************************************************************************/
template <typename Type>
inline int Array<Type>::Iterator::operator-(const Iterator& rhs) const {
	return data - &*rhs;
}

/**************************************************************************************************
* Return the data held
**************************************************************************************************/
template <typename Type>
inline Type& Array<Type>::Iterator::operator[](int rhs) const {
	return data[int];
}

/**************************************************************************************************
* Equivanlence operator
**************************************************************************************************/
template <typename Type>
inline bool Array<Type>::Iterator::operator==(const Iterator& rhs) const {
	return data == &*rhs;
}

/**************************************************************************************************
* Non-equivalence
**************************************************************************************************/
template <typename Type>
inline bool Array<Type>::Iterator::operator!=(const Iterator& rhs) const {
	return data != &*rhs;
}

/**************************************************************************************************
* Less than operator
**************************************************************************************************/
template <typename Type>
inline bool Array<Type>::Iterator::operator<(const Iterator& rhs) const {
	return data < &*rhs;
}

/**************************************************************************************************
* Greater than operator
**************************************************************************************************/
template <typename Type>
inline bool Array<Type>::Iterator::operator>(const Iterator& rhs) const {
	return data > &*rhs;
}

/**************************************************************************************************
* Less than or equals operator
**************************************************************************************************/
template <typename Type>
inline bool Array<Type>::Iterator::operator<=(const Iterator& rhs) const {
	return data <= &*rhs;
}

/**************************************************************************************************
* Greater than or equals operator
**************************************************************************************************/
template <typename Type>
inline bool Array<Type>::Iterator::operator>=(const Iterator& rhs) const {
	return data >= &*rhs;
}