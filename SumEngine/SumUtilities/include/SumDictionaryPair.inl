/**************************************************************************************************
* Title: SumDictionaryPair.inl
* Author: Gael Huber
* Description: Defines dictionary key-value pair
**************************************************************************************************/

/**************************************************************************************************
* Constructor
**************************************************************************************************/
template <typename Key, typename Value>
Dictionary<Key, Value>::Pair::Pair(void) 
{ }

/**************************************************************************************************
* Constructor populating key and value
**************************************************************************************************/
template <typename Key, typename Value>
Dictionary<Key, Value>::Pair::Pair(const Key& k, const Value& v) 
	: key(k), value(v)
{ }

/**************************************************************************************************
* Copy-constructor
**************************************************************************************************/
template <typename Key, typename Value>
Dictionary<Key, Value>::Pair::Pair(const Pair& rhs) 
	: key(rhs.getKey()), value(rhs.getValue())
{ }

/**************************************************************************************************
* Destructor
**************************************************************************************************/
template <typename Key, typename Value>
Dictionary<Key, Value>::Pair::~Pair(void) 
{ }
	
/**************************************************************************************************
* Assignemnt operator
**************************************************************************************************/
template <typename Key, typename Value>
const typename Dictionary<Key, Value>::Pair& Dictionary<Key, Value>::Pair::operator=(const Pair& rhs) {
	// Self-assignment guard
	if(&rhs == this)
		return *this;

	// Set key and value
	key = rhs.getKey();
	value = rhs.getValue();

	// Return this
	return *this;
}

/**************************************************************************************************
* Equivalence
**************************************************************************************************/
template <typename Key, typename Value>
const bool Dictionary<Key, Value>::Pair::operator==(const Pair& rhs) const {
	// Return true if both the key and value are equal
	return (key == rhs.getKey() && value == rhs.getValue()) ? true : false;
}

/**************************************************************************************************
* Non-equivalence
**************************************************************************************************/
template <typename Key, typename Value>
const bool Dictionary<Key, Value>::Pair::operator!=(const Pair& rhs) const {
	// If either the key or the value is not equal, return false
	return (key == getKey() && value == rhs.getValue()) ? false : true;
}

/**************************************************************************************************
* Return the key associated with this pair
**************************************************************************************************/
template <typename Key, typename Value>
const Key& Dictionary<Key, Value>::Pair::getKey(void) const {
	return key;
}

/**************************************************************************************************
* Return the value associated with this pair
**************************************************************************************************/
template <typename Key, typename Value>
const Value& Dictionary<Key, Value>::Pair::getValue(void) const {
	return value;
}

/**************************************************************************************************
* Set the value associated with this pair
**************************************************************************************************/
template <typename Key, typename Value>
void Dictionary<Key, Value>::Pair::setValue(const Value& v) {
	value = v;
}

/**************************************************************************************************
* Swap the data within this pair with the data held within another pair
**************************************************************************************************/
template <typename Key, typename Value>
void Dictionary<Key, Value>::Pair::swap(typename Dictionary<Key, Value>::Pair& rhs) {
	// Create a temporary pair
	Pair tmp = rhs;

	// Assign this to rhs
	rhs = *this;

	// Assign temporary pair to this
	*this = tmp;
}