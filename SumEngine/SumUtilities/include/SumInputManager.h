//*************************************************************************************************
// Title: SumInputManager.h
// Author: Gael Huber
// Description: Manager for all user input
//*************************************************************************************************
#ifndef __SUMINPUTMANAGER_H__
#define __SUMINPUTMANAGER_H__

#include "SumInclude.h"
#include "SumInputDeviceMouse.h"

#define SUM_MOUSE 0
#define SUM_KEYBOARD 1

class InputManager : public Singleton<InputManager>
{
public:
	// Constructor
	InputManager();

	// Destructor
	virtual ~InputManager();

	// Start up
	void startUp(HWND handle);

	// Shut down
	void shutDown();

	// Poll for input
	void update();

private:
	// DirectInput device
	LPDIRECTINPUT8 _inputDevice;

	// Copy of the window handle
	HWND _handle;

	// Keyboard
	//Keyboard* _keyboard;

	// Mouse
	InputDeviceMouse* _mouse;

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

	SUMINLINE const InputDeviceMouse* mouse() const
	{
		return _mouse;
	}
};

#endif