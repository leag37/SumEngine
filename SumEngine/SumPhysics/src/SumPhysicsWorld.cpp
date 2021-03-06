//*************************************************************************************************
// Title: SumPhysicsWorld.cpp
// Author: Gael Huber
// Description: The physical representation of the world. This houses all physics objects and
//	houses the spatial partitioning structures they get stored in.
//*************************************************************************************************
#include "SumPhysicsWorld.h"

//*************************************************************************************************
// Constructor
//*************************************************************************************************
PhysicsWorld::PhysicsWorld()
{ }

//*************************************************************************************************
// Destructor
//*************************************************************************************************
PhysicsWorld::~PhysicsWorld()
{
	_worldMap.clear();
}

//*************************************************************************************************
// Add a body to the world
//*************************************************************************************************
void PhysicsWorld::addBody(PhysicsBody* body)
{
	_worldMap.push_back(body);
}

//*************************************************************************************************
// Get the start of the iterator
//*************************************************************************************************
PhysicsWorld::Iterator PhysicsWorld::begin()
{
	return Iterator(_worldMap, _worldMap.begin());
}

//*************************************************************************************************
// Get the end of the iterator
//*************************************************************************************************
PhysicsWorld::Iterator PhysicsWorld::end()
{
	return Iterator(_worldMap, --_worldMap.end());
}
