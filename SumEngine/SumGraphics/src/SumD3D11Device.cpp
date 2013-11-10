//*************************************************************************************************
// Title: SumD3D11Device.cpp
// Author: Gael Huber
// Description: Encapsulation device for D3D device info. This is useful for both the actual device
//	and the immediate context.
//*************************************************************************************************
#include "SumD3D11Device.h"

namespace SumEngine
{
	//*************************************************************************************************
	// Base constructor
	//*************************************************************************************************
	D3D11Device::D3D11Device()
		:	_device(0), _immediateContext(0)
	{ }

	//*************************************************************************************************
	// Constructor
	// @param
	//	device The ID3DDevice to encapsulate
	//*************************************************************************************************
	D3D11Device::D3D11Device(ID3D11Device* device)
		:	_device(device)
	{
		if(_device != 0)
		{
			_device->GetImmediateContext(&_immediateContext);
		}
	}

	//*************************************************************************************************
	// Copy constructor
	// @param
	//	device D3D11Device to copy
	//*************************************************************************************************
	D3D11Device::D3D11Device(const D3D11Device& device)
		:	_device(device._device),
			_immediateContext(device._immediateContext)
	{ }

	//*************************************************************************************************
	// Destructor
	//*************************************************************************************************
	D3D11Device::~D3D11Device()
	{ }

	//*************************************************************************************************
	// Assignment operator
	// @param
	//	device The ID3D11Device that is to be wrapped by this class
	// @return
	//	D3D11Device The device
	//*************************************************************************************************
	D3D11Device& D3D11Device::operator=(ID3D11Device* device)
	{
		_device = device;
		if(_device != 0)
		{
			_device->GetImmediateContext(&_immediateContext);
		}
		return *this;
	}

	//*************************************************************************************************
	// Check if the device is null
	// @return
	//	SBOOL True if the device is null, false otherwise
	//*************************************************************************************************
	SBOOL D3D11Device::isNull()
	{
		return _device == 0;
	}
		
}	// Namespace