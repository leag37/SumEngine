//*************************************************************************************************
// Title: SumInputDeviceKeyboard.cpp
// Author: Gael Huber
// Description: Keyboard input device
//*************************************************************************************************
#include "SumInputDeviceKeyboard.h"

//*************************************************************************************************
// Constructor
//*************************************************************************************************
InputDeviceKeyboard::InputDeviceKeyboard()
	: InputDevice()
{ }

//*************************************************************************************************
// Constructor
//*************************************************************************************************
InputDeviceKeyboard::InputDeviceKeyboard(LPDIRECTINPUT8 input, HWND handle)
	: InputDevice(input, GUID_SysKeyboard)
{
	// Set keyboard format
	_device->SetDataFormat(&c_dfDIKeyboard);

	// Set control we have over keyboard
	_device->SetCooperativeLevel(handle, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	// Acquire the device
	_device->Acquire();

	// Get input data
	update();
}

//*************************************************************************************************
// Destructor
//*************************************************************************************************
InputDeviceKeyboard::~InputDeviceKeyboard()
{ }

//*************************************************************************************************
// Update function
//*************************************************************************************************
void InputDeviceKeyboard::update()
{
	// Copy device state
	for(SINT i = 0; i < 256; ++i)
	{
		_prevKeyState[i] = _keyState[i];
	}

	_device->GetDeviceState(256, static_cast<LPVOID>(_keyState));
}

//*************************************************************************************************
// Get the keystate for the key	
//*************************************************************************************************
SINT InputDeviceKeyboard::getKey(SINT code) const
{
	return _keyState[code] && 0x80;
}

//*************************************************************************************************
// Get whether the keystate changed
//*************************************************************************************************
SBOOL InputDeviceKeyboard::getKeyChanged(SINT code) const
{
	return _prevKeyState[code] != _keyState[code];
}

//*************************************************************************************************
// Get whether a key was pressed
//*************************************************************************************************
SBOOL InputDeviceKeyboard::getKeyPressed(SINT code) const
{
	return getKeyChanged(code) && _keyState[code] == 0x80;
}

//*************************************************************************************************
// Get whether a key was released
//*************************************************************************************************
SBOOL InputDeviceKeyboard::getKeyReleased(SINT code) const
{
	return true;
}

