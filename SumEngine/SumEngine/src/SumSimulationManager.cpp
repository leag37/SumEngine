//*************************************************************************************************
// Title: SumSimulationManager.cpp
// Author: Gael Huber
// Description: Manages primary game loop and manages subsystem start up and shutdown.
//*************************************************************************************************
#include "SumSimulationManager.h"

//*************************************************************************************************
// Initialize the singleton instance of this class to 0
//*************************************************************************************************
template <> SimulationManager* Singleton<SimulationManager>::singleton = 0;

//*************************************************************************************************
// Constructor
//*************************************************************************************************
SimulationManager::SimulationManager()
	:	_jobManager(0),
		_renderManager(0)
{ }

//*************************************************************************************************
// Destructor
//*************************************************************************************************
SimulationManager::~SimulationManager()
{
	SafeDelete(_jobManager);
	SafeDelete(_renderManager);
	// TODO: Shut down input system
	// TODO: Shut down physics
	// TODO: Shut down resource manager
	// TODO: Shut down game configuration
}

//*************************************************************************************************
// Start up the manager
//*************************************************************************************************
void SimulationManager::startUp()
{
	// TODO: Seed random number generator

	// Initialize memory subsystems
	CreateAllocators();
	
	// TODO: Initialize game configuration

	// TODO: Initialize job manager
	_jobManager = new JobManager();
	_jobManager->startUp(50);

	// TODO: Initialize resources

	// Initialize rendering
	_renderManager = new RenderManager();
	_renderManager->startUp();

	// TODO: Initialize physics

	// TODO: Initialize input system
}

//*************************************************************************************************
// Shut down the manager
//*************************************************************************************************
void SimulationManager::shutDown()
{
	// TODO: Shut down input system

	// TODO: Shut down physics

	// Shut down rendering
	_renderManager->shutDown();

	// TODO: Shut down resource manager

	// Shut down job manager
	_jobManager->shutDown();

	// TODO: Shut down game configuration

	// Destroy allocators
	DestroyAllocators();
}

//*************************************************************************************************
// Run the simulation
//*************************************************************************************************
void SimulationManager::run()
{	
	gameLoop();
}

//*************************************************************************************************
// Game loop for the engine
//*************************************************************************************************
void SimulationManager::gameLoop()
{

}
