//*************************************************************************************************
// Title: SumD3D11Driver.cpp
// Author: Gael Huber
// Description: A class representative of each graphic card/driver available to the engine.
//*************************************************************************************************
#include "SumD3D11Driver.h"

namespace SumEngine
{

	//*************************************************************************************************
	// Default constructor
	//*************************************************************************************************
	D3D11Driver::D3D11Driver()
		: _adapter(0)
	{ }

	//*************************************************************************************************
	// Constructor
	// @param
	//	adapter The DXGIAdapter1 pointer representing the particular D3D driver
	//*************************************************************************************************
	D3D11Driver::D3D11Driver(IDXGIAdapter1* adapter)
		: _adapter(adapter)
	{
		if(_adapter != 0)
		{
			_adapter->GetDesc1(&_adapterDescription);
		}
	}

	//*************************************************************************************************
	// Destructor
	//*************************************************************************************************
	D3D11Driver::~D3D11Driver()
	{
		ReleaseCOM(_adapter);
	}

	//*************************************************************************************************
	// Get the adapter
	// @return
	//	IDXGIAdapter1 The adapter to be used for the driver
	//*************************************************************************************************
	IDXGIAdapter1* D3D11Driver::getAdapter() const
	{
		return _adapter;
	}

	//*************************************************************************************************
	// Get the dedicated system memory of this adapter
	// @return
	//	SUINT The dedicated system memory
	//*************************************************************************************************
	SUINT D3D11Driver::getDedicatedSystemMemory() const
	{
		return _adapterDescription.DedicatedSystemMemory;
	}

	//*************************************************************************************************
	// Get the dedicated video memory of this adapter
	// @return
	//	SUINT The dedicated video memory
	//*************************************************************************************************
	SUINT D3D11Driver::getDedicatedVideoMemory() const
	{
		return _adapterDescription.DedicatedVideoMemory;
	}

	//*************************************************************************************************
	// Get the shared system memory of this adapter
	// @return
	//	SUINT The shared system memory
	//*************************************************************************************************
	SUINT D3D11Driver::getSharedSystemMemory() const
	{
		return _adapterDescription.SharedSystemMemory;
	}

}	// Namespace