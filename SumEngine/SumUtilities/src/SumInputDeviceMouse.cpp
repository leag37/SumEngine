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
	_device->GetDeviceState(sizeof(DIMOUSESTATE), static_cast<LPVOID>(&_state));
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

	// Get input data
	_device->GetDeviceState(sizeof(DIMOUSESTATE), static_cast<LPVOID>(&_state));
}

SINT InputDeviceMouse::absX()
{
	return _state.lX;
}

SFLOAT InputDeviceMouse::absXf()
{
	return static_cast<SFLOAT>(_state.lX);
}

SINT InputDeviceMouse::absY()
{
	return _state.lY;
}

// Current z
SINT InputDeviceMouse::absZ()
{
	return _state.lZ;
}

// Relative X
SINT InputDeviceMouse::relX()
{
	return _state.lX;
}

SFLOAT InputDeviceMouse::relXf()
{
	return static_cast<SFLOAT>(_state.lX);
}


SFLOAT InputDeviceMouse::relXf() const
{
	return static_cast<SFLOAT>(_state.lX);
}

// Relative Y
SINT InputDeviceMouse::relY()
{
	return _state.lY;
}

SFLOAT InputDeviceMouse::relYf()
{
	return static_cast<SFLOAT>(_state.lY);
}

const SFLOAT InputDeviceMouse::relYf() const
{
	return static_cast<SFLOAT>(_state.lY);
}

// Relative z
SINT InputDeviceMouse::relZ()
{
	return _state.lZ;
}

