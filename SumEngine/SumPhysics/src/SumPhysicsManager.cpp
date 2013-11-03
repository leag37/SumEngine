//*************************************************************************************************
// Title: SumPhysicsManager.h
// Author: Gael Huber
// Description: Manager for game physics.
//*************************************************************************************************
#include "SumPhysicsManager.h"

//*************************************************************************************************
// Initialize the singleton instance of this class to 0
//*************************************************************************************************
template <> PhysicsManager* Singleton<PhysicsManager>::singleton = 0;

//*************************************************************************************************
// Constructor
//*************************************************************************************************
PhysicsManager::PhysicsManager()
{

}

//*************************************************************************************************
// Destructor
//*************************************************************************************************
PhysicsManager::~PhysicsManager()
{

}

//*************************************************************************************************
// Initialization method
//*************************************************************************************************
void PhysicsManager::startUp()
{

}

//*************************************************************************************************
// Shut down the manager
//*************************************************************************************************
void PhysicsManager::shutDown()
{

}

//*************************************************************************************************
// Update function for the manager
//*************************************************************************************************
void PhysicsManager::update()
{
	// Broad phase collision culling, update AABBs and compute overlapping pairs
	queryForCollisionPairs();
	processQueue();

	// Remove overlapping pairs using BV test

	// Compute contact points, resolve interpenetrations

	// Resolve constraints

	// Solve equations of motion
}

//*************************************************************************************************
// Process the job queue
//*************************************************************************************************
void PhysicsManager::processQueue()
{
	// Process events
	while(_jobQueue.size() > 0)
	{
		PhysicsJob* job = _jobQueue.front();
		job->execute();
		_jobQueue.pop_front();
		SafeDelete(job);
	}
}

//*************************************************************************************************
// Register a physics object
//*************************************************************************************************
void PhysicsManager::registerPhysicsObject(PhysicsBody* body)
{
	// Push to the raw list of bodies
	_bodyList.push_back(body);

	// Push to the world
	_world.addBody(body);
}

//*************************************************************************************************
// Query for all potential collision pairs
//*************************************************************************************************
void PhysicsManager::queryForCollisionPairs()
{
	// Let's initialize our delegate function for collision tests
	Delegate2<PhysicsBody*, PhysicsBody*> collisionDelegate = Delegate2<PhysicsBody*, PhysicsBody*>(this, &PhysicsManager::testCollision);

	// Iterate through our physics map
	PhysicsWorld::Iterator end = _world.end();

	for(PhysicsWorld::Iterator itr = _world.begin(); itr != end; ++itr)
	{
		// Update parameters
		PhysicsJob* job = new PhysicsCollisionTestJob(collisionDelegate, itr.getFirst(), itr.getSecond());
		_jobQueue.push_back(job);
	}
}

//*************************************************************************************************
// Test a potential collision pair
//*************************************************************************************************
void PhysicsManager::testCollision(PhysicsBody* body1, PhysicsBody* body2)
{
	TestCollision(body1->getAABB(), body2->getAABB());
	int a = 0;
}

