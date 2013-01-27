//*************************************************************************************************
// Title: SumSimulationManager.h
// Author: Gael Huber
// Description: Manages primary game loop and manages subsystem start up and shutdown.
//*************************************************************************************************
#ifndef __SUMSIMULATIONMANAGER_H__
#define __SUMSIMULATIONMANAGER_H__

#include "SumInclude.h"
#include "SumJobManager.h"
#include "SumRenderManager.h"
#include "SumDelegate.h"

class SimulationManager : public Singleton<SimulationManager>
{
public:
	// Constructor
	SimulationManager();

	// Destructor
	~SimulationManager();

	// Start up the manager
	void startUp();

	// Shut down the manager
	void shutDown();

	// Run the simulation
	void run();

private:
	// Game loop for the engine
	void gameLoop();

private:
	// Manager for threading and job subsystem
	JobManager* _jobManager;

	// Manager for rendering and effects pipeline
	RenderManager* _renderManager;

	// Can the application run?
	SBOOL _canRun;

// Inline functions
public:
	// Get singleton object
	SUMINLINE static SimulationManager& getSingleton()
	{
		assert(singleton);
		return *singleton;
	}

	// Get singleton pointer
	SUMINLINE static SimulationManager* getSingletonPtr()
	{
		return singleton;
	}
};

#endif