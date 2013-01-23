/**************************************************************************************************
* Title: SumForwardListIterator.inl
* Author: Gael Huber
* Description: List iterator, permits forward iteration through the list.
**************************************************************************************************/

/**************************************************************************************************
* Default constructor
**************************************************************************************************/
template <typename Type>
ForwardList<Type>::Iterator::Iterator(void) 
	: n(0)
{ }

/**************************************************************************************************
* Copy-constructor
**************************************************************************************************/
template <typename Type>
ForwardList<Type>::Iterator::Iterator(const Iterator& rhs) 
	: n(reinterpret_cast<Node*>(reinterpret_cast<unsigned int>(&*rhs)))
{ }

/**************************************************************************************************
* Constructor that binds list
**************************************************************************************************/
template <typename Type>
ForwardList<Type>::Iterator::Iterator(Node* arg) 
	: n(arg)
{ }

/**************************************************************************************************
* Assignment operator
**************************************************************************************************/
template <typename Type>
const typename ForwardList<Type>::Iterator& ForwardList<Type>::Iterator::operator=(const typename ForwardList<Type>::Iterator& rhs) {
	// Self-assignment guard
	if(&rhs == this)
		return *this;

	// Assign node to the same node as rhs
	n = reinterpret_cast<Node*>(reinterpret_cast<unsigned int>(&*rhs));

	return *this;
}

/**************************************************************************************************
* Destructor
**************************************************************************************************/
template <typename Type>
ForwardList<Type>::Iterator::~Iterator(void) 
{ 
	n = 0;
}

/**************************************************************************************************
* Equivalence
**************************************************************************************************/
template <typename Type>
const bool ForwardList<Type>::Iterator::operator==(const Iterator& rhs) const {
	// If the pointers are the same to the data are the same, return true
	return (reinterpret_cast<Node*>(reinterpret_cast<unsigned int>(&*rhs)) == n) ? true : false;
}

/**************************************************************************************************
* Non-equivalence
**************************************************************************************************/
template <typename Type>
const bool ForwardList<Type>::Iterator::operator!=(const Iterator& rhs) const {
	// If the pointers are the same to the data are the same, return false
	return (reinterpret_cast<Node*>(reinterpret_cast<unsigned int>(&*rhs)) == n) ? false : true;
}

/**************************************************************************************************
* Pre-increment
**************************************************************************************************/
template <typename Type>
const typename ForwardList<Type>::Iterator& ForwardList<Type>::Iterator::operator++(void) {
	// Move forward
	n = n->getNext();

	// Return this
	return *this;
}

/**************************************************************************************************
* Post-increment
**************************************************************************************************/
template <typename Type>
const typename ForwardList<Type>::Iterator ForwardList<Type>::Iterator::operator++(int rhs) {
	// Create a temporary iterator equal to the current iterator
	Iterator itr = *this;

	// Icremement this iterator
	++*this;// n = n->getNext();

	// Return the copy
	return itr;
}

/**************************************************************************************************
* Return the value
**************************************************************************************************/
template <typename Type>
inline const Type& ForwardList<Type>::Iterator::operator*(void) const {
	return n->getData();
}

/**************************************************************************************************
* Return pointer to the class object
**************************************************************************************************/
template <typename Type>
const Type* ForwardList<Type>::Iterator::operator->(void) const {
	return &**this;
}
