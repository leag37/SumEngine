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
#include "SumInputManager.h"
#include "SumConfigurationManager.h"
#include "SumResourceManager.h"
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
	// Input manager
	InputManager* _inputManager;

	// Manager for threading and job subsystem
	JobManager* _jobManager;

	// Manager for rendering and effects pipeline
	RenderManager* _renderManager;

	// Resource manager
	ResourceManager* _resourceManager;

	// Configuration manager
	ConfigurationManager* _configurationManager;

	// Jobs
	Job renderJob;
	Job inputJob;

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