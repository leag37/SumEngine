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
		_configurationManager(0),
		_simulation(0)
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
	SafeDelete(_simulation);
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
	_inputManager->startUp(_renderManager->handle());

	// Initialize simulation
	_simulation = new Simulation();
	_simulation->startUp();

	// The engine can now run
	gCanRun = true;
	_timer.reset();
}

//*************************************************************************************************
// Shut down the manager
//*************************************************************************************************
void SimulationManager::shutDown()
{
	// Shut down job manager
	_jobManager->shutDown();

	// Shut down simulation
	_simulation->shutDown();

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
	renderJob = Job(new Delegate(_renderManager, &RenderManager::update));
	inputJob = Job(new Delegate(_inputManager, &InputManager::update));

	//Job job = Job(new Delegate1<int>(_simulation, &Simulation::test, 2));
	//RequestJob(job);
	//Delegate1<int> woo = Delegate1<int>(_simulation, &Simulation::test, 2);
	//woo();


	
	// Define a struct to hold a Windows event message
	MSG msg;

	// While windows message queue is populated and the program has not been exited
	while(gCanRun)
	{
		// Timer tick
		_timer.tick();
		calculateFrameStats();

		// Check for any Windows messages
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// Translate keystroke message to a compatible format
			TranslateMessage(&msg);

			// Dispatch the message to WindowProcess function
			DispatchMessage(&msg);
		}

		// Wait for input
		WaitForJob(inputJob);

		// Update simulation logic


		// Wait for simulation update


		// Poll for input
		RequestJob(inputJob);

		// Wait for rendering job to finish
		WaitForJob(renderJob);

		// Render the scene
		RequestJob(renderJob);
	}
}

//*************************************************************************************************
// Calculate the frame statistics
//*************************************************************************************************
void SimulationManager::calculateFrameStats()
{
	// Compute average frames per second and average time it takes to render one frame
	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	++frameCnt;

	// Compute averages over one second period
	if((_timer.totalTime() - timeElapsed) >= 1.0f) {
		float fps = (float)frameCnt;
		float mspf = 1000.0f / fps;

		std::ostringstream outs;
		outs.precision(6);
		outs << "SumEngine v0.0.1 " << "    "
			 << "FPS: " << fps << "    "
			 << "Frame Time: " << mspf << " (ms)";
		SetWindowText(gWindowHandle, (LPCSTR) outs.str().c_str());

		// Reset for next average
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}
