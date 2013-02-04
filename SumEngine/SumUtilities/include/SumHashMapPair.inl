/**************************************************************************************************
* Title: SumHashMapPair.inl
* Author: Gael Huber
* Description: A pair is nothing more than a key-value pair. These are used exclusively when 
*	dealing with the iterator, pair values are not designed to be kept	in memory at all times.
**************************************************************************************************/

/**************************************************************************************************
* Default constructor
**************************************************************************************************/
template <typename Key, typename Value>
inline HashMap<Key, Value>::Pair::Pair(void)
	: first(Key()), second(Value())
{ }

/**************************************************************************************************
* Constructor specifying key and pair
**************************************************************************************************/
template <typename Key, typename Value>
inline HashMap<Key, Value>::Pair::Pair(const Key& first, const Value& second) 
	: first(first), second(second)
{ }

/**************************************************************************************************
* Copy constructor
**************************************************************************************************/
template <typename Key, typename Value>
inline HashMap<Key, Value>::Pair::Pair(const Pair& rhs) 
	: first(rhs.first), second(rhs.second)
{ }

/**************************************************************************************************
* Destructor
**************************************************************************************************/
template <typename Key, typename Value>
inline HashMap<Key, Value>::Pair::~Pair(void)
{ }

/**************************************************************************************************
* Assignment
**************************************************************************************************/
template <typename Key, typename Value>
inline typename HashMap<Key, Value>::Pair& HashMap<Key, Value>::Pair::operator=(const Pair& rhs) {
	// Self-assignment guard
	if(this == &rhs)
		return *this;
	
	first = rhs.first;
	second = rhs.second;

	return *this;
}

/**************************************************************************************************
* Equivalence
**************************************************************************************************/
template <typename Key, typename Value>
inline bool HashMap<Key, Value>::Pair::operator==(const Pair& rhs) const {
	return first == rhs.first && second == rhs.second;
}

/**************************************************************************************************
* Non-equivalence
**************************************************************************************************/
template <typename Key, typename Value>
inline bool HashMap<Key, Value>::Pair::operator!=(const Pair& rhs) const {
	return first != rhs.first || second != rhs.second;
}

/**************************************************************************************************
* Equivalence of valid data
**************************************************************************************************/
template <typename Key, typename Value>
inline bool HashMap<Key, Value>::Pair::operator==(int rhs) const {
	//memcmp(
	return true;
}

	// Non-equivalence of valid data
	//bool operator!=(int rhs) const;