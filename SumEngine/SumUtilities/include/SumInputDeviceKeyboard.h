//*************************************************************************************************
// Title: SumInputDeviceKeyboard.h
// Author: Gael Huber
// Description: Keyboard input device
//
// TODO: Process device input and allow delegate functions to be mapped to certain keystates and
//	key combinations
//*************************************************************************************************
#ifndef __SUMINPUTDEVICEKEYBOARD_H__
#define __SUMINPUTDEVICEKEYBOARD_H__

#include "SumInputDevice.h"

class InputDeviceKeyboard : public InputDevice
{
public:
	// Constructor
	InputDeviceKeyboard();

	// Constructor
	InputDeviceKeyboard(LPDIRECTINPUT8 input, HWND handle);

	// Destructor
	~InputDeviceKeyboard();

	// Update function
	void update();

	// Get the keystate for the key	
	SINT getKey(SINT code) const;

private:
	// Current keyboard state
	BYTE _keyState[256];

	// Previous keyboard state
	BYTE _prevKeyState[256];
};

#endif