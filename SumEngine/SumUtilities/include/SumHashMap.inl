/**************************************************************************************************
* Title: SumHashMap.inl
* Author: Gael Huber
* Description: HashMap is responsible for acting as the cohesive hash table such that there appears
*	to only be one map visible on the implementation side. This is achieved by having an array of 
*	two buckets. The first bucket is the assignment bucket where all new hash assignments exist. 
*	The second bucket only exists as an "old" bucket when we are in the process of incrementally 
*	increasing the size of the hash table. HashMap will, however, contain the set of hash 
*	functions to be used and will determine which hash function is to be used at allocation. 
*	Additionally, HashMap will contain the current list of keys. 
**************************************************************************************************/

/**************************************************************************************************
* Default constructor
**************************************************************************************************/
template <typename Key, typename Value>
HashMap<Key, Value>::HashMap(void)
	: _size(0), _capacity(32)
{
	// Create the bucket and initialize all values
	bucket = Array<typename List<Pair>::Iterator>(_capacity);
	for(int i = 0; i < _capacity; ++i) {
		bucket.push_back(List<Pair>::Iterator());
	}

	// Choose a hashing function
	chooseFunction();
}

/**************************************************************************************************
* Copy constructor
**************************************************************************************************/
template <typename Key, typename Value>
HashMap<Key, Value>::HashMap(const HashMap<Key, Value>& rhs) 
	: _size(0), _capacity(rhs.capacity())
{
	// Create the bucket and initialize all values
	bucket = Array<typename List<Pair>::Iterator>(_capacity);
	for(int i = 0; i < _capacity; ++i) {
		bucket.push_back(List<Pair>::Iterator());
	}
	
	// Iterate through all values and insert them into the hashmap
	Iterator e = rhs.end();
	for(Iterator itr = rhs.begin(); itr != e; ++itr) {
		(*this)[itr->first] = itr->second;
	}
}

/**************************************************************************************************
* Destructor
**************************************************************************************************/
template <typename Key, typename Value>
HashMap<Key, Value>::~HashMap(void) {
}

/**************************************************************************************************
* Assignment operator
**************************************************************************************************/
template <typename Key, typename Value>
HashMap<Key, Value>& HashMap<Key, Value>::operator=(const HashMap<Key, Value>& rhs) {
	if(this == &rhs)
		return *this;

	// Clear current buckets
	bucket.clear();

	// Create the bucket and initialize all values
	bucket = Array<typename List<Pair>::Iterator>(_capacity);
	for(int i = 0; i < _capacity; ++i) {
		bucket.push_back(List<Pair>::Iterator());
	}
	
	// Iterate through all values and insert them into the hashmap
	Iterator e = rhs.end();
	for(Iterator itr = rhs.begin(); itr != e; ++itr) {
		(*this)[itr->first] = itr->second;
	}

	return *this;
}

/**************************************************************************************************
* Test whether the hashmap is empty
**************************************************************************************************/
template <typename Key, typename Value>
inline bool HashMap<Key, Value>::empty(void) const {
	return _size == 0;
}

/**************************************************************************************************
* Returns the size of the hashmap
**************************************************************************************************/
template <typename Key, typename Value>
inline int HashMap<Key, Value>::size(void) const {
	return _size;
}

/**************************************************************************************************
* Returns the maximum size of the hashmap in terms of content
**************************************************************************************************/
template <typename Key, typename Value>
inline int HashMap<Key, Value>::max_size(void) const {
	return (int)((float)_capacity * HASH_LOAD_FACTOR);
}

/**************************************************************************************************
* Return the capacity of the container
**************************************************************************************************/
template <typename Key, typename Value>
inline int HashMap<Key, Value>::capacity(void) const {
	return _capacity;
}

/**************************************************************************************************
* Returns an interator pointing to the beginning of the hashmap
**************************************************************************************************/
template <typename Key, typename Value>
inline typename HashMap<Key, Value>::Iterator HashMap<Key, Value>::begin(void) const {
	return Iterator(pairList.begin());
}

