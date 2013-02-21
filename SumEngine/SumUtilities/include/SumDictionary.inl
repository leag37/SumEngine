/**************************************************************************************************
* Title: SumDictionary.inl
* Author: Gael Huber
* Description: Defines a templated dictionary. The dictionary is implemented in the form of a
*	specialized tree of objects.
**************************************************************************************************/

/**************************************************************************************************
* Constructor
**************************************************************************************************/
template <typename Key, typename Value>
Dictionary<Key, Value>::Dictionary(void) 
	: dictionary(0), size(0)
{ }

/**************************************************************************************************
* Copy-constructor
**************************************************************************************************/
template <typename Key, typename Value>
Dictionary<Key, Value>::Dictionary(const Dictionary<Key, Value>& rhs) 
	: dictionary(0), size(0)
{
	// Iterate through the tree being copied and insert all objects
	for(Dictionary<Key, Value>::Iterator itr = rhs.begin(); itr != end(); ++itr) {
		insert((*itr).getKey(), (*itr).getValue());
	}
}

/**************************************************************************************************
* Destructor
**************************************************************************************************/
template <typename Key, typename Value>
Dictionary<Key, Value>::~Dictionary(void) {
	// Call clear to empty the data structure
	clear();
}

/**************************************************************************************************
* Assignment operator
**************************************************************************************************/
template <typename Key, typename Value>
const Dictionary<Key, Value>& Dictionary<Key, Value>::operator=(const Dictionary<Key, Value>& rhs) {
	// Clear current contents
	clear();
	
	// Iterate through the tree being copied and insert all objects
	for(Dictionary<Key, Value>::Iterator itr = begin(); itr != end(); ++itr) {
		insert((*itr).getKey(), (*itr).getValue());
	}

	// Return the result
	return *this;
}

/**************************************************************************************************
* Equivalence
**************************************************************************************************/
template <typename Key, typename Value>
const bool Dictionary<Key, Value>::operator==(const Dictionary<Key, Value>& rhs) const {
	// First check to see if sizes are the same, if not return false
	if(size != rhs.getSize()) {
		return false;
	}
	
	// Iterate through the tree and see if all key-value pairs match
	Dictionary<Key, Value>::Iterator t0 = begin();
	Dictionary<Key, Value>::Iterator t1 = rhs.begin();

	while(t0 != end()) {
		// If either the keys are not equal or the values associated with the keys are not equal, the 
		// dictionaries are not the same
		if(((*t0).getKey() != (*t1).getKey()) || ((*t0).getValue() != (*t1).getValue())) {
			return false;
		}

		// Icremement both iterators
		++t0;
		++t1;
	}
	
	// All pairs matched, so return true
	return true;
}

/**************************************************************************************************
* Non-equivalence
**************************************************************************************************/
template <typename Key, typename Value>
const bool Dictionary<Key, Value>::operator!=(const Dictionary<Key, Value>& rhs) const {
		// First check to see if sizes are the same, if not return true
	if(size != rhs.getSize()) {
		return true;
	}
	
	// Iterate through the tree and see if all key-value pairs match
	Dictionary<Key, Value>::Iterator t0 = begin();
	Dictionary<Key, Value>::Iterator t1 = rhs.begin();

	while(t0 != end()) {
		// If either the keys are not equal or the values associated with the keys are not equal, the 
		// dictionaries are not the same
		if(((*t0).getKey() != (*t1).getKey()) || ((*t0).getValue() != (*t1).getValue())) {
			return true;
		}

		// Icremement both iterators
		++t0;
		++t1;
	}
	
	// All pairs matched, so return true
	return false;

	return true;
}

/**************************************************************************************************
* Iterator to begin
**************************************************************************************************/
template <typename Key, typename Value>
const typename Dictionary<Key, Value>::Iterator Dictionary<Key, Value>::begin(void) const {
	return Iterator(Dictionary::_leftMost(dictionary));
}

