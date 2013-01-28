/**************************************************************************************************
* Title: SumForwardList.inl
* Author: Gael Huber
* Description: Describes a singly-linked list.
**************************************************************************************************/

/**************************************************************************************************
* Constructor
**************************************************************************************************/
template <typename Type>
ForwardList<Type>::ForwardList(void) 
	: head(0), tail(0), count(0)
{ }

/**************************************************************************************************
* Copy-constructor
**************************************************************************************************/
template <typename Type>
ForwardList<Type>::ForwardList(const ForwardList<Type>& rhs)
	: head(0), tail(0)
{
	// Set the count
	count = rhs.getCount();

	// We only need to copy data if count is greater than 0, otherwise head and tail are both 0
	if(count > 0) {
		// Create the head node for this list
		head = new Node(*rhs.begin());
		Node* n = head;

		// Iterate through the list and copy each new node
		for(ForwardList<Type>::Iterator itr = rhs.begin(); itr != rhs.end(); ++itr) {
			n->setNext(new Node(*itr));
		}
	
		// Set the tail node equal to the current node
		tail = n;
	}
}

/**************************************************************************************************
* Destructor
**************************************************************************************************/
template <typename Type>
ForwardList<Type>::~ForwardList(void) {
	Node* n = head;

	while(head != 0) {
		// Move the head forward
		head = head->getNext();

		// Delete the previous head
		delete n;

		// Set n to the head
		n = head;
	}

	// Ensure head and tail are 0
	head = 0;
	tail = 0;
}

/**************************************************************************************************
* Assignment operator
**************************************************************************************************/
template <typename Type>
const ForwardList<Type>& ForwardList<Type>::operator=(const ForwardList<Type>& rhs) {
	// Self-assignment guard
	if(this == &rhs)
		return *this;

	// Delete the previously existing data
	~ForwardList();

	// Set the counts to be the same
	count = rhs.getCount();

	// Set the head
	head = rhs[0];

	return *this;
}

/**************************************************************************************************
* Equivalence operator
**************************************************************************************************/
template <typename Type>
const bool ForwardList<Type>::operator==(const ForwardList<Type>& rhs) const {
	// Check counts
	if(count != rhs.getCount())
		return false;

	// Iterate over each list, if all values are equal the lists are equal
	Iterator itr0 = begin();
	Iterator itr1 = rhs.begin();
	while(itr0 != end()) {
		// If the data is not equal, the lists are not matching
		if(*itr0 != *itr1) {
			return false;
		}

		// Icremement both iterators
		++itr0;
		++itr1;
	}

	// Successfully iterated over all values, so the lists must be equal
	return true;
}

/**************************************************************************************************
* Non-equivalence operator
**************************************************************************************************/
template <typename Type>
const bool ForwardList<Type>::operator!=(const ForwardList<Type>& rhs) const {
	// Check counts
	if(count != rhs.getCount())
		return true;

	// Iterate over each list, if all values are equal the lists are equal
	Iterator itr0 = begin();
	Iterator itr1 = rhs.begin();
	while(itr0 != end()) {
		// If the data is not equal, the lists are not matching therefore return true
		if(*itr0 != *itr1) {
			return true;
		}

		// Icremement both iterators
		++itr0;
		++itr1;
	}

	// Successfully iterated over all values, so the lists must be equal, therefore return false
	return false;
}

/**************************************************************************************************
* Push a value onto the front of the list
**************************************************************************************************/
template <typename Type>
void ForwardList<Type>::push_front(const Type& val) {
	// Create a new head
	Node* tHead = new Node(val);

	// Make the old head the new head's next node
	tHead->setNext(tHead);

	// Set the head to the new head
	head = tHead;

	// Increment count
	count++;
}

/**************************************************************************************************
* Push a value onto the back of the list
**************************************************************************************************/
template <typename Type>
void ForwardList<Type>::push_back(const Type& val) {
	// If head does not exist
	if(!head) {
		// Create the head node with a value
		head = new Node(val);

		// Set tail equal to the head
		tail = head;
	} else {
		// Otherwise, create a new tail node and set tail equal to it
		tail->setNext(new Node(val));
		tail = tail->getNext();
	}

	// Increment the count
	count++;
}

/**************************************************************************************************
* Pop the value from the front of the list
**************************************************************************************************/
template <typename Type>
const Type ForwardList<Type>::pop_front(void) {
	// Get the data to return
	Type t = head->getData();

	// Create a temporary head (the second node)
	Node* tHead = head->getNext();

	// Delete the head
	delete head;

	// Set the new head
	head = tHead;

	// Decrement count
	--count;

	// Return the data
	return t;
}

/**************************************************************************************************
* Pop the value from the back of the list
**************************************************************************************************/
template <typename Type>
const Type ForwardList<Type>::pop_back(void) {
	// Iterate through each node until the next node is tail
	Node* n = head;
	while(n->getNext() != tail) {
		n = n->getNext();
	}

	// We have found the tail, so pull the data out
	Type t = tail->getData();

	// Delete the tail
	delete tail;

	// Set the new tail
	tail = n;

	// Decremement count
	--count;

	// Return the data
	return t;
}

/**************************************************************************************************
* Returns the first value in the list
**************************************************************************************************/
template <typename Type>
const Type& ForwardList<Type>::front(void) const {
	return *begin();
}

/**************************************************************************************************
* Returns the front value of the list
**************************************************************************************************/
template <typename Type>
const typename ForwardList<Type>::Iterator ForwardList<Type>::begin(void) const {
	return Iterator(head);
}

/**************************************************************************************************
* Returns the end value of the list
**************************************************************************************************/
template <typename Type>
const typename ForwardList<Type>::Iterator ForwardList<Type>::end(void) const {
	return Iterator(0);
}

/**************************************************************************************************
* Reverse all the links within the linked list
**************************************************************************************************/
template <typename Type>
void ForwardList<Type>::reverse(void) {
}

/**************************************************************************************************
* Find the length of the linked list
**************************************************************************************************/
template <typename Type>
const unsigned int ForwardList<Type>::getCount(void) const {
	return count;
}

/**************************************************************************************************
* Return whether the list has a valid head
**************************************************************************************************/
template <typename Type>
SUMINLINE const bool ForwardList<Type>::hasHead(void) const {
	return head != 0;
}