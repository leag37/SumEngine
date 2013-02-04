/**************************************************************************************************
* Title: SumList.inl
* Author: Gael Huber
* Description: Main container for the list and all major functionality
**************************************************************************************************/

/**************************************************************************************************
* Default constructor
**************************************************************************************************/
template <typename Type>
inline List<Type>::List(void)
	: head(new Node()), _size(0)
{ }

/**************************************************************************************************
* Copy constructor
**************************************************************************************************/
template <typename Type>
List<Type>::List(const List<Type>& rhs) 
	: head(new Node()), _size(0)
{
	// Push all elements in the existing list to the new list
	Iterator e = rhs.end();
	for(Iterator itr = rhs.begin(); itr != e; ++itr) {
		push_back(*itr);
	}
}

/**************************************************************************************************
* Destructor
**************************************************************************************************/
template <typename Type>
List<Type>::~List(void) {
	// Delete all nodes in the list
	Node* curr = head->next;

	while(curr != head) {
		curr = curr->next;
		delete curr->prev;
	}
	
	delete head;
}

/**************************************************************************************************
* Assignment operator
**************************************************************************************************/
template <typename Type>
List<Type>& List<Type>::operator=(const List<Type>& rhs) {
	// Self-assignment guard
	if(this == &rhs)
		return *this;

	// Delete old content
	clear();

	// Add new content
	Iterator e = rhs.end();
	for(Iterator itr = rhs.begin(); itr != e; ++itr) {
		push_back(*itr);
	}
}

/**************************************************************************************************
* Equivalence operator
**************************************************************************************************/
template <typename Type>
bool List<Type>::operator==(const List<Type>& rhs) const {
	// Check size
	if(_size != rhs.size())
		return false;

	// Size check passed, match contents
	Iterator itr1 = begin();
	Iterator thisEnd = end();
	Iterator itr2 = rhs.begin();

	while(itr1 != thisEnd) {
		if(*itr1 != *itr2) {
			return false;
		}
		++itr1;
		++itr2;
	}

	// All values matched, must be true
	return true;
}

/**************************************************************************************************
* Non-equivalence operator
**************************************************************************************************/
template <typename Type>
bool List<Type>::operator!=(const List<Type>& rhs) const {
	// Check size
	if(_size != rhs.size())
		return true;

	// Size check passed, match contents
	Iterator itr1 = begin();
	Iterator thisEnd = end();
	Iterator itr2 = rhs.begin();

	while(itr1 != thisEnd) {
		if(*itr1 != *itr2) {
			return true;
		}
		++itr1;
		++itr2;
	}

	// All values matched, must be true
	return false;
}

/**************************************************************************************************
* Return an iterator pointing to the beginning of the list
**************************************************************************************************/
template <typename Type>
inline typename List<Type>::Iterator List<Type>::begin(void) const {
	return Iterator(head->next);
}

/**************************************************************************************************
* Return an iterator pointing to the end of the list
**************************************************************************************************/
template <typename Type>
inline typename List<Type>::Iterator List<Type>::end(void) const {
	return Iterator(head);
}

/**************************************************************************************************
* Test whether the list is empty
**************************************************************************************************/
template <typename Type>
inline bool List<Type>::empty(void) const {
	return _size == 0;
}

/**************************************************************************************************
* Return the size of the list
**************************************************************************************************/
template <typename Type>
inline int List<Type>::size(void) const {
	return _size;
}

/**************************************************************************************************
* Increase the size of the list by a given amount
**************************************************************************************************/
template <typename Type>
inline void List<Type>::_incSize(int inc) {
	_size += inc;
}

/**************************************************************************************************
* Access the first element
**************************************************************************************************/
template <typename Type>
inline Type& List<Type>::front(void) {
	return head->next->data;
}

/**************************************************************************************************
* Access the last element
**************************************************************************************************/
template <typename Type>
inline Type& List<Type>::back(void) {
	return head->prev->data;
}

