/**************************************************************************************************
* Title: SumHashMap.h
* Author: Gael Huber
* Description: Hash map used to contain information within a table.
**************************************************************************************************/
#ifndef __SUMHASHMAP_H__
#define __SUMHASHMAP_H__

#include "SumInclude.h"
#include "SumRandom.h"
#include "SumList.h"
#include "SumArray.h"

// The load factor used to determine the point at which we want to enlarge the table
#define HASH_LOAD_FACTOR 0.75f

// Number of elements to be moved to the new table with each insertion
#define HASH_R	1

// Basically, have a pointer to a portion of space of size Value * max elements. Simulateneously we
// will mantain an ordered array of keys length max elements to notify whether a value exists. 

// When load factor is reached, we enlarge the vector of pairs by 8 (default size is 16). We then assign
// the same value (end) to all elements in the new vector. Iterate through all elements in the list 
// from end->begin and re-hash/add them to the vector.

/**************************************************************************************************
* HashMap
* -----------------
* HashMap is responsible for acting as the cohesive hash table such that there appears to only be
* one map visible on the implementation side. This is achieved by having an array of two buckets.
* The first bucket is the assignment bucket where all new hash assignments exist. The second bucket
* only exists as an "old" bucket when we are in the process of incrementally increasing the size
* of the hash table. HashMap will, however, contain the set of hash functions to be used and will
* determine which hash function is to be used at allocation. Additionally, HashMap will contain the
* current list of keys. 
**************************************************************************************************/
template <typename Key, typename Value>
class HashMap {
public:
	// Pairs the data together for easy storage
	struct Pair;

public:
	// Iterator for the hashmap
	class Iterator;

public:
	// Default constructor
	HashMap(void);

	// Copy constructor
	HashMap(const HashMap<Key, Value>& rhs);

	// Destructor
	~HashMap(void);

	// Assignment operator
	HashMap<Key, Value>& operator=(const HashMap<Key, Value>& rhs);

	// Test whether the hashmap is empty
	bool empty(void) const;

	// Returns the size of the hashmap
	int size(void) const;

	// Returns the maximum size of the hashmap in terms of content
	int max_size(void) const;

	// Returns the capacity of the container
	int capacity(void) const;

	// Returns an interator pointing to the beginning of the hashmap
	Iterator begin(void) const;

	// Returns an interator pointing to the end of the hashmap
	Iterator end(void) const;

	// Attempt to get a value from the hashmap. If the value does not yet exist, add it.
	Value& operator[](const Key& key);

	// Attempt to get a value from the hashmap at a given key
	Value& at(const Key& key);

	// Find the element with a specific key
	Iterator find(const Key& key); 

	// Returns the number of entries with given key. Since duplicate entries are not permitted, this
	// basically tells you whether a given key exists in the hashmap.
	int count(const Key& key) const;

	// Erase the value at the given position if it exists
	Iterator erase(const Iterator position);

	// Erase a given key if it exists (returns the number of elements erased, 1 being successful 0
	// otherwise)
	int erase(const Key& key);

	// Erases the range of elements between first and last including first but not including last.
	// Returns an iterator pointing to the position immediately after the erased section.
	Iterator erase(const Iterator first, const Iterator last);

	// Clear the hashmap of all values, leaving it with a size of 0
	void clear(void);

private:
	// Choose a hashing function
	void chooseFunction(void);

	// Grow the hash map
	void grow(void);

	// Attempt to find a given key in the array and return an iterator
	typename List<Pair>::Iterator _find(const Key& key);

	// Insert a pair with a blank value into the hash map
	typename List<Pair>::Iterator _insert(const Key& key);

	// Insert a pair into the hashmap given a key
	typename List<Pair>::Iterator _insert(const typename List<typename HashMap<Key, Value>::Pair>::Iterator& itr);

private:
	// The list of pairs (primarily used with iteration and vector manipulation)
	List<Pair> pairList;

	// Array of pair iterators used to determine whether a given pair already exists within the map
	Array<typename List<Pair>::Iterator> bucket;

	// Number of elements
	int _size;

	// Maximum number of elements
	int _capacity;

	// Hash function
	unsigned int (*func)(const char*);
};

/**************************************************************************************************
* Pair
* -----------------
* A pair is nothing more than a key-value pair. These are used exclusively when dealing with the
* iterator, pair values are not designed to be kept	in memory at all times.
**************************************************************************************************/
template <typename Key, typename Value>
struct HashMap<Key, Value>::Pair {
	// Default constructor
	Pair(void);

	// Constructor specifying key and pair
	Pair(const Key& first, const Value& second);

	// Copy constructor
	Pair(const Pair& rhs);

	// Destructor
	~Pair(void);

	// Assignment
	Pair& operator=(const Pair& rhs);

	// Equivalence
	bool operator==(const Pair& rhs) const;

	// Non-equivalence
	bool operator!=(const Pair& rhs) const;

	// Equivalence of valid data
	bool operator==(int rhs) const;

	// Non-equivalence of valid data
	bool operator!=(int rhs) const;

	// First value of the pair (key)
	Key first;

	// Second value of the pair (value)
	Value second;
};

/**************************************************************************************************
* Iterator
* -----------------
* The iterator for the hash map will permit linear progressing through the hash map in order of key
* values. The iterator should act similar to an array iterator, however data contained should be
* a pair rather than discreet references to the data.
**************************************************************************************************/
template <typename Type, typename Value>
class HashMap<Type, Value>::Iterator {
public:
	// Default constructor
	Iterator(void);

	// Constructor given an iterator in the list
	Iterator(const typename List<Pair>::Iterator& data);

	// Copy constructor
	Iterator(const Iterator& rhs);

	// Destructor
	~Iterator(void);

	// Return the data referenced
	Pair& operator*(void) const;

	// Return a pointer to the class object
	Pair* operator->(void) const;

	// Pre-increment
	Iterator& operator++(void);
	
	// Post-increment
	Iterator operator++(int rhs);

	// Pre-decrement
	Iterator& operator--(void);

	// Post-decrement
	Iterator operator--(int rhs);

	// Increment by integer
	Iterator& operator+=(int rhs);

	// Return this + integer
	Iterator operator+(int rhs) const;

	// Decrement by integer
	Iterator& operator-=(int rhs);

	// Return this - integer
	Iterator operator-(int rhs) const;

	// Return the data held
	Pair& operator[](int rhs) const;

	// Equivanlence operator
	bool operator==(const Iterator& rhs) const;

	// Non-equivalence
	bool operator!=(const Iterator& rhs) const;

private:
	// Pointer to the data element in the ordered array
	typename List<Pair>::Iterator data;
};

/**************************************************************************************************
* Family of hash functions to use
**************************************************************************************************/
extern "C" 
{
	unsigned int RSHash(const char* str);
	unsigned int JSHash(const char* str);
	unsigned int PJWHash(const char* str);
	unsigned int ELFHash(const char* str);
	unsigned int BKDRHash(const char* str);
	unsigned int SDBMHash(const char* str);
	unsigned int DJBHash(const char* str);
	unsigned int DEKHash(const char* str);
	unsigned int BPHash(const char* str);
	unsigned int FNVHash(const char* str);
	unsigned int APHash(const char* str);
};

/**************************************************************************************************
* Inline files
**************************************************************************************************/
#include "SumHashMap.inl"
#include "SumHashMapPair.inl"
#include "SumHashMapIterator.inl"

#endif