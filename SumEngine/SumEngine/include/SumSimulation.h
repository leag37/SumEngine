//*************************************************************************************************
// Title: SumSimulation.h
// Author: Gael Huber
// Description: Simulation controller for system.
//*************************************************************************************************
#ifndef __SUMSIMULATION_H__
#define __SUMSIMULATION_H__

#include "SumInclude.h"
#include "SumPhysicsManager.h"
#include "SumRenderManager.h"
#include "SumInputManager.h"
#include "SumMovableEntity.h"

class Simulation
{
public:
	// Constructor
	Simulation();

	// Destructor
	~Simulation();

	// Start up the simulation
	void startUp();

	// Shut down the simulation
	void shutDown();

	// Update the world
	void update(SFLOAT dTime);

private:
	// Camera
	Camera* _camera;

	// TEMP
	MovableEntity* _box;
	Entity* _plane;
};

#endif