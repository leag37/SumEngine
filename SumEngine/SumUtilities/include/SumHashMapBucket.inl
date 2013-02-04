/**************************************************************************************************
* Title: SumHashMapBucket.inl
* Author: Gael Huber
* Description: Bucket is the core of the hash map. It contains all variables needed to keep track 
*	of its capacity, load factor, as well as the actual data.
**************************************************************************************************/

/**************************************************************************************************
* Default constructor (default bucket capacity is 4)
**************************************************************************************************/
template <typename Key, typename Value>
HashMap<Key, Value>::Bucket::Bucket(void) 
	: size(0), capacity(4)
{
	pairs = new Pair[capacity];
}

//// Constructor given the bucket capacity
//Bucket(int capacity);
//
//// Copy constructor
//Bucket(const Bucket<Key, Value>& rhs);
//
/**************************************************************************************************
* Destructor
**************************************************************************************************/
template <typename Key, typename Value>
HashMap<Key, Value>::Bucket::~Bucket(void) {
	// TODO
}
//
//// Assignment operator
//Bucket& operator=(const Bucket& rhs);
//
//// Equivalence
//bool operator==(const Bucket& rhs) const;
//
//// Non-equivalence
//bool operator!=(const Bucket& rhs) const;
//

/**************************************************************************************************
* Attempt to pull a value from the bucket, otherwise insert a value into the bucket
**************************************************************************************************/
template <typename Key, typename Value>
Value& HashMap<Key, Value>::Bucket::operator[](const Key& key) {
	Pair* p0 = &(pairs[0]);
	Pair* p1 = &(pairs[1]);
	Pair p2 = pairs[0];

	Value v;
	return v;
}