/**************************************************************************************************
* Assign new content to the container. The data is everything that exists between first and last
* inclusive. The current contents of the list are erased.
**************************************************************************************************/
template <typename Type>
void List<Type>::assign(const Iterator& first, const Iterator& last) {
	// Clear the contents of the list
	clear();

	// Add the new contents to the list
	for(Iterator itr = first; itr <= last, ++itr) {
		push_back(*itr);
	}
}

/**************************************************************************************************
* Assign the content of the container to be n copies of a specified value. The current contents of
* the list are erased.
**************************************************************************************************/
template <typename Type>
void List<Type>::assign(int n, const Type& val) {
	// Clear the current contents
	clear();

	// Add n copies of the new value
	for(int i = 0; i < n; ++i) {
		push_back(val);
	}
}

/**************************************************************************************************
* Push a value at the front of the list
**************************************************************************************************/
template <typename Type>
inline void List<Type>::push_front(const Type& val) {
	// Create the new node with links in place
	Node* n = new Node(val, head->next, head);

	// Fix existing links
	head->next->prev = n;
	head->next = n;

	++_size;
}

/**************************************************************************************************
* Pop a value from the front of the list
**************************************************************************************************/
template <typename Type>
void List<Type>::pop_front(void) {
	// Verify that we can delete from the list
	if(size() == 0)
		return;

	// We have a valid first node, so we can pull out the node to delete
	Node* n = head->next;

	// Fix links
	head->next = n->next;
	n->next->prev = head;

	// Delete the node
	delete n;

	--_size;
}

/**************************************************************************************************
* Push a value at the back of the list
**************************************************************************************************/
template <typename Type>
inline void List<Type>::push_back(const Type& val) {
	// Create the new node
	Node* n = new Node(val, head, head->prev);

	// Fix existing links
	head->prev->next = n;
	head->prev = n;

	++_size;
}

/**************************************************************************************************
* Pop a value from the back of the list
**************************************************************************************************/
template <typename Type>
void List<Type>::pop_back(void) {
	// Verify that we have items to pop
	if(size() == 0)
		return;

	// Pull out item to pop
	Node* n = head->prev;

	// Fix links
	n->prev->next = head;
	head->prev = n->prev;

	// Delete node
	delete n;

	--_size;
}

/**************************************************************************************************
* Insert an element into the list. Return an iterator pointing to newly inserted element.
**************************************************************************************************/
template <typename Type>
typename List<Type>::Iterator List<Type>::insert(typename List<Type>::Iterator position, const Type& val) {
	// Acquire the position node
	Node* p = reinterpret_cast<Node*>(reinterpret_cast<unsigned int>(&*position));

	// Create a new node and insert it
	Node* n = new Node(val, p, p->prev);

	// Fix existing links
	p->prev->next = n;
	p->prev = n;

	++_size;

	return Iterator(n);
}

/**************************************************************************************************
* Insert n copies of val into the list
**************************************************************************************************/
template <typename Type>
void List<Type>::insert(typename List<Type>::Iterator position, int n, const Type& val) {
	// Acquire insert position
	Node* p = reinterpret_cast<Node*>(reinterpret_cast<unsigned int>(&*position));

	// Create n new nodes and insert them
	for(int i = 0; i < n; ++i) {
		// Create a new node
		Node* n = new Node(val, p, p->prev);

		// Fix existing links
		p->prev->next = n;
		p->prev = n;

		// Shift p forward
		p = p->next;
	}

	_size += n;
}

/**************************************************************************************************
* Erase a value from the list. Return the new value at this position in the list (if erasing last
* element, the iterator would point to end)
**************************************************************************************************/
template <typename Type>
typename List<Type>::Iterator List<Type>::erase(typename List<Type>::Iterator position) {
	// If iterator is end, fail by returning same iterator
	if(position == end())
		return position;

	// Acquire node at delete position
	Node* p = reinterpret_cast<Node*>(reinterpret_cast<unsigned int>(&*position));
	Node* toDelete = p;

	// Delete the node
	p->prev->next = p->next;
	p->next->prev = p->prev;
	p = p->next;
	delete toDelete;

	--_size;

	return Iterator(p);
}

