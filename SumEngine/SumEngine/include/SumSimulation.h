//*************************************************************************************************
// Title: SumSimulation.h
// Author: Gael Huber
// Description: Simulation controller for system.
//*************************************************************************************************
#ifndef __SUMSIMULATION_H__
#define __SUMSIMULATION_H__

#include "SumInclude.h"
#include "SumRenderManager.h"
#include "SumInputManager.h"

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

private:
	// Camera
	Camera* _camera;
};

#endif