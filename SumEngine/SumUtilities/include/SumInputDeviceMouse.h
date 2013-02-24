//*************************************************************************************************
// Title: SumInputDeviceMouse.h
// Author: Gael Huber
// Description: Mouse input device
//*************************************************************************************************
#ifndef __SUMINPUTDEVICEMOUSE_H__
#define __SUMINPUTDEVICEMOUSE_H__

#include "SumInputDevice.h"

class InputDeviceMouse : public InputDevice
{
public:
	// Constructor
	InputDeviceMouse();

	// Constructor
	InputDeviceMouse(LPDIRECTINPUT8 input, HWND handle);

	// Destructor
	~InputDeviceMouse();

	// Update function
	void update();

	// Current X
	// Current Y
	// Relative X
	// Relative Y


private:
	// Previous mouse state
	DIMOUSESTATE _prevState;

	// Current mouse state
	DIMOUSESTATE _currState;
};

#endif