/**************************************************************************************************
* Erase all values within the specified range, excluding last.
**************************************************************************************************/
template <typename Type>
typename List<Type>::Iterator List<Type>::erase(typename List<Type>::Iterator first, typename List<Type>::Iterator last) {
	// Erase all nodes within range
	while(first != last) {
		first = erase(first);
	}

	// Return the end of the range
	return last;
}

/**************************************************************************************************
* Clear all contents of the list
**************************************************************************************************/
template <typename Type>
void List<Type>::clear(void) {
	// Set up current node and node to delete
	Node* pNode = head->next;

	// Delete all nodes
	while(pNode != head) {
		head->next = pNode->next;
		delete pNode;
		pNode = head->next;
	}

	// Close off list
	head->next = head;
	head->prev = head;

	_size = 0;
}

/**************************************************************************************************
* Removes all elements from list x and moves them into this list at a specified position
**************************************************************************************************/
template <typename Type>
void List<Type>::splice(typename List<Type>::Iterator position, List<Type>& x) {
	// Iterate through the list and add all values
	Iterator e = x.end();
	for(Iterator itr = x.begin(); itr != e; ++itr) {
		// Insert at the current position
		position = insert(position, *itr);
	}

	// Clear the old list
	x.clear();
}

/**************************************************************************************************
* Removes only element at i from list x and moves it into this list at a specified position
**************************************************************************************************/
template <typename Type>
void List<Type>::splice(typename List<Type>::Iterator position, List<Type>& x, typename List<Type>::Iterator i) {
	// Insert element into current list
	insert(position, *i);

	// Remove from old list
	x.erase(i);
}

/**************************************************************************************************
* Removes all elements from first to last from list x and moves them into this list at a specified 
* position
**************************************************************************************************/
template <typename Type>
void List<Type>::splice(typename List<Type>::Iterator position, List<Type>& x, 
	typename List<Type>::Iterator first, typename List<Type>::Iterator last) {
	// Iterate from first to last
	while(first != last) {
		// Add first to the list
		position = insert(position, *first);
		
		// Increment and remove first from the list
		first = x.erase(first);
	}
}

/**************************************************************************************************
* Removes all elements from list x and moves them into this list without recreating the nodes.
* Instead, the nodes are directly manipulated.
**************************************************************************************************/
template <typename Type>
void List<Type>::_splice_same(typename List<Type>::Iterator position, List<Type>& x) {
	// Adjust list sizes if the lists are not the same
	if(this != &x) {
		_size += x.size();
		x._incSize(-x.size());
	}
	
	// Pull relevant nodes
	Node* pos = position.nodePtr();
	Node* xFirst = x.begin().nodePtr();
	Node* xLast = (--x.end()).nodePtr();

	// Ensure x has node relations properly fixed (i.e. head points to itself)
	x.head->next = x.head;
	x.head->prev = x.head;

	// Insert first
	pos->prev->next = xFirst;
	xFirst->prev = pos->prev;

	// Insert last
	pos->prev = xLast;
	xLast->next = pos;
}

/**************************************************************************************************
* Removes only element at i from list x and moves it into this list at a specified position into 
* this list without recreating the nodes. Instead, the nodes are directly manipulated.
**************************************************************************************************/
template <typename Type>
void _splice_same(typename List<Type>::Iterator position, List<Type>& x, typename List<Type>::Iterator i) {
	// Adjust list sizes
	if(this != &x) {
		++_size;
		x._incSize(-1);
	}

	// Remove node from other list
	i.nodePtr()->prev->next = i.nodePtr()->next;
	i.nodePtr()->next->prev = i.nodePtr()->prev;

	//	Insert into this list
	position.nodePtr()->prev->next = i.nodePtr();
	i.nodePtr()->prev = position.nodePtr()->prev;
	position.nodePtr()->prev = i.nodePtr();
	i.nodePtr()->next = position.nodePtr();
}