/**************************************************************************************************
* Returns an interator pointing to the end of the hashmap
**************************************************************************************************/
template <typename Key, typename Value>
inline typename HashMap<Key, Value>::Iterator HashMap<Key, Value>::end(void) const {
	return Iterator(pairList.end());
}

/**************************************************************************************************
* Attempt to get a value from the hashmap. If the value does not yet exist, add it.
**************************************************************************************************/
template <typename Key, typename Value>
Value& HashMap<Key, Value>::operator[](const Key& key) {
	// Determine whether a valid value exists at the given slot
	List<Pair>::Iterator _where = _find(key);
	if(_where == List<Pair>::Iterator()) {
		// We have no valid matches, so we will need to insert it.
		_where = _insert(key);
		++_size;
	}

	// There is a valid value, so we will return the second of the iterator
	return (*_where).second;
}

/**************************************************************************************************
* Attempt to get a value from the hashmap at a given key
**************************************************************************************************/
template <typename Key, typename Value>
Value& HashMap<Key, Value>::at(const Key& key) {
	// Return the value at a given key
	return (*_find(key)).second;
}

/**************************************************************************************************
* Find the element with a specific key
**************************************************************************************************/
template <typename Key, typename Value>
typename HashMap<Key, Value>::Iterator HashMap<Key, Value>::find(const Key& key) {
	Iterator itr = _find(key);
	if(itr == Iterator())
		return end();
	return itr;
}

/**************************************************************************************************
* Returns the number of entries with given key. Since duplicate entries are not permitted, this
* basically tells you whether a given key exists in the hashmap.
**************************************************************************************************/
template <typename Key, typename Value>
int HashMap<Key, Value>::count(const Key& key) const {
	if(find(key) == end())
		return 0;
	return 1;
}

/**************************************************************************************************
* Erase the value at the given position if it exists
**************************************************************************************************/
template <typename Key, typename Value>
typename HashMap<Key, Value>::Iterator HashMap<Key, Value>::erase(const typename HashMap<Key, Value>::Iterator position) {
	// If it doesn't exist, return the same iterator
	if(find(itr->first) == end())
		return itr;

	// It exists, so save the value of the iterator we will be returning
	Iterator toReturn = itr + 1;

	// Remove the value from the bucket
	unsigned int slot = func(static_cast<const char*>((*itr).first)) % _capacity;
	bucket[slot] = List<Pair>::Iterator()
	pairList.remove(*itr);
	--_size;
	return toReturn;
}

/**************************************************************************************************
* Erase a given key if it exists (returns the number of elements erased, 1 being successful 0
* otherwise)
**************************************************************************************************/
template <typename Key, typename Value>
int HashMap<Key, Value>::erase(const Key& key) {
	Iterator itr = find(key);
	if(itr == end())
		return 0;
	erase(itr);
	return 1;
}

/**************************************************************************************************
* Erases the range of elements between first and last including first but not including last.
* Returns an iterator pointing to the position immediately after the erased section.
**************************************************************************************************/
template <typename Key, typename Value>
typename HashMap<Key, Value>::Iterator HashMap<Key, Value>::erase(
	const typename HashMap<Key, Value>::Iterator first, const typename HashMap<Key, Value>::Iterator last) {
	Iterator itr = first;
	while(itr != last) {
		itr = erase(itr);
	}
	return itr;
}

/**************************************************************************************************
* Clear the hashmap of all values, leaving it with a size of 0
**************************************************************************************************/
template <typename Key, typename Value>
void HashMap<Key, Value>::clear(void) {
	erase(begin(), end());
}

/**************************************************************************************************
* Choose a hashing function for the map
**************************************************************************************************/
template <typename Key, typename Value>
void HashMap<Key, Value>::chooseFunction(void) {
	// Generate a random float
	float f = nextFloat();
	
	// Find partition for dividing into 11ths
	const float partition = 1.0f / 11.0f;

	// Choose the function
	int function = 0;
	float val = 1.0f;
	while(val > 0.0f) {
		val -= partition;
		if(f > val) {
			switch(function) {
			case 0:
				func = RSHash;
				break;
			case 1:
				func = JSHash;
				break;
			case 2:
				func = PJWHash;
				break;
			case 3:
				func = ELFHash;
				break;
			case 4:
				func = BKDRHash;
				break;
			case 5:
				func = SDBMHash;
				break;
			case 6:
				func = DJBHash;
				break;
			case 7:
				func = DEKHash;
				break;
			case 8:
				func = BPHash;
				break;
			case 9:
				func = FNVHash;
				break;
			case 10:
				func = APHash;
				break;
			}
			break;
		}
		++function;
	}

	// Default
	if(func == 0)
		func = RSHash;
}

