/**************************************************************************************************
* Title: SumList.h
* Author: Gael Huber
* Description: Defines a standard bi-directional list.
**************************************************************************************************/
#ifndef __SUMLIST_H__
#define __SUMLIST_H__

#include "SumInclude.h"

/**************************************************************************************************
* List
* ----------------------
* Main container for the list and all major functionality
**************************************************************************************************/
template <typename Type>
class List {
private:
	// A node in the list
	struct Node;

public:
	// Bidirectional iterator for the list
	class Iterator;

public:
	// Default constructor
	List(void);

	// Copy constructor
	List(const List<Type>& rhs);

	// Destructor
	~List(void);

	// Assignment operator
	List<Type>& operator=(const List<Type>& rhs);

	// Equivalence operator
	bool operator==(const List<Type>& rhs) const;

	// Non-equivalence operator
	bool operator!=(const List<Type>& rhs) const;

	// Return an iterator pointing to the beginning of the list
	Iterator begin(void) const;

	// Return an iterator pointing to the end of the list
	Iterator end(void) const;

	// Test whether the list is empty
	bool empty(void) const;

	// Return the size of the list
	int size(void) const;

	// Increase the size of the list by a given amount
	void _incSize(int inc);

	// Access the first element
	Type& front(void);

	// Access the last element
	Type& back(void);

	// Assign new content to the container. The data is everything that exists between first and last
	// inclusive. The current contents of the list are erased.
	void assign(const Iterator& first, const Iterator& last);

	// Assign the content of the container to be n copies of a specified value. The current contents
	// of the list are erased.
	void assign(int n, const Type& val);

	// Push a value at the front of the list
	void push_front(const Type& val);

	// Pop a value from the front of the list
	void pop_front(void);

	// Push a value at the back of the list
	void push_back(const Type& val);

	// Pop a value from the back of the list
	void pop_back(void);

	// Insert an element into the list. Return an iterator pointing to newly inserted element.
	Iterator insert(Iterator position, const Type& val);

	// Insert n copies of val into the list
	void insert(Iterator position, int n, const Type& val);

	// Erase a value from the list. Return the new value at this position in the list (if erasing last
	// element, the iterator would point to end)
	Iterator erase(Iterator position);

	// Erase all values within the specified range.
	Iterator erase(Iterator first, Iterator last);

	// Clear all contents of the list
	void clear(void);

	// Removes all elements from list x and moves them into this list at a specified position
	void splice(Iterator position, List<Type>& x);

	// Removes only element at i from list x and moves it into this list at a specified position
	void splice(Iterator position, List<Type>& x, Iterator i);

	// Removes all elements from first to last from list x and moves them into this list at a 
	// specified position
	void splice(Iterator position, List<Type>& x, Iterator first, Iterator last);

	// Removes all elements from list x and moves them into this list without recreating the nodes.
	// Instead, the nodes are directly manipulated.
	void _splice_same(Iterator position, List<Type>& x);

	// // Removes only element at i from list x and moves it into this list at a specified position
	// into this list without recreating the nodes. Instead, the nodes are directly manipulated.
	void _splice_same(Iterator position, List<Type>& x, Iterator i);

	// Removes all elements from first to last from list x and moves them into this list at a given 
	// position without creating copies of the data.
	void _splice_same(Iterator position, List<Type>& x, Iterator first, Iterator last, int count);

	// Removes all occurrences of an element with the given value
	void remove(const Type& val);

	// Removes any occurrences where the predicate is determined to be true (www.cplusplus.com/reference/stl/list/remove_if/
	template <class Predicate0>
	void remove_if(Predicate0 pred);

	// Removes all adjacent duplicate values (considering the first occurrence as the "unique" value)
	void unique(void);

	// Removes all adjacent duplicate values (considering the first occurrence as the "unique" value)
	// according to a predicate
	template <class Predicate1>
	void unique(Predicate1 pred);

	// Removes all duplicate values
	void unique_all(void);

	// Removes all duplicate values according to a predicate
	template <class Predicate2>
	void unique_all(Predicate2 pred);

	// Merge sorted lists together by moving elements from one list to the other one at a time
	void merge(List<Type>& list);

	// Merge sorted lists together based on a predicate by moving elements from one list to the other
	// one at a time
	template <class Compare>
	void merge(List<Type>& list, Compare comp);

	// Sort all elements in the list
	void sort(void);

	// Sort all elements according to a special comparative function
	template <class Compare>
	void sort(Compare comp);

	// Reverse the order of the list
	void reverse(void);

	// Swap the contents of two lists
	template <typename Type>
	friend void _swap(List<Type>& lhs, List<Type>& rhs);

private:
	// Merge in-place when used with sorting (in other words, no new nodes are created, they are
	// merely changed around)
	void _merge(List<Type>& list);

	// Merge in-place according to a predicate when used with sorting (in other words, no new nodes
	// are created, they are merely changed around)
	template <class Compare>
	void _merge(List<Type>& list, Compare comp);

private:
	// Head node of the list (head is actually a dummy value that acts as the "end", in otherwords, an
	// empty node)
	Node* head;

	// Size of the list
	int _size;
};

/**************************************************************************************************
* Node
* ----------------------
* A list node, containing pointers to both preceding and succeeding nodes
**************************************************************************************************/
template <typename Type>
struct List<Type>::Node {
	// Constructor
	Node(void);

	// Constructor specifying data
	Node(Type data);

	// Constructor specifying data, next, and previous
	Node(Type data, Node* next, Node* prev);

	// Copy constructor
	Node(const Node& rhs);

	// Destructor
	~Node(void);

	// Swap the contents of the nodes
	void swap(Node* rhs);

	// The data held within the node
	Type data;

	// Next node in the list
	Node* next;

	// Previous node in the list
	Node* prev;
};

/**************************************************************************************************
* Iterator
* ----------------------
* Bidirectional list iterator
**************************************************************************************************/
template <typename Type>
class List<Type>::Iterator {
public:
	// Default constructor
	Iterator(void);

	// Constructor given list information
	Iterator(Node* n);

	// Copy constructor
	Iterator(const Iterator& rhs);

	// Destructor
	~Iterator(void);

	// Assignment operator
	Iterator& operator=(const Iterator& rhs);

	// Equality operator
	bool operator==(const Iterator& rhs) const;

	// Inequality operator
	bool operator!=(const Iterator& rhs) const;

	// Dereference operator to return value
	Type& operator*(void) const;

	// Dereference operator to return pointer to object
	Type* operator->(void) const;

	// Pre-increment
	Iterator& operator++(void);

	// Post-increment
	Iterator operator++(int rhs);

	// Pre-decrement
	Iterator& operator--(void);

	// Post-decrement
	Iterator operator--(int rhs);

	// Return the node
	Node* nodePtr(void) const;

private:
	// Node in list
	Node* n;
};

/**************************************************************************************************
* Includes
**************************************************************************************************/

#include "SumList.inl"
#include "SumListNode.inl"
#include "SumListIterator.inl"

#endif