//*************************************************************************************************
// Title: SumForwardListNode.inl
// Author: Gael Huber
// Description: Implements functions for a ForwardList node, such as getters and setters for data
//	and next node.
//*************************************************************************************************

//*************************************************************************************************
// Default constructor
//*************************************************************************************************
template <typename Type>
ForwardList<Type>::Node::Node(void) 
	: next(0)
{ }

/**************************************************************************************************
* Constructor specifying data
**************************************************************************************************/
template <typename Type>
ForwardList<Type>::Node::Node(const Type& d) 
	: next(0), data(d)
{ }

/**************************************************************************************************
* Destructor
**************************************************************************************************/
template <typename Type>
ForwardList<Type>::Node::~Node(void) {
	next = 0;
}

/**************************************************************************************************
* Returns the data
**************************************************************************************************/
template <typename Type>
const Type& ForwardList<Type>::Node::getData(void) const {
	return data;
}

/**************************************************************************************************
* Sets the data
**************************************************************************************************/
template <typename Type>
void ForwardList<Type>::Node::setData(const Type& d) {
	data = d;
}

/**************************************************************************************************
* Returns the next node
**************************************************************************************************/
template <typename Type>
typename ForwardList<Type>::Node* const ForwardList<Type>::Node::getNext(void) const {
	return next;
}

/**************************************************************************************************
* Sets the next node
**************************************************************************************************/
template <typename Type>
void ForwardList<Type>::Node::setNext(Node* n) {
	next = n;
}