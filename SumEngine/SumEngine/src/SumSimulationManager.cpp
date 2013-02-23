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
	:	_inputManager(0),
		_jobManager(0),
		_renderManager(0),
		_resourceManager(0),
		_configurationManager(0)
{ }

//*************************************************************************************************
// Destructor
//*************************************************************************************************
SimulationManager::~SimulationManager()
{
	SafeDelete(_jobManager);
	SafeDelete(_renderManager);
	SafeDelete(_resourceManager);
	SafeDelete(_inputManager);
	// TODO: Shut down physics
	// TODO: Shut down resource manager
	SafeDelete(_configurationManager);
}

//*************************************************************************************************
// Start up the manager
//*************************************************************************************************
void SimulationManager::startUp()
{
	// TODO: Seed random number generator

	// Initialize memory subsystems
	CreateAllocators();
	
	// Initialize game configuration
	_configurationManager = new ConfigurationManager();
	_configurationManager->startUp();

	// Initialize job manager
	_jobManager = new JobManager();
	SINT numThreads = _configurationManager->getConfiguration("Engine")->retrieveValue("threads").toInt();
	_jobManager->startUp(numThreads);

	// Initialize resources
	_resourceManager = new ResourceManager();
	_resourceManager->startUp();

	// Initialize rendering
	_renderManager = new RenderManager();
	_renderManager->startUp();

	// TODO: Initialize physics

	// Initialize input system
	_inputManager = new InputManager();
	_inputManager->startUp();

	// The engine can now run
	gCanRun = true;
}

//*************************************************************************************************
// Shut down the manager
//*************************************************************************************************
void SimulationManager::shutDown()
{
	// Shut down job manager
	_jobManager->shutDown();

	// Shut down input system
	_inputManager->shutDown();

	// TODO: Shut down physics

	// Shut down rendering
	_renderManager->shutDown();

	// Shut down resource manager
	_resourceManager->shutDown();

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
	// Jobs for major for engine components
	renderJob = Job(Delegate0(_renderManager, &RenderManager::update));
	inputJob = Job(Delegate0(_inputManager, &InputManager::update));
	
	// Define a struct to hold a Windows event message
	MSG msg;

	// While windows message queue is populated and the program has not been exited
	while(gCanRun)
	{
		// Check for any Windows messages
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// Translate keystroke message to a compatible format
			TranslateMessage(&msg);

			// Dispatch the message to WindowProcess function
			DispatchMessage(&msg);
		}

		// Poll for input
		RequestJob(inputJob);

		// Wait for rendering job to finish
		WaitForJob(renderJob);

		// Wait for input
		WaitForJob(inputJob);

		// Render the scene
		RequestJob(renderJob);
	}
}
