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
	:	Singleton(),
		_inputManager(0),
		_jobManager(0),
		_physicsManager(0),
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
	SafeDelete(_physicsManager);
	SafeDelete(_configurationManager);
	SafeDelete(_simulation);
}

//*************************************************************************************************
// Start up the manager
//*************************************************************************************************
void SimulationManager::startUp()
{
	// Seed random number generator
	seed();

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
	_renderManager = new SumEngine::RenderManager();
	_renderManager->startUp();

	// Initialize physics
/*	_physicsManager = new PhysicsManager();
	_physicsManager->startUp();

	// Initialize input system
	_inputManager = new InputManager();
	_inputManager->startUp(0);//_renderManager->handle());
	*/
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
	//_inputManager->shutDown();

	// Shut down physics
	//_physicsManager->shutDown();

	// Shut down rendering
	_renderManager->shutDown();

	// Shut down resource manager
	_resourceManager->shutDown();

	// Shut down game configuration
	_configurationManager->shutDown();

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
// Synchronous order of tasks are as follows:
// 1) Game object update - Ensure physics object matches entity direction based on input/planning
// 2) Animation
// 3) Post-animation update - Ensure rendering object made to match physics object
// 4) Dynamic physics
// 5) Ragdoll physics
// 6) AI
// 7) Audio
// 8) ...
// 9) Input
// 10) Rendering
//
// Asynchronous order of tasks (ignore animation for now):
// < update phys
// > sync phys/anim
// > update world
// < sync phys/anim
// > update anim
// < update world
// > sync world/phys
// < update mesh
// < update anim
// > sync anim/mesh
// < sync world/phys
// > update phys
// < sync anim/mesh
// > update mesh
//*************************************************************************************************
void SimulationManager::gameLoop()
{
	// Jobs for major for engine components
	simulationDelegate = new Delegate1<SFLOAT>(_simulation, &Simulation::update);
	simulationJob = Job(simulationDelegate);

	//physicsDelegate = new Delegate(_physicsManager, &PhysicsManager::update);
	//physicsJob = Job(physicsDelegate);

	renderDelegate = new Delegate(_renderManager, &SumEngine::RenderManager::update); 
	renderJob = Job(renderDelegate);

	//inputDelegate = new Delegate(_inputManager, &InputManager::update);
	//inputJob = Job(inputDelegate);
	
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

		// Cache deltaTime
		SFLOAT deltaTime = _timer.deltaTime();

		// Wait for physics update
		WaitForJob(physicsJob);

		// Wait for input joob
		WaitForJob(inputJob);

		// Update world
		simulationDelegate->setParam1(deltaTime);
		RequestJob(simulationJob);

		// Wait for world update
		WaitForJob(simulationJob);

		// Request input
		//RequestJob(inputJob);

		// Wait for rendering
		WaitForJob(renderJob);

		// Update physics
		//RequestJob(physicsJob);

		// Update rendering
		RequestJob(renderJob);

		/*// Wait for input
		WaitForJob(inputJob);

		// Update simulation logic
		simulationDelegate->setParam1(deltaTime);
		RequestJob(simulationJob);

		// Wait for simulation update
		WaitForJob(simulationJob);	

		// Poll for input
		RequestJob(inputJob);

		// Wait for rendering job to finish
		WaitForJob(renderJob);

		// Render the scene
		RequestJob(renderJob);*/
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

/*		std::ostringstream outs;
		outs.precision(6);
		outs << "SumEngine v0.0.1 " << "    "
			 << "FPS: " << fps << "    "
			 << "Frame Time: " << mspf << " (ms)";
		SetWindowText(gWindowHandle, (LPCSTR) outs.str().c_str());
*/
		// Reset for next average
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}
