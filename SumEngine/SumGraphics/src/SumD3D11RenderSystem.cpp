//*************************************************************************************************
// Title: SumD3D11RenderSystem.cpp
// Author: Gael Huber
// Description: D3D11 Render System wrapper
//*************************************************************************************************
#include "SumD3D11RenderSystem.h"

namespace SumEngine
{
	//*************************************************************************************************
	// Default constructor 
	//*************************************************************************************************
	D3D11RenderSystem::D3D11RenderSystem()
		:	_device(0)
	{ }

	//*************************************************************************************************
	// Destructor 
	//*************************************************************************************************
	D3D11RenderSystem::~D3D11RenderSystem()
	{
		// TODO
	}

	//*************************************************************************************************
	// Initialize the rendering system 
	//*************************************************************************************************
	void D3D11RenderSystem::init()
	{
		// Create the DXGI device factory
		_createDXGIFactory();

		// Create the device and scan hardware
		_createD3D11Device();

		//
	}

	//*************************************************************************************************
	// Build the render system capabilities
	//*************************************************************************************************
	void D3D11RenderSystem::_buildRenderSystemCapabilities()
	{
	}

	//*************************************************************************************************
	// Create the DXGI factory instance
	//*************************************************************************************************
	void D3D11RenderSystem::_createDXGIFactory()
	{
		// Initialize the factory
		HRESULT result = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&_dxgiFactory));
	}

	//*************************************************************************************************
	// Create the device or detect the best option if there are no config settings
	//*************************************************************************************************
	void D3D11RenderSystem::_createD3D11Device()
	{
		// Build the list of available drivers
		_buildD3D11DriverList();
		

	}

	//************************************************************************************************
	// Create the list of valid drivers for this system
	//************************************************************************************************
	void D3D11RenderSystem::_buildD3D11DriverList()
	{
		// Iterate through the adapters and create a list of adapter settings
		for(SUINT i = 0; ; ++i)
		{
			IDXGIAdapter1* adapter = 0;
			DXGI_ADAPTER_DESC1 adapterDesc;
		
			// Get the adapter
			HRESULT result = _dxgiFactory->EnumAdapters1(i, &adapter);

			// If no adapter found, exit
			if(result == DXGI_ERROR_NOT_FOUND)
			{
				break;
			}

			// If the adapter failed to get fetched, delete it
			else if(result != S_OK)
			{
				delete adapter;
			}
			
			// Add the adapter to the list
			_drivers.push_back(new D3D11Driver(adapter));
		}
	}

	//*************************************************************************************************
	// Set the lighting status of the rendering system
	//*************************************************************************************************
	void D3D11RenderSystem::setLightingEnabled(SBOOL enabled)
	{
		// TODO
	}

	//*************************************************************************************************
	// Create a render window.
	// @param
	//	name The name of the window (this name must be unique as the window is mapped to a dictionary)
	// @param
	//	width The window's outer width (inner width will be slightly smaller due to borders)
	// @param
	//	height The window's outer height (inner height wil be slightly smaller due to borders)
	// @param
	//	fullscreen Should the window be created in fullscreen
	// @return
	//	RenderWindow The render window created for the engine
	//*************************************************************************************************
	RenderWindow* D3D11RenderSystem::createRenderWindow(const String& name, SUINT width, SUINT height, SBOOL fullscreen)
	{
		// TODO
		return 0;
	}

}	// Namespace