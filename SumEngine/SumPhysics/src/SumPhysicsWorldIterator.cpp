//*************************************************************************************************
// Title: SumPhysicsWorldIterator.cpp
// Author: Gael Huber
// Description: Iterator for PhysicsWorld. Each iterator functions such that it returns a valid 
//	intersection pair. To qualify as an intersection pair, the objects must be within the same 
//	region of space.
//*************************************************************************************************
#include "SumPhysicsWorld.h"

//*************************************************************************************************
// Constructor given map
//*************************************************************************************************
PhysicsWorld::Iterator::Iterator(const List<PhysicsBody*>& inWorldMap)
	:	_worldMap(inWorldMap)
{
	_first = _worldMap.begin();
	_second = _first;
	++_second;
}

//*************************************************************************************************
// Constructor given map. Derive second from itr + 1
//*************************************************************************************************
PhysicsWorld::Iterator::Iterator(const List<PhysicsBody*>& inWorldMap, List<PhysicsBody*>::Iterator itr)
	:	_worldMap(inWorldMap)
{
	_first = itr;
	_second = _first;
	++_second;
}

//*************************************************************************************************
// Destructor
//*************************************************************************************************
PhysicsWorld::Iterator::~Iterator()
{
}

//*************************************************************************************************
// Non-equivalence operator
//*************************************************************************************************
SBOOL PhysicsWorld::Iterator::operator!=(const Iterator& value)
{
	// First case is for primary values to differ. If they are the same (i.e. we are looking at the 
	// same index) we must look to the secondary value
	return _first != value._first || _second != value._second;
}

//*************************************************************************************************
// Pre-Increment operator
//*************************************************************************************************
PhysicsWorld::Iterator& PhysicsWorld::Iterator::operator++()
{
	// Check second against end
	++_second;
	if(_second == _worldMap.end()) 
	{
		// If second is at the end, increment first
		++_first;
		_second = _first;
		++_second;
	}

	return *this;
}

//*************************************************************************************************
// Return the first physics body
//*************************************************************************************************
PhysicsBody* PhysicsWorld::Iterator::getFirst()
{
	return *_first;
}

//*************************************************************************************************
// Return the second physis body
//*************************************************************************************************
PhysicsBody* PhysicsWorld::Iterator::getSecond()
{
	return *_second;
}
