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
	SINT absX();

	SFLOAT absXf();

	// Current Y
	SINT absY();

	// Current z
	SINT absZ();

	// Relative X
	SINT relX();

	// Relative x as a float
	SFLOAT relXf();

	SFLOAT relXf() const;

	// Relative Y
	SINT relY();

	// Relative y as a float
	SFLOAT relYf();

	const SFLOAT relYf() const;

	// Relative z
	SINT relZ();

private:
	// Current mouse state
	DIMOUSESTATE _state;
};

#endif