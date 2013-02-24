//*************************************************************************************************
// Title: SumInputDeviceMouse.h
// Author: Gael Huber
// Description: Mouse input device
//*************************************************************************************************
#include "SumInputDeviceMouse.h"

//*************************************************************************************************
// Constructor
//*************************************************************************************************
InputDeviceMouse::InputDeviceMouse()
	: InputDevice()
{ }

//*************************************************************************************************
// Constructor
//*************************************************************************************************
InputDeviceMouse::InputDeviceMouse(LPDIRECTINPUT8 input, HWND handle)
	: InputDevice(input, GUID_SysMouse)
{
	// Set data format
	_device->SetDataFormat(&c_dfDIMouse);

	// Set the control we have over the mouse
	_device->SetCooperativeLevel(handle, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	// Initialize
	_device->Acquire();

	// Get input data
	_device->GetDeviceState(sizeof(DIMOUSESTATE), static_cast<LPVOID>(&_currState));

	// Set previous state
	_prevState = _currState;
}

//*************************************************************************************************
// Destructor
//*************************************************************************************************
InputDeviceMouse::~InputDeviceMouse()
{ }

//*************************************************************************************************
// Update function
//*************************************************************************************************
void InputDeviceMouse::update()
{
	// Ensure we havea access
	_device->Acquire();

	// Set previous state
	_prevState = _currState;

	// Get input data
	_device->GetDeviceState(sizeof(DIMOUSESTATE), static_cast<LPVOID>(&_currState));
}