/**************************************************************************************************
* Removes all elements from first to last from list x and moves them into this list at a given 
* position without creating copies of the data.
**************************************************************************************************/
template <typename Type>
void List<Type>::_splice_same(typename List<Type>::Iterator position, List<Type>& x, 
	typename List<Type>::Iterator first, typename List<Type>::Iterator last, int count) {
	// Fix list sizes
	if(this != &x) {
		x._incSize(-count);
		_size += count;
	}

	// Splice the node into place
	first.nodePtr()->prev->next = last.nodePtr();
	last.nodePtr()->prev->next = position.nodePtr();
	position.nodePtr()->prev->next = first.nodePtr();

	Node* pNode = position.nodePtr()->prev;
	position.nodePtr()->prev = last.nodePtr()->prev;
	last.nodePtr()->prev = first.nodePtr()->prev;
	first.nodePtr()->prev = pNode;
}

/**************************************************************************************************
* Removes all occurrences of an element with the given value
**************************************************************************************************/
template <typename Type>
void List<Type>::remove(const Type& val) {
	Iterator e = end();
	Iterator itr = begin();
	while(itr != e) {
		if(*itr == val) {
			itr = erase(itr);
		} else {
			++itr;
		}
	}
}

/**************************************************************************************************
* Removes any occurrences where the predicate is determined to be true
**************************************************************************************************/
template <typename Type>
template <class Predicate0>
void List<Type>::remove_if(Predicate0 pred) {
	Iterator e = end();
	Iterator itr = begin();
	while(itr != e) {
		if(pred(*itr)) {
			itr = erase(itr);
		} else {
			++itr;
		}
	}
}

/**************************************************************************************************
* Removes all adjacent duplicate values (considering the first occurrence as the "unique" value)
**************************************************************************************************/
template <typename Type>
void List<Type>::unique(void) {
	// Iterate through all nodes
	Node* pNode = head->next;
	Node* pNext;
	for( ; pNode != head; pNode = pNode->next) {
		// If the next node has the same content as this node, delete the next node
		pNext = pNode->next;
		while(pNode->data == pNext->data) {
			pNext = pNext->next;
			erase(Iterator(pNext->prev));
		}
	}
}

/**************************************************************************************************
* Removes all adjacent duplicate values (considering the first occurrence as the "unique" value)
* according to a predicate
**************************************************************************************************/
template <typename Type>
template <class Predicate1>
void List<Type>::unique(Predicate1 pred) {
	// Iterate through all nodes
	Node* pNode = head->next;
	Node* pNext;
	for( ; pNode != head; pNode = pNode->next) {
		// If the next node has the same content as this node, delete the next node
		pNext = pNode->next;
		while(pred(pNode->data, pNext->data)) {
			pNext = pNext->next;
			erase(Iterator(pNext->prev));
		}
	}
}

/**************************************************************************************************
* Removes all duplicate values (does not assume a sorted list)
**************************************************************************************************/
template <typename Type>
void List<Type>::unique_all(void) {
	// Iterate through all nodes
	Node* pNode = head->next;
	for( ; pNode != head; pNode = pNode->next) {
		// Find any duplicates of pNode
		for(Node* pNext = pNode->next; pNext != head; pNext = pNext->next) {
			if(pNode->data == pNext->data) {
				pNext = reinterpret_cast<Node*>(reinterpret_cast<unsigned int>(&*(erase(Iterator(pNext)))))->prev;
			}
		}
	}
}

