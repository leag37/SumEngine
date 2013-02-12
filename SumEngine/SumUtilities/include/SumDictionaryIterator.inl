/**************************************************************************************************
* Title: SumDictionaryIterator.inl
* Author: Gael Huber
* Description: Defines an iterator for the dictionary
**************************************************************************************************/

/**************************************************************************************************
* Default constructor
**************************************************************************************************/
template <typename Key, typename Value>
Dictionary<Key, Value>::Iterator::Iterator(void) 
	: n(0)
{ }

/**************************************************************************************************
* Constructor that binds the dictionary
**************************************************************************************************/
template <typename Key, typename Value>
Dictionary<Key, Value>::Iterator::Iterator(Node* arg) 
	: n(arg)
{ }

/**************************************************************************************************
* Copy-constructor
**************************************************************************************************/
template <typename Key, typename Value>
Dictionary<Key, Value>::Iterator::Iterator(const Iterator& rhs) 
	: n(reinterpret_cast<Node*>(reinterpret_cast<unsigned int>(&*rhs)))
{ }

/**************************************************************************************************
* Destructor
**************************************************************************************************/
template <typename Key, typename Value>
Dictionary<Key, Value>::Iterator::~Iterator(void) 
{
	n = 0;
}

/**************************************************************************************************
* Assignment operator
**************************************************************************************************/
template <typename Key, typename Value>
const typename Dictionary<Key, Value>::Iterator& Dictionary<Key, Value>::Iterator::operator=(const Iterator& rhs) {
	// Self assignment guard
	if(&rhs == this)
		return *this;

	// Assign node
	n = reinterpret_cast<Node*>(reinterpret_cast<unsigned int>(&*rhs));

	// Return this
	return *this;
}

/**************************************************************************************************
* Equivalence
**************************************************************************************************/
template <typename Key, typename Value>
const bool Dictionary<Key, Value>::Iterator::operator==(const Iterator& rhs) const {
	return (reinterpret_cast<Node*>(reinterpret_cast<unsigned int>(&*rhs)) == n) ? true : false;
}

/**************************************************************************************************
* Non-equivalence
**************************************************************************************************/
template <typename Key, typename Value>
const bool Dictionary<Key, Value>::Iterator::operator!=(const Iterator& rhs) const {
	return (reinterpret_cast<Node*>(reinterpret_cast<unsigned int>(&*rhs)) == n) ? false : true;
}

/**************************************************************************************************
* Pre-increment
**************************************************************************************************/
template <typename Key, typename Value>
const typename Dictionary<Key, Value>::Iterator& Dictionary<Key, Value>::Iterator::operator++(void) {
	// First check whether the node is valid, it is valid if it is not a leaf
	if(Dictionary::_isNil(n)) {
		;
	} 
	// Valid, so we want to check for a right subtree. If a right subtree exists, find the minimum of
	// that tree.
	else if(!n->getRight()->isEmpty()) {
		n = Dictionary::_leftMost(n->getRight());
	} 
	// Otherwise, we must climb the tree while n.parent != 0 && n == n.parent.right
	else {
		Node* tNode;
		while(!(Dictionary::_isNil(tNode = n->getParent())) && (n == tNode->getRight())) {
			n = tNode;
		}
		n = tNode;
	}

	// Return the iterator
	return *this;
}

/**************************************************************************************************
* Post-increment
**************************************************************************************************/
template <typename Key, typename Value>
const typename Dictionary<Key, Value>::Iterator Dictionary<Key, Value>::Iterator::operator++(int) {
	// Copy this
	Iterator itr = *this;

	// Increment this
	++*this;

	// Return the unchanged object
	return itr;
}

/**************************************************************************************************
* Pre-decrement
**************************************************************************************************/
template <typename Key, typename Value>
const typename Dictionary<Key, Value>::Iterator& Dictionary<Key, Value>::Iterator::operator--(void) {
	// First check whether the node is valid, it is valid if it is not a leaf
	if(Dictionary::_isNil(n)) {
		;
	} 
	// Valid, so we want to check for a left subtree. If a left subtree exists, find the maximum of
	// that tree.
	else if(!n->getLeft()->isEmpty()) {
		n = Dictionary::_rightMost(n->getLeft());
	} 
	// Otherwise, we must climb the tree while n.parent != 0 && n == n.parent.left
	else {
		Node* tNode;
		while(!(Dictionary::_isNil(tNode = n->getParent())) && (n == tNode->getLeft())) {
			n = tNode;
		}
		n = tNode;
	}

	// Return the iterator
	return *this;
}

/**************************************************************************************************
* Post-decrement
**************************************************************************************************/
template <typename Key, typename Value>
const typename Dictionary<Key, Value>::Iterator Dictionary<Key, Value>::Iterator::operator--(int) {
	// Copy this
	Iterator itr = *this;

	// Increment this
	--*this;

	// Return the unchanged object
	return itr;
}

/**************************************************************************************************
* Return the associated value
**************************************************************************************************/
template <typename Key, typename Value>
const typename Dictionary<Key, Value>::Pair& Dictionary<Key, Value>::Iterator::operator*(void) const {
	return n->getData();
}

/**************************************************************************************************
* Return a pointer to the associated object
**************************************************************************************************/
template <typename Key, typename Value>
const typename Dictionary<Key, Value>::Pair* Dictionary<Key, Value>::Iterator::operator->(void) const {
	return (&**this);
}
