//*************************************************************************************************
// Title: SumPhysicsWorld.h
// Author: Gael Huber
// Description: The physical representation of the world. This houses all physics objects and
//	houses the spatial partitioning structures they get stored in.
//*************************************************************************************************
#ifndef __SUMPHYSICSWORLD_H__
#define __SUMPHYSICSWORLD_H__

#include "SumPhysicsCore.h"

class PhysicsWorld
{
public:
	// Iterator declaration
	class Iterator;

public:
	// Constructor
	PhysicsWorld();

	// Destructor
	~PhysicsWorld();

	// Add a body to the world
	void addBody(PhysicsBody* body);

	// Get the start of the iterator
	Iterator begin();

	// Get the end of the iterator
	Iterator end();

private:
	// List of bodies
	List<PhysicsBody*> _worldMap;
};


// Iterator for the world. Each iterator functions such that it returns a valid intersection pair. 
// To qualify as an intersection pair, the objects must be within the same region of space.
class PhysicsWorld::Iterator
{
public:
	// Default constructor
	Iterator();

	// Constructor given map
	Iterator(const List<PhysicsBody*>& inWorldMap);

	// Destructor
	~Iterator();

	// Pre-Increment operator
	Iterator& operator++();

	// Return the first physics body
	PhysicsBody* getFirst();

	// Return the second physis body
	PhysicsBody* getSecond();

private:
	// First body
	PhysicsBody* _first;

	// Second body
	PhysicsBody* _second;

	// Reference to list
	List<PhysicsBody*>& _worldMap;
};

#endif // __SUMPHYSICSWORLD_H__