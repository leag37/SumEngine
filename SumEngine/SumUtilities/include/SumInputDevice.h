//*************************************************************************************************
// Title: SumInputDevice.h
// Author: Gael Huber
// Description: Basic input device class from which other input devices can use to provide an easy
//	interface when supporting addional input methods.
//*************************************************************************************************
#ifndef __SUMINPUTDEVICE_H__
#define __SUMINPUTDEVICE_H__

#include "SumInclude.h"

class InputDevice
{
public:
	// Constructor
	InputDevice(void);

	// Constructor
	InputDevice(LPDIRECTINPUT8 input, const GUID& deviceInterface);

	// Destructor
	virtual ~InputDevice();

	// Update the device
	virtual void update(void) = 0;

protected:
	// Input device pointer
	LPDIRECTINPUTDEVICE8 _device;

	// Is the device enabled
	SBOOL _enabled;

public:
	// Is the device enabled
	SUMINLINE SBOOL enabled() const
	{
		return _enabled;
	}

	// Set enabled state
	SUMINLINE void setEnabled(SBOOL value)
	{
		_enabled = value;
	}
};

#endif