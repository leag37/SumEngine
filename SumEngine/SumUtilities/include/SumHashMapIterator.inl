/**************************************************************************************************
* Title: SumHashMapIterator.inl
* Author: Gael Huber
* Description: The iterator for the hash map will permit linear progressing through the hash map in
*	order of key values. The iterator should act similar to an array iterator, however data 
*	contained should be a pair rather than discreet references to the data.
**************************************************************************************************/

/**************************************************************************************************
* Default constructor
**************************************************************************************************/
template <typename Key, typename Value>
inline HashMap<Key, Value>::Iterator::Iterator(void)
{ }

/**************************************************************************************************
* Constructor given an iterator in the list
**************************************************************************************************/
template <typename Key, typename Value>
inline HashMap<Key, Value>::Iterator::Iterator(const typename List<Pair>::Iterator& data)
	: data(data)
{ }

/**************************************************************************************************
* Copy constructor
**************************************************************************************************/
template <typename Key, typename Value>
HashMap<Key, Value>::Iterator::Iterator(const Iterator& rhs)
	: data(static_cast<List<Pair>::Iterator&>(rhs))
{ }

/**************************************************************************************************
* Destructor
**************************************************************************************************/
template <typename Key, typename Value>
HashMap<Key, Value>::Iterator::~Iterator(void)
{ }

/**************************************************************************************************
* Return the data referenced
**************************************************************************************************/
template <typename Key, typename Value>
inline typename HashMap<Key, Value>::Pair& HashMap<Key, Value>::Iterator::operator*(void) const {
	return *data;
}

/**************************************************************************************************
* Return a pointer to the class object
**************************************************************************************************/
template <typename Key, typename Value>
inline typename HashMap<Key, Value>::Pair* HashMap<Key, Value>::Iterator::operator->(void) const {
	return &**this;
}

/**************************************************************************************************
* Pre-increment
**************************************************************************************************/
template <typename Key, typename Value>
inline typename HashMap<Key, Value>::Iterator& HashMap<Key, Value>::Iterator::operator++(void) {
	++data;
	return *this;
}
	
/**************************************************************************************************
* Post-increment
**************************************************************************************************/
template <typename Key, typename Value>
inline typename HashMap<Key, Value>::Iterator HashMap<Key, Value>::Iterator::operator++(int rhs) {
	Iterator itr = *this;
	++data;
	return itr;
}

/**************************************************************************************************
* Pre-decrement
**************************************************************************************************/
template <typename Key, typename Value>
inline typename HashMap<Key, Value>::Iterator& HashMap<Key, Value>::Iterator::operator--(void) {
	--data;
	return *this;
}

/**************************************************************************************************
* Post-decrement
**************************************************************************************************/
template <typename Key, typename Value>
inline typename HashMap<Key, Value>::Iterator HashMap<Key, Value>::Iterator::operator--(int rhs) {
	Iterator itr = *this;
	--data;
	return itr;
}

/**************************************************************************************************
* Increment by integer
**************************************************************************************************/
template <typename Key, typename Value>
inline typename HashMap<Key, Value>::Iterator& HashMap<Key, Value>::Iterator::operator+=(int rhs) {
	for(int i = 0; i < rhs; ++i) {
		++*this;
	}
	return *this;
}

/**************************************************************************************************
* Return this + integer
**************************************************************************************************/
template <typename Key, typename Value>
inline typename HashMap<Key, Value>::Iterator HashMap<Key, Value>::Iterator::operator+(int rhs) const {
	Iterator itr = *this;
	for(int i = 0; i < rhs; ++i) {
		++*this;
	}
	return itr;
}

/**************************************************************************************************
* Decrement by integer
**************************************************************************************************/
template <typename Key, typename Value>
inline typename HashMap<Key, Value>::Iterator& HashMap<Key, Value>::Iterator::operator-=(int rhs) {
	for(int i = 0; i < rhs; ++i) {
		--*this;
	}
	return *this;
}

/**************************************************************************************************
* Return this - integer
**************************************************************************************************/
template <typename Key, typename Value>
inline typename HashMap<Key, Value>::Iterator HashMap<Key, Value>::Iterator::operator-(int rhs) const {
	Iterator itr = *this;
	for(int i = 0; i < rhs; ++i) {
		--*this;
	}
	return itr;
}

/**************************************************************************************************
* Return the data held
**************************************************************************************************/
template <typename Key, typename Value>
typename HashMap<Key, Value>::Pair& HashMap<Key, Value>::Iterator::operator[](int rhs) const {
	Iterator itr = *this;
	for(int i = 0; i < rhs; ++i) {
		++itr;
	}
	return *itr;
}

/**************************************************************************************************
* Equivanlence operator
**************************************************************************************************/
template <typename Key, typename Value>
inline bool HashMap<Key, Value>::Iterator::operator==(const typename HashMap<Key, Value>::Iterator& rhs) const {
	return *data == *rhs;
}

/**************************************************************************************************
* Non-equivalence
**************************************************************************************************/
template <typename Key, typename Value>
inline bool HashMap<Key, Value>::Iterator::operator!=(const typename HashMap<Key, Value>::Iterator& rhs) const {
	return *data != *rhs;
}