/**************************************************************************************************
* Attempt to find a given key in the array and return an iterator
**************************************************************************************************/
template <typename Key, typename Value>
typename List<typename HashMap<Key, Value>::Pair>::Iterator HashMap<Key, Value>::_find(const Key& key) {
	// First thing to do is to try to discover whether an entry exists. We will convert the key to a
	// const char* to hash the key
	unsigned int slot = func(static_cast<const char*>(key)) % _capacity;
	
	// End iterator and blank iterator to avoid endless recreation
	Array<typename List<Pair>::Iterator>::Iterator e = bucket.end();
	List<Pair>::Iterator blank = List<Pair>::Iterator();

	for(Array<typename List<Pair>::Iterator>::Iterator _where = 
		Array<typename List<Pair>::Iterator>::Iterator(&bucket[slot]); 
		_where != e; ++_where) {
		// Key does not exist, return blank iterator
		if(*_where == blank) {
			return blank;
		} 
		// Key may exist (there is a chance of collision correction so we cannot guarantee that the two
		// keys will match)
		else if((*(*_where)).first == key) {
			return *_where;
		}
	}

	// No match found, safety check in case we reach the end of the list
	return blank;
}

/**************************************************************************************************
* Insert a pair with a blank value into the hash map
**************************************************************************************************/
template <typename Key, typename Value>
typename List<typename HashMap<Key, Value>::Pair>::Iterator HashMap<Key, Value>::_insert(const Key& key) {	
	// Check for re-hash
	if((float)_size / (float)_capacity > HASH_LOAD_FACTOR) {
		grow();
	}
	
	// Insert into the list
	pairList.push_front(Pair(key, Value()));
	return _insert(pairList.begin());
}

/**************************************************************************************************
* Insert a pair into the hashmap given a key
**************************************************************************************************/
template <typename Key, typename Value>
typename List<typename HashMap<Key, Value>::Pair>::Iterator HashMap<Key, Value>::_insert(const typename List<typename HashMap<Key, Value>::Pair>::Iterator& itr) {
	// Add to the pair iterator to the array
	unsigned int slot = func(static_cast<const char*>((*itr).first)) % _capacity;
	
	// End iterator and blank iterator to avoid endless recreation
	Array<typename List<Pair>::Iterator>::Iterator e = bucket.end();
	List<Pair>::Iterator blank = List<Pair>::Iterator();

	for(Array<typename List<Pair>::Iterator>::Iterator _where = 
		Array<typename List<Pair>::Iterator>::Iterator(&bucket[slot]); 
		_where != e; ++_where) {
		// Key does not exist, add here!
		if(*_where == blank) {
			bucket[slot] = itr;
			return bucket[slot];
		} 
	}

	// Reached the end, rehash due to over-collision
	grow();
	return _insert(itr);
}

/**************************************************************************************************
* Grow the hash map
**************************************************************************************************/
template <typename Key, typename Value>
void HashMap<Key, Value>::grow(void) {
	// Choose a new hash function
	chooseFunction();

	// First, reset and enlarge the bucket
	_capacity *= 8;
	bucket = Array<typename List<Pair>::Iterator>(_capacity);
	for(int i = 0; i < _capacity; ++i) {
		bucket.push_back(List<Pair>::Iterator());
	}

	// Now we will iterate through the list and re-insert into the bucket
	typename List<Pair>::Iterator e = pairList.end();
	for(typename List<Pair>::Iterator itr = pairList.begin(); itr != e; ++itr) {
		_insert(itr);
	} 
}