/**************************************************************************************************
* Removes all duplicate values according to a predicate
**************************************************************************************************/
template <typename Type>
template <class Predicate2>
void List<Type>::unique_all(Predicate2 pred) {
	// Iterate through all nodes
	Node* pNode = head->next;
	for( ; pNode != head; pNode = pNode->next) {
		// Find any duplicates of pNode
		for(Node* pNext = pNode->next; pNext != head; pNext = pNext->next) {
			if(pred(pNode->data, pNext->data)) {
				pNext = reinterpret_cast<Node*>(reinterpret_cast<unsigned int>(&*(erase(Iterator(pNext)))))->prev;
			}
		}
	}
}

/**************************************************************************************************
* Merge sorted lists together by moving elements from one list to the other one at a time
**************************************************************************************************/
template <typename Type>
void List<Type>::merge(List<Type>& list) {
	// Iterate through both lists
	Iterator itr0 = begin();
	Iterator itr1 = list.begin();
	Iterator end0 = end();
	Iterator end1 = list.end();
	Iterator position = itr0;

	while(itr0 != end0 && itr1 != end1) {
		// First list has ended, add only from second list
		if(itr0 == end0) {
			position = insert(position, *itr1);
			itr1 = list.erase(itr1);
		} 
		// Second list has ended, add only from first list
		else if(itr1 == end1) {
			++itr0;
			++position;
		} 
		// We must compare both iterators to insert at a given position
		else {
			if(*itr0 <= *itr1) {
				++itr0;
				++position;
			} else {
				position = insert(position, *itr1);
				itr0 = position;
				itr1 = list.erase(itr1);
			}
		}
	}
}

/**************************************************************************************************
* Merge sorted lists together based on a predicate by moving elements from one list to the other
* one at a time
**************************************************************************************************/
template <typename Type>
template <class Compare>
void List<Type>::merge(List<Type>& list, Compare comp) {
	// Iterate through both lists
	Iterator itr0 = begin();
	Iterator itr1 = list.begin();
	Iterator end0 = end();
	Iterator end1 = list.end();
	Iterator position = itr0;

	while(itr0 != end0 && itr1 != end1) {
		// First list has ended, add only from second list
		if(itr0 == end0) {
			position = insert(position, *itr1);
			itr1 = list.erase(itr1);
		} 
		// Second list has ended, add only from first list
		else if(itr1 == end1) {
			++itr0;
			++position;
		} 
		// We must compare both iterators to insert at a given position
		else {
			if(comp(*itr0, *itr1)) {
				++itr0;
				++position;
			} else {
				position = insert(position, *itr1);
				itr0 = position;
				itr1 = list.erase(itr1);
			}
		}
	}
}

/**************************************************************************************************
* Sort all elements in the list
**************************************************************************************************/
template <typename Type>
void List<Type>::sort(void) {
	// Maximum number of bins
	const int MAXBINS = 32;
	
	// Temporary list as well as a bin lists
	List<Type> tempList, binList[MAXBINS + 1];
	int maxBin = 0;

	while(!empty()) {
		// Sort another element using bins
		tempList._splice_same(tempList.begin(), *this, begin(), ++begin(), 1);

		int bin;
		for(bin = 0; bin < maxBin && !binList[bin].empty(); ++bin) {
			// Merge into larger bins
			binList[bin]._merge(tempList);
			_swap(binList[bin], tempList);
		}

		// If we are at the last bin, merge temp list
		if(bin == MAXBINS) {
			binList[bin - 1]._merge(tempList);
		} else {
			// Spill into a new bin while we are able to
			_swap(binList[bin], tempList);
			if(bin == maxBin)
				++maxBin;
		}
	}

	for(int bin = 1; bin < maxBin; ++bin) {
		// Merge the bins up
		binList[bin]._merge(binList[bin - 1]);
	}

	// The result is in the last bin, so splice that into the current list
	_splice_same(begin(), binList[maxBin - 1]);
}