/**************************************************************************************************
* Iterator to end
**************************************************************************************************/
template <typename Key, typename Value>
const typename Dictionary<Key, Value>::Iterator Dictionary<Key, Value>::end(void) const {
	return Iterator(0);
}

/**************************************************************************************************
* Return whether the dictionary is empty
**************************************************************************************************/
template <typename Key, typename Value>
const bool Dictionary<Key, Value>::empty(void) const {
	return ((size == 0) ? true : false);
}

/**************************************************************************************************
* Return size
**************************************************************************************************/
template <typename Key, typename Value>
const unsigned int Dictionary<Key, Value>::getSize(void) const {
	return size;
}

/**************************************************************************************************
* Array-based accessor (inserts if it cannot find)
**************************************************************************************************/
template <typename Key, typename Value>
Value& Dictionary<Key, Value>::operator[](const Key& rhs) {
	// Attempt to find the value
	Iterator itr = find(rhs);

	// If the key does not exist, add it to the dictionary
	if(itr == end()) {
		itr = insert(rhs, Value());
	}

	// Return the value as a non-const
	return const_cast<Value&>((*itr).getValue());
}

/**************************************************************************************************
* Insert element
**************************************************************************************************/
template <typename Key, typename Value>
const typename Dictionary<Key, Value>::Iterator Dictionary<Key, Value>::insert(const Key& key, const Value& value) {
	// Create a node (with accompanying leaves) to insert and follow standard insertion method
	Pair p = Pair(key, value);

	// Node that we will probe with
	Node* n = dictionary;

	// If the root is zero, set as head
	if(n == 0) {
		n = new Node(p);
		dictionary = n;
	} else {
		// Search until we find a leaf
		while(!n->isEmpty()) {		
			// If the key is less than the current key, go left
			if(key < n->getData().getKey()) {
				n = n->getLeft();
			} else {
				// Go right
				n = n->getRight();
			}
		}

		// If the current node is empty, we have found a leaf
		if(n->isEmpty()) {
			// Set the data
			n->setData(p);

			// Change the color to red
			n->setColor(Node::RED);			
		}
	}

	// Node to return
	Node* toReturn = n;

	// We have finished our insertion so create new leaves
	Node* l = new Node();
	l->setColor(Node::BLACK);
	Node* r = new Node();
	r->setColor(Node::BLACK);
	n->setLeft(l);
	n->setRight(r);

	// We must now insure the itegrity of the tree, so we must go through the various cases starting
	// with the first one
	unsigned int insertCase = 1;
	Node* g = 0;	// Grandparent node
	Node* u = 0;	// Uncle node
	
	// Keep going until we no longer have an insert case
	while(insertCase > 0) {
		switch(insertCase) {
		// The current node is the root of the tree
		case 1:
			// If the current node is the root, paint the node black
			if(n->getParent() == 0) {
				n->setColor(Node::BLACK);
				insertCase = 0;
			} else {
				// Otherwise, we are not at the root and must continue to check tree integrity
				insertCase = 2;
			}
			break;

		// Check whether the current node's parent is black
		case 2:
			// If the node's parent is black, our tree is valid
			if(n->getParent()->getColor() != Node::BLACK) {
				// Otherwise, we must make sure our properties are not threatened
				insertCase = 3;
			} else {
				insertCase = 0;
			}
			break;
		
		// If both parent and uncle are red, both should become black
		case 3:
			// If both P and U are red, the both of them can be repainted black and G becomes red. This 
			// maintains property 5.
			u = n->getUncle();
	
			if((u != 0) && (u->getColor() == Node::RED)) {
				// Change the parent and uncle to black
				u->setColor(Node::BLACK);
				n->getParent()->setColor(Node::BLACK);

				// Change the grandparent to red
				g = n->getGrandparent();
				g->setColor(Node::RED);

				// Check whether the grandparent is the root, if we are the grandparent cannot be red
				n = g;
				insertCase = 1;

			} else {
				// We must continue to check the validity of the tree
				insertCase = 4;
			}
			break;
		
		// The parent is red but the uncle is black, perform a left rotation
		case 4:
			// Get the grandparent
			g = n->getGrandparent();

			// If n is the right child of its parent and the parent is the left child of the grandparent,
			// we must perform a left rotation and set n equal to its left child
			if((n == n->getParent()->getRight()) && (n->getParent() == g->getLeft())) {
				rotate_left(n->getParent());
				n = n->getLeft();
			} else if((n == n->getParent()->getLeft()) && (n->getParent() == g->getRight())) {
				// Otherwise if n is the parent's left child and the parent is the grandparent's right child, 
				// perform a right rotation and set n equal to its right child
				rotate_right(n->getParent());
				n = n->getRight();
			}

			// Check the validity of the tree
			insertCase = 5;

			break;
		
		// The parent is red but the uncle is black, perform a right rotation
		case 5:
			// Get the grandparent
			g = n->getGrandparent();

			// Set the parent's color to black and the grandparent to red
			n->getParent()->setColor(Node::BLACK);
			g->setColor(Node::RED);

			// If the n is left child and the parent is the left child, rotate the grandparent right
			if(n == n->getParent()->getLeft()) { // && (n->getParent() == g->getLeft())) {
				rotate_right(g);
			} else { // if((n == n->getParent()->getRight()) && (n->getParent() == g->getRight())) {
				// Otherwise if n is the right child and the parent is the right child, rotate the grandparent left
				rotate_left(g);
			}

			// No more insert cases to go through
			insertCase = 0;

			break;
		}
	}

	// We have shuffled, so make sure that the dictionary points to the root
	while(dictionary->getParent() != 0) {
		dictionary = dictionary->getParent();
	}

	// Icremement the count
	++size;

	// Return a matching iterator
	return Iterator(toReturn);
}

