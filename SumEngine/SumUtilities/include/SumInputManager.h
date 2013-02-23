//*************************************************************************************************
// Title: SumInputManager.h
// Author: Gael Huber
// Description: Manager for all user input
//*************************************************************************************************
#ifndef __SUMINPUTMANAGER_H__
#define __SUMINPUTMANAGER_H__

#include "SumInclude.h"

class InputManager : public Singleton<InputManager>
{
public:
	// Constructor
	InputManager();

	// Destructor
	virtual ~InputManager();

	// Start up
	void startUp();

	// Shut down
	void shutDown();

	// Poll for input
	void update();

public:
	SUMINLINE static InputManager& getSingleton()
	{
		assert(singleton);
		return *singleton;
	}

	SUMINLINE static InputManager* getSingletonPtr()
	{
		return singleton;
	}


};

#endif