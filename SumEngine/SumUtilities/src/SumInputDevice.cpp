//*************************************************************************************************
// Title: SumInputDevice.cpp
// Author: Gael Huber
// Description: Basic input device class from which other input devices can use to provide an easy
//	interface when supporting addional input methods.
//*************************************************************************************************
#include "SumInputDevice.h"

//*************************************************************************************************
// Constructor
//*************************************************************************************************
InputDevice::InputDevice(void)
	: _device(0), _enabled(false)
{ }

//*************************************************************************************************
// Constructor
//*************************************************************************************************
InputDevice::InputDevice(LPDIRECTINPUT8 input, const GUID& deviceInterface)
	: _device(0), _enabled(false)
{
	// Create the device
	input->CreateDevice(deviceInterface, &_device, NULL);

	// The device is now enabled
	_enabled = true;
}

//*************************************************************************************************
// Destructor
//*************************************************************************************************
InputDevice::~InputDevice()
{
	// Delete the device
	_device->Unacquire();
	ReleaseCOM(_device);
}