/**************************************************************************************************
* Erase element based on key
**************************************************************************************************/
template <typename Key, typename Value>
void Dictionary<Key, Value>::erase(const Key& key) {
	// Find the node with the relevant key
	Iterator successor = find(key);
	
	// Only procede if the node is valid
	if(successor == end()) {
		return;
	}

	// Assign the proper successor node and the node to delete
	Iterator toDelete = successor++;

	// Save the node to erased
	Node* deleteNode = reinterpret_cast<Node*>(reinterpret_cast<unsigned int>(&*toDelete));
	Node* child = 0;
	
	// While we need to delete
	bool checkDelete = true;
	while(checkDelete) {
		// If toDelete is a leaf, we must just delete it
		if(Dictionary::_isLeaf(deleteNode)) {
			// If it is the root, set root to 0
			if(deleteNode->getParent() == 0) {
				child = 0;
			}
			// If left child, assign one of the external leaves to the parent
			else if(deleteNode == deleteNode->getParent()->getLeft()) {
				child = deleteNode->getLeft();
				deleteNode->getParent()->setLeft(deleteNode->getLeft());
			} else {
				child = deleteNode->getRight();
				deleteNode->getParent()->setRight(deleteNode->getRight());
			}

			checkDelete = false;
		 }
		// Otherwise, if toDelete only has one child we just move the child up
		else if(Dictionary::_isNil(deleteNode->getRight()) || Dictionary::_isNil(deleteNode->getLeft())) {
			// Get the non-nil child
			child = (Dictionary::_isNil(deleteNode->getRight())) ? deleteNode->getLeft() : deleteNode->getRight();
		
			// If child will be the new root, just set it's parent as 0
			if(deleteNode->getParent() == 0) {
				child->setParent(0);
			}
			// If it is the right child, we move the right child up
			else if(deleteNode == deleteNode->getParent()->getRight()) {
				deleteNode->getParent()->setRight(child);
			}
			// Otherwise, we move the left child up
			else {
				deleteNode->getParent()->setLeft(child);
			}
			checkDelete = false;
		}
		// Otherwise we have two valid children and must use the successor node
		else {
			// Replace the node to delete with the successor's information
			Node* successorNode = reinterpret_cast<Node*>(reinterpret_cast<unsigned int>(&*successor));

			// Swap the data
			deleteNode->getData().swap(successorNode->getData());

			// If successor is a leaf, we have no problems and can just delete successor, otherwise we must
			// do another iteration of deletion on the successor node. 
			if(Dictionary::_isLeaf(successorNode)) {
				checkDelete = false;
			}

			// We are now looking at the successor node as the node to be deleted
			toDelete = successorNode;
		}
	}

	// If the node's color is black check whether the child node is red, otherwise we must ensure the
	// tree's validity down the line
	unsigned int deleteCase = 0;
	if(deleteNode->getColor() == Node::BLACK && child) {
		if(child->getColor() == Node::RED) {
			child->setColor(Node::BLACK);
		} else {
			deleteCase = 1;
		}
	}

	// Prepare pointers for any relevant relatives
	Node* s = 0;	// Sibling node
	Node* n = child;	// Node on which the operations are being performed

	// Check the variuos delete cases
	while(deleteCase > 0) {
		switch(deleteCase) {
		// n is the new root. In this case, nothing needs to be done and the tree is valid.
		case 1:
			if(n->getParent() == 0) {
				deleteCase = 0;
			} else {
				deleteCase = 2;
			}
			break;

		// If the sibling node is red while this node is black, reverse the colors of the parent and the
		// sibling. Then we rotate left at the parent turning the sibling into n's grandparent. The
		// parent MUST be black as it has a red child.
		case 2:
			// Get the sibling node
			s = n->getSibling();

			// Check whether the sibling is red
			if(s->getColor() == Node::RED) {
				// Set the parent node to red and the sibling color to black
				n->getParent()->setColor(Node::RED);
				s->setColor(Node::BLACK);

				if(n == n->getParent()->getLeft()) {
					rotate_left(deleteNode->getParent());
				} else {
					rotate_right(deleteNode->getParent());
				}
			}

			// Move on to the third case
			deleteCase = 3;
			break;

		// Parent, sibling, and sibling's children are black so repaint sibling as red. This results in
		// all paths passing through sibling (i.e. not through n) to have one less black node. Deleting
		// n's parent made all paths passing through n have one less black node so this rebalances the
		// tree. However, all paths that pass through the parent now have one fewer black nodes than
		// paths that do not pass through parent, so rebalance starting on the parent.
		case 3:
			// Get the sibling
			s = n->getSibling();

			// Check for blackness of parent, sibling, and sibling's children
			if((n->getParent()->getColor() == Node::BLACK) &&
				(s->getColor() == Node::BLACK) &&
				(s->getLeft()->getColor() == Node::BLACK) &&
				(s->getRight()->getColor() == Node::BLACK)) {
				// Set s to red and rebalance
				s->setColor(Node::RED);
				n = n->getParent();
				deleteCase = 1;
			} else {
				deleteCase = 4;
			}
			break;

		// If sibling and sibling's children are black but the parent is red, we simply swap the colors
		// of the sibling with the parent. This makes up for having one less black node in the deleted
		// path.
		case 4:
			// Get the sibling
			s = n->getSibling();

			if(s == 0) {
				deleteCase = 0;
			}
			// Make our checks
			else if((n->getParent()->getColor() == Node::RED) &&
				(s->getLeft() && s->getLeft()->getColor() == Node::BLACK) && 
				(s->getRight() && s->getRight()->getColor() == Node::BLACK) &&
				(s->getColor() == Node::BLACK)) {
				// Swap parent and sibling colors
				n->getParent()->setColor(Node::BLACK);
				s->setColor(Node::RED);
				deleteCase = 0;
			} else  {
				deleteCase = 5;
			}
			break;

		// Sibling is black, but siblings left child is red while the right child is black. Additionally,
		// n is the left child of sibling's parent. We can rotate right at sibling and swap colors with
		// its new parent. However, this causes n to have a black sibling whose right child is red, so
		// we cannot guarantee the validity of our tree.
		case 5:
			// Get the sibling node
			s = n->getSibling();

			// Ensure we can cause case 6 to rotate properly
			if(s->getColor() == Node::BLACK) {
				// Perform our major checks
				if(s->getRight() && s->getLeft()) {
					if((n == n->getParent()->getLeft()) &&
						(s->getRight()->getColor() == Node::BLACK) &&
						(s->getLeft()->getColor() == Node::RED)) {
						// Exchange sibling's color with its left child and rotate right
						s->setColor(Node::RED);
						s->getLeft()->setColor(Node::BLACK);
						rotate_right(s);
					} else if((n == n->getParent()->getRight()) &&
						(s->getLeft()->getColor() == Node::BLACK) &&
						(s->getRight()->getColor() == Node::RED)) {
						// Exchange sibling's color with its right child and rotate left
						s->setColor(Node::RED);
						s->getRight()->setColor(Node::BLACK);
						rotate_left(s);
					}
				}
			}

			// Move onto case 6
			deleteCase = 6;
			break;

		// Sibling is black, sibling's right child is red, n is the left child of the parent. In this
		// case, we rotate left at the parent. Swap colors between the sibling and the parent and make
		// the sibling's right child black. 
		case 6:
			// Get the sibling
			s = n->getSibling();

			// Swap sibling's color with the parent
			s->setColor(n->getParent()->getColor());
			n->getParent()->setColor(Node::BLACK);

			// If n is the left child, the sibling's right child becomes black and rotate left on the parent
			if(n == n->getParent()->getLeft() && s->getRight()) {
				s->getRight()->setColor(Node::BLACK);
				rotate_left(n->getParent());
			} else if(s->getLeft()) {
				// Otherwise the change the sibling's left child to black and rotate right on the parent
				s->getLeft()->setColor(Node::BLACK);
				rotate_right(n->getParent());
			}

			// Last case, finished with rebalancing the tree
			deleteCase = 0;
			break;
		}
	}

	// Finally delete the node
	delete deleteNode;
	deleteNode = 0;

	// We have shuffled, so make sure that the dictionary points to the root (we will reset dictionary
	// since it's entirely possible that dictionary was the deleted node)
	dictionary = child;
	while(dictionary && dictionary->getParent() != 0) {
		dictionary = dictionary->getParent();
	}

	// Decrement the size
	--size;
}

