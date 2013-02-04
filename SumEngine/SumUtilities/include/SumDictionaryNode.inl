/**************************************************************************************************
* Title: SumDictionaryNode.inl
* Author: Gael Huber
* Description: Defines a node in the dictionary
**************************************************************************************************/

/**************************************************************************************************
* Constructor
**************************************************************************************************/
template <typename Key, typename Value>
Dictionary<Key, Value>::Node::Node(void) 
	: parent(0), left(0), right(0), color(RED), empty(true)
{ }

/**************************************************************************************************
* Constructor specifying pair and the parent
**************************************************************************************************/
template <typename Key, typename Value>
Dictionary<Key, Value>::Node::Node(const Pair& d) 
	: parent(0), left(0), right(0), data(d), color(RED), empty(false)
{ }

/**************************************************************************************************
* Copy-construtor
**************************************************************************************************/
template <typename Key, typename Value>
Dictionary<Key, Value>::Node::Node(const Node& rhs) 
	: parent(rhs.getParent()), left(rhs.getLeft()), right(rhs.getRight()), data(rhs.getData()),
	color(rhs.getColor()), empty(rhs.getEmpty())
{ }

/**************************************************************************************************
* Destructor
**************************************************************************************************/
template <typename Key, typename Value>
Dictionary<Key, Value>::Node::~Node(void) {
	// Delete any external leaves if they exist and are attached to this node
	if(left != 0 && this == left->getParent()) { //Dictionary::_isNil(left)) {
		delete left;
	}
	if(right != 0 && this == right->getParent()) { //Dictionary::_isNil(right)) {
		delete right;
	}

	parent = 0;
	left = 0;
	right = 0;
}

/**************************************************************************************************
* Return the parent node
**************************************************************************************************/
template <typename Key, typename Value>
typename Dictionary<Key, Value>::Node* Dictionary<Key, Value>::Node::getParent(void) const {
	return parent;
}

/**************************************************************************************************
* Set the parent node
**************************************************************************************************/
template <typename Key, typename Value>
void Dictionary<Key, Value>::Node::setParent(typename Dictionary<Key, Value>::Node* p) {
	parent = p;
}

/**************************************************************************************************
* Return the left child
**************************************************************************************************/
template <typename Key, typename Value>
typename Dictionary<Key, Value>::Node* Dictionary<Key, Value>::Node::getLeft(void) const {
	return left;
}

/**************************************************************************************************
* Set the left child
**************************************************************************************************/
template <typename Key, typename Value>
void Dictionary<Key, Value>::Node::setLeft(typename Dictionary<Key, Value>::Node* l) {
	left = l;
	if(left)
		l->setParent(this);
}

/**************************************************************************************************
* Return the right child
**************************************************************************************************/
template <typename Key, typename Value>
typename Dictionary<Key, Value>::Node* Dictionary<Key, Value>::Node::getRight(void) const {
	return right;
}

/**************************************************************************************************
* Set the right child
**************************************************************************************************/
template <typename Key, typename Value>
void Dictionary<Key, Value>::Node::setRight(typename Dictionary<Key, Value>::Node* r) {
	right = r;
	if(right)
		right->setParent(this);
}

/**************************************************************************************************
* Returns the grandparent of this node if it exists
**************************************************************************************************/
template <typename Key, typename Value>
typename Dictionary<Key, Value>::Node* Dictionary<Key, Value>::Node::getGrandparent(void) {
	// Return the grandparent if the parent exists, otherwise return 0
	if(parent != 0) {
		return parent->getParent();
	} else {
		return 0;
	}
}

/**************************************************************************************************
* Returns the uncle of this node if it exists
**************************************************************************************************/
template <typename Key, typename Value>
typename Dictionary<Key, Value>::Node* Dictionary<Key, Value>::Node::getUncle(void) {
	Node* g = getGrandparent();

	// If there is no grandparent, we can't have an uncle
	if(g == 0) {
		return 0;
	}

	// If the parent is equal to the grandparent's left child, choose the right child
	if(parent == g->getLeft()) {
		return g->getRight();
	} else {
		// Otherwise, choose the left child
		return g->getLeft();
	}
}

/**************************************************************************************************
* Returns the sibling of this node
**************************************************************************************************/
template <typename Key, typename Value>
typename Dictionary<Key, Value>::Node* Dictionary<Key, Value>::Node::getSibling(void) {
	// If there is no parent, there can be no sibling
	if(parent == 0)
		return 0;

	// Otherwise return sibling
	return ((this == parent->getRight()) ? parent->getLeft() : parent->getRight());
}

/**************************************************************************************************
* Return the data held within the node
**************************************************************************************************/
template <typename Key, typename Value>
const typename Dictionary<Key, Value>::Pair& Dictionary<Key, Value>::Node::getData(void) const {
	return data;
}

/**************************************************************************************************
* Return non-const version of data held within the node
**************************************************************************************************/
template <typename Key, typename Value>
typename Dictionary<Key, Value>::Pair& Dictionary<Key, Value>::Node::getData(void) {
	return data;
}

/**************************************************************************************************
* Set the value associated with this pair
**************************************************************************************************/
template <typename Key, typename Value>
void Dictionary<Key, Value>::Node::setData(const Pair& d) {
	data = d;
	empty = false;
}


/**************************************************************************************************
* Return the color of the node
**************************************************************************************************/
template <typename Key, typename Value>
const typename Dictionary<Key, Value>::Node::Color Dictionary<Key, Value>::Node::getColor(void) const {
	return color;
}

/**************************************************************************************************
* Set the color of the node
**************************************************************************************************/
template <typename Key, typename Value>
void Dictionary<Key, Value>::Node::setColor(const Color value) {
	color = value;
}

/**************************************************************************************************
* Returns whether the node is empty
**************************************************************************************************/
template <typename Key, typename Value>
const bool Dictionary<Key, Value>::Node::isEmpty(void) const {
	return empty;
}