//*************************************************************************************************
// Title: SumForwardList.h
// Author: Gael Huber
// Description: Describes a singly-linked list.
//
// TODO: Convert block comment format in ForwardList class to follow current convention
// TODO: Convert ForwardList to utilize SumEngine's memory allocator
// TODO: Convert to use SumPlatform
//*************************************************************************************************
#ifndef __SUMFORWARDLIST_H__
#define __SUMFORWARDLIST_H__

template <typename Type>
class ForwardList {
private:
	class Node;		// Represents each node of the list
	
public:
	// http://www.cplusplus.com/reference/std/iterator/
	// http://www.cplusplus.com/reference/std/iterator/iterator/
	// http://www.yolinux.com/TUTORIALS/LinuxTutorialC++STL.html
	class Iterator;	// Foward iterator for the list

public:
	ForwardList(void);		// Constructor
	ForwardList(const ForwardList<Type>& rhs);	// Copy-constructor
	~ForwardList(void);		// Destructor

	const ForwardList<Type>& operator=(const ForwardList<Type>& rhs);	// Assignment operator
	const bool operator==(const ForwardList<Type>& rhs) const;	// Equivalence operator
	const bool operator!=(const ForwardList<Type>& rhs) const;	// Non-equivalence operator

	void push_front(const Type& val);	// Push a value onto the front of the list
	void push_back(const Type& val);	// Push a value onto the back of the list
	const Type pop_front(void);		// Pop the value from the front of the list
	const Type pop_back(void);		// Pop the value from the back of the list
	const Type& front(void) const;	// Returns the first value in the list
	const Iterator begin(void) const;	// Returns the front-value iterator of the list
	const Iterator end(void) const;	// Returns the end-value iterator of the list
	void reverse(void);		// Reverse all the links within the linked list
	const unsigned int getCount(void) const;	// Find the length of the linked list
	const bool hasHead(void) const;		// Returns whether the list has a valid head

private:
	Node* head;		// Head node of the list
	Node* tail;		// Tail node of the list
	unsigned int count;		// Number of elements in the list
};


/**************************************************************************************************
* Forward list node, contains the value being held by the node and a reference to the next node.
**************************************************************************************************/
template <typename Type>
class ForwardList<Type>::Node {
public:
	Node(void);		// Default constructor
	explicit Node(const Type& d);	// Constructor specifying data
	~Node(void);	// Destructor

	const Type& getData(void) const;	// Returns the data
	void setData(const Type& d);		// Sets the data
	Node* const getNext(void) const;	// Returns the next node
	void setNext(Node* n);	// Sets the next node

private:
	Type data;	// Data of the node
	Node* next;	// The node that comes after this node in the list
};

/**************************************************************************************************
* List iterator, permits forward iteration through the list.
**************************************************************************************************/
template <typename Type>
class ForwardList<Type>::Iterator {
public:
	Iterator(void);		// Default constructor
	Iterator(const Iterator& rhs);	// Copy-constructor
	Iterator(Node* arg);	// Constructor that binds list
	~Iterator(void);		// Destructor

	const Iterator& operator=(const Iterator& rhs);	// Assignment operator
	const bool operator==(const Iterator& rhs) const;		// Equivalence
	const bool operator!=(const Iterator& rhs) const;		// Non-equivalence
	const Iterator& operator++(void);	// Pre-increment
	const Iterator operator++(int rhs);	// Post-increment
	const Type& operator*(void) const;	// Return the value
	const Type* operator->(void) const;	// Return pointer to this object

private:
	Node* n;
};

// File inline includes
#include "SumForwardList.inl"
#include "SumForwardListNode.inl"
#include "SumForwardListIterator.inl"


#endif