/**************************************************************************************************
* Erase element based on iterator
**************************************************************************************************/
template <typename Key, typename Value>
void Dictionary<Key, Value>::erase(const Iterator& itr) {
	erase((*itr).getKey());
}

/**************************************************************************************************
* Swap contents with another dictionary
**************************************************************************************************/
template <typename Key, typename Value>
void Dictionary<Key, Value>::swap(Dictionary<Key, Value>& rhs) {
	// Make a temporary dictionary equal to the dictionary being passed in
	Dictionary<Key, Value> temp = rhs;

	// Assign this dictionary to rhs
	rhs = *this;;

	// Assign temp to this dictionary
	(*this) = temp;
}

/**************************************************************************************************
* Clear the content of the dictionary
**************************************************************************************************/
template <typename Key, typename Value>
void Dictionary<Key, Value>::clear(void) {
	// As long as there is a valid head node, clear it
	while(dictionary) {
		erase(Dictionary<Key, Value>::Iterator(dictionary));
	}
}

/**************************************************************************************************
* Return an iterator to the value found, if no value is found return an iterator to end
**************************************************************************************************/
template <typename Key, typename Value>
const typename Dictionary<Key, Value>::Iterator Dictionary<Key, Value>::find(const Key& key) const {
	// Find the key and return an iterator to it
	// Start at the head
	Node* n = dictionary;
	Iterator toReturn;

	// Keep searching until we find then node or we reach a leaf
	bool continueSearch = true;
	while(continueSearch) {
		// If the node is a leaf, we we exit the search and set toReturn to 0
		if(Dictionary::_isNil(n)) {
			continueSearch = false;
			toReturn = Iterator(0);
		}
		// We find the key, so we have a matching node and set toReturn to the corresponding node
		else if(n->getData().getKey() == key) {
			continueSearch = false;
			toReturn = Iterator(n);
		} 
		// If the key is less than the key, go left
		else if(key < n->getData().getKey()) {
			n = n->getLeft();
		} 
		// Otherwise, the key is greater than or equal to the current node so go right
		else {
			n = n->getRight();
		}
	}

	// Return the iterator
	return toReturn;
}

