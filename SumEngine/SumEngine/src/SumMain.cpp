//*************************************************************************************************
// Title: SumMain.cpp
// Author: Gael Huber
// Description: Main class of the engine. Responsible for launching the engine proper.
//
// TODO: Find out why debug mode doesn't work as standalone exe
//*************************************************************************************************
#include "SumSimulationManager.h"

//*************************************************************************************************
// Main method of the engine.
//*************************************************************************************************
SINT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) 
{
	// Initialize the simulation
	SimulationManager* simulation = new SimulationManager();
	simulation->startUp();

	// Run the simulation
	simulation->run();

	// Shut down the simulation
	simulation->shutDown();
	SafeDelete(simulation);
	
	// End program
	return 0;
}