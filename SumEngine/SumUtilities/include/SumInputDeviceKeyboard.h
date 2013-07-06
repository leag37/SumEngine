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

#define MAX_KEYS 256

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

	// Get whether a keystate changed
	SBOOL getKeyChanged(SINT code) const;

	// Get whether a key was pressed
	SBOOL getKeyPressed(SINT code) const;

	// Get whether a key was released
	SBOOL getKeyReleased(SINT code) const;

private:
	// Current keyboard state
	BYTE _keyState[256];

	// Previous keyboard state
	BYTE _prevKeyState[256];
};

#endif