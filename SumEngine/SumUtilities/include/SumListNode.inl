/**************************************************************************************************
* Title: SumListNode.inl
* Author: Gael Huber
* Description: A list node, containing pointers to both preceding and succeeding nodes
**************************************************************************************************/

/**************************************************************************************************
* Constructor
**************************************************************************************************/
template <typename Type>
List<Type>::Node::Node(void) {
	next = this;
	prev = this;
}

/**************************************************************************************************
* Constructor specifying data
**************************************************************************************************/
template <typename Type>
List<Type>::Node::Node(Type data)
	: data(data)
{ }

/**************************************************************************************************
* Constructor specifying data, next, and previous
**************************************************************************************************/
template <typename Type>
List<Type>::Node::Node(Type data, Node* next, Node* prev)
	: data(data), next(next), prev(prev)
{ }

/**************************************************************************************************
* Copy constructor
**************************************************************************************************/
template <typename Type>
List<Type>::Node::Node(const Node& rhs)
	: data(rhs.data), next(rhs.next), prev(rhs.prev)
{ }

/**************************************************************************************************
* Destructor
**************************************************************************************************/
template <typename Type>
List<Type>::Node::~Node(void) {
	next = 0;
	prev = 0;
}

/**************************************************************************************************
* Swap the contents of the nodes
**************************************************************************************************/
template <typename Type>
void List<Type>::Node::swap(typename List<Type>::Node* rhs) {
	Type ty = rhs->data;
	rhs->data = data;
	data = ty;

	next->prev = rhs;
	prev->next = rhs;
	rhs->next->prev = this;
	rhs->prev->next = this;

	Node* pNode = next;
	next = rhs->next;
	rhs->next = pNode;

	pNode = prev;
	prev = rhs->prev;
	rhs->prev = pNode;
}