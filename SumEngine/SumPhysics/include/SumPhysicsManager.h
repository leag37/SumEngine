//*************************************************************************************************
// Title: SumPhysicsManager.h
// Author: Gael Huber
// Description: Manager for game physics.
//*************************************************************************************************
#ifndef __SUMPHYSICSMANAGER_H__
#define __SUMPHYSICSMANAGER_H__

#include "SumPhysicsCore.h"

class PhysicsManager : public Singleton<PhysicsManager>
{
public:
	// Constructor
	PhysicsManager();

	// Destructor
	~PhysicsManager();

	// Singleton instance
	SUMINLINE static PhysicsManager& getSingleton()
	{
		assert(singleton);
		return *singleton;
	}

	// Singleton pointer
	SUMINLINE static PhysicsManager* getSingletonPtr()
	{
		return singleton;
	}

	// Initialization method
	void startUp();

	// Shut down the manager
	void shutDown();

	// Update function for the manager
	void update();

	// Register a physics object
	void registerPhysicsObject();

private:

};

#endif // __SUMPHYSICSMANAGER_H__