/**************************************************************************************************
* Perform a right rotation
**************************************************************************************************/
template <typename Key, typename Value>
void Dictionary<Key, Value>::rotate_right(Node* n) {
	// Let P be N's left child
	Node* p = n->getLeft();

	// Set P to be the new root
	if(n->getParent() == 0) {
		p->setParent(n->getParent());
	} else {
		if(n->getParent()->getRight() == n) {
			n->getParent()->setRight(p);
		} else {
			n->getParent()->setLeft(p);
		}
	}

	// Set N's left child to be P's right child
	n->setLeft(p->getRight());

	// Set P's right child to be N
	p->setRight(n);
}

/**************************************************************************************************
* Perform a left rotation
**************************************************************************************************/
template <typename Key, typename Value>
void Dictionary<Key, Value>::rotate_left(Node* n) {
	// Let Q be N's right child
	Node* q = n->getRight();

	// Set Q to be the new root
	if(n->getParent() == 0) {
		q->setParent(n->getParent());
	} else {
		if(n->getParent()->getRight() == n) {
			n->getParent()->setRight(q);
		} else {
			n->getParent()->setLeft(q);
		}
	}

	// Set N's right child to be Q's left child
	n->setRight(q->getLeft());

	// Set Q's left child to be N
	q->setLeft(n);
}

