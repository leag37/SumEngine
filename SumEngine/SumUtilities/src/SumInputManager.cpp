//*************************************************************************************************
// Title: SumInputManager.cpp
// Author: Gael Huber
// Description: Manager for all user input
//*************************************************************************************************
#include "SumInputManager.h"

//*************************************************************************************************
// Initialize singleton to 0
//*************************************************************************************************
template <> InputManager* Singleton<InputManager>::singleton = 0;

//*************************************************************************************************
// Constructor
//*************************************************************************************************
InputManager::InputManager()
{ }

//*************************************************************************************************
// Destructor
//*************************************************************************************************
InputManager::~InputManager()
{

}

//*************************************************************************************************
// Start up
//*************************************************************************************************
void InputManager::startUp(HWND handle)
{
	// Create the DirectInput device
	DirectInput8Create(	
		gHInstance,//GetModuleHandle(0),							// Application handle
		DIRECTINPUT_VERSION,						// Current DirectInput version
		IID_IDirectInput8,							// DirectInput interface version
		reinterpret_cast<void**>(&_inputDevice),	// DirectInput interface pointer
		NULL);

	// Save the handle
	_handle = handle;

	// Create the keyboard

	// Create the mouse
	_mouse = new InputDeviceMouse(_inputDevice, _handle);

}

//*************************************************************************************************
// Shut down
//*************************************************************************************************
void InputManager::shutDown()
{

}

//*************************************************************************************************
// Poll for input
//*************************************************************************************************
void InputManager::update()
{
	if(_mouse && _mouse->enabled())
	{
		_mouse->update();
	}
}

