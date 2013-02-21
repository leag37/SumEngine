/**************************************************************************************************
* Title: SumDictionary.h
* Author: Gael Huber
* Description: Defines a templated dictionary. The dictionary is implemented in the form of a
*	red-black tree. Red-black trees have the following properties:
*	Property 1: A node is either red or black
*	Property 2: The root is black
*	Property 3: All leaves are the same color as the root
*	Property 4: Both children of every red node are black
*	Property 5: Every simple path from a given node to any of its descendant leaves contains the
*		same number of black nodes.
//
// TODO: Add const accessor functions
**************************************************************************************************/
#ifndef __SUMDICTIONARY_H__
#define __SUMDICTIONARY_H__

#include "SumInclude.h"

template <typename Key, typename Value>
class Dictionary {
private:
	class Pair;		// Represents a key-value pair in the dictionary
	class Node;		// Represents a node in the dictionary

public:
	class Iterator;		// Represents an iterator for the dictionary

public:
	Dictionary(void);	// Constructor
	Dictionary(const Dictionary<Key, Value>& rhs);	// Copy-constructor
	~Dictionary(void);	// Destructor
	const Dictionary<Key, Value>& operator=(const Dictionary<Key, Value>& rhs);		// Assignment operator

	const bool operator==(const Dictionary<Key, Value>& rhs) const;		// Equivalence
	const bool operator!=(const Dictionary<Key, Value>& rhs) const;		// Non-equivalence

	const Iterator begin(void) const;	// Iterator to begin
	const Iterator end(void) const;		// Iterator to end

	const bool empty(void) const;			// Return whether the dictionary is empty
	const unsigned int getSize(void) const;	// Return size

	Value& operator[](const Key& rhs);	// Array-based accessor (inserts if it cannot find)

	const Iterator insert(const Key& key, const Value& value);	// Insert element
	void erase(const Key& key);		// Erase element based on key
	void erase(const Iterator& itr);	// Erase element based on iterator
	void swap(Dictionary<Key, Value>& rhs);	// Swap contents with another dictionary
	void clear(void);	// Clear the content of the dictionary
	const Iterator find(const Key& key) const;	// Return an iterator to the value found, if no value is found return an iterator to end

public:
	static const bool _isLeaf(Node* n);	// Return whether the node is a leaf
	static Node* _leftMost(Node* n);	// Return the left-most node of this subtree
	static Node* _rightMost(Node* n);	// Return the right-most node of this subtree
	static const bool _isNil(Node* n);	// Returns whether or not a node is valid (0 or empty are not valid)

private:
	void rotate_left(Node* n);		// Perform a left rotation
	void rotate_right(Node* n);		// Perform a right rotation
	void replace_node(Node* n0, Node* n1);	// Replaces n0 with n1 in the tree

	Node* dictionary;	// Pointer to head of dictionary
	unsigned int size;	// Size of the dictionary
};

/**************************************************************************************************
* Defines dictionary key-value pair
**************************************************************************************************/
template <typename Key, typename Value>
class Dictionary<Key, Value>::Pair {
public:
	Pair(void);		// Constructor
	Pair(const Key& k, const Value& v);	// Constructor populating key and value
	Pair(const Pair& rhs);	// Copy-constructor
	~Pair(void);	// Destructor
	
	const Pair& operator=(const Pair& rhs);		// Assignemnt operator
	const bool operator==(const Pair& rhs) const;	// Equivalence
	const bool operator!=(const Pair& rhs) const;	// Non-equivalence

	const Key& getKey(void) const;		// Return the key associated with this pair
	const Value& getValue(void) const;	// Return the value associated with this pair
	Value& getValue(void);				// Return non-const version of value associated with this pair
	void setValue(const Value& v);	// Set the value associated with this pair
	void swap(Pair& rhs);	// Swap the pair with another pair

private:
	Key key;		// The key of the pair
	Value value;	// The associated value
};

/**************************************************************************************************
* Defines a node in the dictionary
**************************************************************************************************/
template <typename Key, typename Value>
class Dictionary<Key, Value>::Node {
public:
	// Color of the node
	enum Color {BLACK = 0, RED};

public:
	Node(void);		// Constructor
	Node(const Pair& d);	// Constructor specifying pair and the parent
	Node(const Node& rhs);	// Copy-construtor
	~Node(void);	// Destructor

	Node* getParent(void) const;	// Return the parent node
	void setParent(Node* p);		// Sets the parent node
	Node* getLeft(void) const;	// Return the left child
	void setLeft(Node* l);		// Sets the left child
	Node* getRight(void) const;	// Return the right child
	void setRight(Node* r);		// Sets the right child
	
	Node* getGrandparent(void);	// Returns the grandparent of this node if it exists
	Node* getUncle(void);		// Returns the uncle of this node if it exists
	Node* getSibling(void);		// Returns the sibling of this node

	const Pair& getData(void) const;	// Return the data held within the node
	Pair& getData(void);				// Return non-const version of data held within the node
	void setData(const Pair& d);		// Set the data of the node
	const Color getColor(void) const;	// Return the color of the node
	void setColor(const Color value);	// Set the color of the node

	const bool isEmpty(void) const;	// Returns whether the node is empty

private:
	Pair data;		// Data held within the node
	Color color;	// Color of the node
	bool empty;		// Is the node empty?
	Node* parent;	// Parent node, or root of tree if head
	Node* left;		// Left child
	Node* right;	// Right child
};
#include <string>
/**************************************************************************************************
* Defines an iterator for the dictionary
**************************************************************************************************/
template <typename Key, typename Value>
class Dictionary<Key, Value>::Iterator {
public:
	Iterator(void);		// Default constructor
	Iterator(Node* arg);	// Constructor that binds the dictionary
	Iterator(const Iterator& rhs);	// Copy-constructor
	~Iterator(void);	// Destructor

	const Iterator& operator=(const Iterator& rhs);		// Assignment operator
	const bool operator==(const Iterator& rhs) const;	// Equivalence
	const bool operator!=(const Iterator& rhs) const;	// Non-equivalence
	const Iterator& operator++(void);	// Pre-increment
	const Iterator operator++(int rhs);	// Post-increment
	const Iterator& operator--(void);	// Pre-decrement
	const Iterator operator--(int rhs);	// Post-decrement
	const Pair& operator*(void) const;	// Return the associated value
	const Pair* operator->(void) const;	// Return a pointer to the associated object
	Node* _node() const;			// Directly return the node

private:
	Node* n;
};

#include "SumDictionary.inl"
#include "SumDictionaryNode.inl"
#include "SumDictionaryPair.inl"
#include "SumDictionaryIterator.inl"

#endif