/**************************************************************************************************
* Replaces n0 with n1 in the tree
**************************************************************************************************/
template <typename Key, typename Value>
void Dictionary<Key, Value>::replace_node(typename Dictionary<Key, Value>::Node* n0,
	typename Dictionary<Key, Value>::Node* n1) {	
	// Set both children
	n1->setLeft(n0->getLeft());
	n1->setRight(n0->getRight());
		
	// Replace n0 with n1 as the root of the subtree
	if(n0->getParent() == 0) {
		n1->setParent(n0->getParent());
	} else {
		if(n0->getParent()->getRight() == n0) {
			n0->getParent()->setRight(n1);
		} else {
			n0->getParent()->setLeft(n1);
		}
	}
}

/**************************************************************************************************
* Returns whether the node is a leaf
**************************************************************************************************/
template <typename Key, typename Value>
const bool Dictionary<Key, Value>::_isLeaf(typename Dictionary<Key, Value>::Node* n) {
	return (Dictionary::_isNil(n->getLeft()) &&  Dictionary::_isNil(n->getRight())) ? true : false;
}

/**************************************************************************************************
* Return the left-most node of this subtree
**************************************************************************************************/
template <typename Key, typename Value>
typename Dictionary<Key, Value>::Node* Dictionary<Key, Value>::_leftMost(typename Dictionary<Key, Value>::Node* n) {
	// Safety check for non-existent node
	if(n == 0)
	{
		return 0;
	}

	// While there is a left child that is not null, go to it
	while(!n->getLeft()->isEmpty()) {
		n = n->getLeft();
	}

	// Return the final node
	return n;
}

/**************************************************************************************************
* Return the right-most node of this subtree
**************************************************************************************************/
template <typename Key, typename Value>
typename Dictionary<Key, Value>::Node* Dictionary<Key, Value>::_rightMost(typename Dictionary<Key, Value>::Node* n) {
	// While there is a right child that is not null, go to it
	while(n->getRight() != 0) {
		n = n->getRight();
	}

	// Return the final node
	return n;
}

/**************************************************************************************************
* Returns whether or not a node is valid (0 and empty are invalid)
**************************************************************************************************/
template <typename Key, typename Value>
const bool Dictionary<Key, Value>::_isNil(typename Dictionary<Key, Value>::Node* n) {
	return (n == 0 || n->isEmpty()) ? true : false;
}