/**************************************************************************************************
* Title: SumListIterator.inl
* Author: Gael Huber
* Description: Bidirectional list iterator
**************************************************************************************************/

/**************************************************************************************************
* Default constructor
**************************************************************************************************/
template <typename Type>
inline List<Type>::Iterator::Iterator(void)
	: n(0)
{ }

/**************************************************************************************************
* Constructor given list information
**************************************************************************************************/
template <typename Type>
inline List<Type>::Iterator::Iterator(Node* n)
	: n(n)
{ }

/**************************************************************************************************
* Copy constructor
**************************************************************************************************/
template <typename Type>
inline List<Type>::Iterator::Iterator(const Iterator& rhs)
	: n(reinterpret_cast<Node*>(reinterpret_cast<unsigned int>(&*rhs)))
{ }

/**************************************************************************************************
* Destructor
**************************************************************************************************/
template <typename Type>
inline List<Type>::Iterator::~Iterator(void) {
	n = 0;
}

/**************************************************************************************************
* Assignment operator
**************************************************************************************************/
template <typename Type>
inline typename List<Type>::Iterator& List<Type>::Iterator::operator=(const Iterator& rhs) {
	if(this == &rhs)
		return *this;

	n = reinterpret_cast<Node*>(reinterpret_cast<void*>(&*rhs));
	return *this;
}

/**************************************************************************************************
* Equality operator
**************************************************************************************************/
template <typename Type>
inline bool List<Type>::Iterator::operator==(const Iterator& rhs) const {
	return (reinterpret_cast<Node*>(reinterpret_cast<void*>(&*rhs)) == n) ? true : false;
}

/**************************************************************************************************
* Inequality operator
**************************************************************************************************/
template <typename Type>
inline bool List<Type>::Iterator::operator!=(const Iterator& rhs) const {
	return (reinterpret_cast<Node*>(reinterpret_cast<void*>(&*rhs)) == n) ? false : true;
}

/**************************************************************************************************
* Dereference operator to return value
**************************************************************************************************/
template <typename Type>
inline Type& List<Type>::Iterator::operator*(void) const {
	return n->data;
}

/**************************************************************************************************
* Dereference operator to return pointer to object
**************************************************************************************************/
template <typename Type>
inline Type* List<Type>::Iterator::operator->(void) const {
	return &**this;
}

/**************************************************************************************************
* Pre-increment
**************************************************************************************************/
template <typename Type>
inline typename List<Type>::Iterator& List<Type>::Iterator::operator++(void) {
	n = n->next;
	return *this;
}

/**************************************************************************************************
* Post-increment
**************************************************************************************************/
template <typename Type>
inline typename List<Type>::Iterator List<Type>::Iterator::operator++(int rhs) {
	Iterator itr = *this;
	++*this;
	return itr;
}

/**************************************************************************************************
* Pre-decrement
**************************************************************************************************/
template <typename Type>
inline typename List<Type>::Iterator& List<Type>::Iterator::operator--(void) {
	n = n->prev;
	return *this;
}
/**************************************************************************************************
* Post-decrement
**************************************************************************************************/
template <typename Type>
inline typename List<Type>::Iterator List<Type>::Iterator::operator--(int rhs) {
	Iterator itr = *this;
	--*this;
	return itr;
}

/**************************************************************************************************
* Return the node
**************************************************************************************************/
template <typename Type>
inline typename List<Type>::Node* List<Type>::Iterator::nodePtr(void) const {
	return n;
}