/**************************************************************************************************
* Sort all elements according to a special comparative function
**************************************************************************************************/
template <typename Type>
template <class Compare>
void List<Type>::sort(Compare comp) {
	// Maximum number of bins
	const int MAXBINS = 32;
	
	// Temporary list as well as a bin lists
	List<Type> tempList, binList[MAXBINS + 1];
	int maxBin = 0;

	while(!empty()) {
		// Sort another element using bins
		tempList._splice_same(tempList.begin(), *this, begin(), ++begin(), 1);

		int bin;
		for(bin = 0; bin < maxBin && !binList[bin].empty(); ++bin) {
			// Merge into larger bins
			binList[bin]._merge(tempList, comp);
			_swap(binList[bin], tempList);
		}

		// If we are at the last bin, merge temp list
		if(bin == MAXBINS) {
			binList[bin - 1]._merge(tempList, comp);
		} else {
			// Spill into a new bin while we are able to
			_swap(binList[bin], tempList);
			if(bin == maxBin)
				++maxBin;
		}
	}

	for(int bin = 1; bin < maxBin; ++bin) {
		// Merge the bins up
		binList[bin]._merge(binList[bin - 1], comp);
	}

	// The result is in the last bin, so splice that into the current list
	_splice_same(begin(), binList[maxBin - 1]);
}

/**************************************************************************************************
* Reverse the order of the list
**************************************************************************************************/
template <typename Type>
void List<Type>::reverse(void) {
	// Get the head node
	const Node* pHead = head;
	Node* pNode = pHead;

	// Iterate through all the nodes
	for(;;) {
		// Flip node pointers
		const Node* pNext = pNode->next;
		pNode->next = pNode->prev;
		pNode->prev = pNext;

		// Break if we went all the way around
		if(pNext == pHead)
			break;

		// Increment the nodes
		pNode = pNext;
	}
}

/**************************************************************************************************
* Merge in-place when used with sorting (in other words, no new nodes are created, they are merely
* changed around)
**************************************************************************************************/
template <typename Type>
void List<Type>::_merge(List<Type>& list) {
	// Iterate through both lists
	Iterator first1 = begin();
	Iterator last1 = end();
	Iterator first2 = list.begin();
	Iterator last2 = list.end();

	while(first1 != last1 && first2 != last2) {
		// First list has ended, add only from second list
		if(*first2 < *first1) {
			Iterator mid2 = first2;
			_splice_same(first1, list, first2, ++mid2, 1);
			first2 = mid2;
		} 
		// Second list has ended, add only from first list
		else {
			++first1;
		} 
	}

	// Splice the remainder of the list into this
	if(first2 != last2) {
		_splice_same(last1, list, first2, last2, list.size());
	}
}

/**************************************************************************************************
* Merge in-place according to a predicate when used with sorting (in other words, no new nodes are 
* created, they are merely changed around)
**************************************************************************************************/
template <typename Type>
template <class Compare>
void List<Type>::_merge(List<Type>& list, Compare comp) {
		// Iterate through both lists
	Iterator first1 = begin();
	Iterator last1 = end();
	Iterator first2 = list.begin();
	Iterator last2 = list.end();

	while(first1 != last1 && first2 != last2) {
		// First list has ended, add only from second list
		if(comp(*first2, *first1)) {
			Iterator mid2 = first2;
			_splice_same(first1, list, first2, ++mid2, 1);
			first2 = mid2;
		} 
		// Second list has ended, add only from first list
		else {
			++first1;
		} 
	}

	// Splice the remainder of the list into this
	if(first2 != last2) {
		_splice_same(last1, list, first2, last2, list.size());
	}
}

/**************************************************************************************************
* Swap the contents of two lists
**************************************************************************************************/
template <typename Type>
void _swap(List<Type>& lhs, List<Type>& rhs) {
	// Swap heads
	List<Type>::Node* pNode = rhs.head;
	rhs.head = lhs.head;
	lhs.head = pNode;

	// Swap sizes
	int s = lhs._size;
	lhs._size = rhs.size();
	rhs._incSize(s - lhs._size);
}