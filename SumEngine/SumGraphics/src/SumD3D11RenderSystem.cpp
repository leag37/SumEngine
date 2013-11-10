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
		:	_device(0),
			_dxgiFactory(0),
			_activeDriver(0),
			_activeRenderWindow(0)
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

		// Get the application instance handle
		_hInstance = GetModuleHandle(NULL);
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
		
		// Pick a driver
		_chooseD3D11Driver();

		// Device flags
		SUINT deviceFlags = 0;

		// Build target level list
		D3D_FEATURE_LEVEL targetFeatureLevels[] = 
		{
			D3D_FEATURE_LEVEL_11_0
		};
		SUINT numFeatureLevels = sizeof(targetFeatureLevels) / sizeof(D3D_FEATURE_LEVEL);

		// Create the driver from the driver
		ID3D11Device* device = 0;
		HRESULT result = D3D11CreateDevice(
			_activeDriver->getAdapter(),
			D3D_DRIVER_TYPE_UNKNOWN,
			0,
			deviceFlags,
			targetFeatureLevels,
			numFeatureLevels,
			D3D11_SDK_VERSION,
			&device,
			0,
			0
			);

		if(FAILED(result))
		{
			MessageBox(0, "D3DCreateDevice failed", 0, 0);
		}

		if(device->GetFeatureLevel() != D3D_FEATURE_LEVEL_11_0)
		{
			MessageBox(0, "DirectX 11 is not supported on this device", 0, 0);
		}

		// Initialize the device
		_device = D3D11Device(device);
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
	// Choose the most appropriate D3D11 Driver
	//*************************************************************************************************
	void D3D11RenderSystem::_chooseD3D11Driver()
	{
		// Driver to choose
		D3D11Driver* chosenDriver = 0;

		Array<D3D11Driver*>::Iterator end = _drivers.end();
		for(Array<D3D11Driver*>::Iterator itr = _drivers.begin(); itr != end; ++itr)
		{
			D3D11Driver* currDriver = (*itr);
			
			// Choose this driver is none have been chosen yet
			if(chosenDriver == 0)
			{
				chosenDriver = currDriver;
			}
			// Otherwise, compare system capabilities
			else
			{
				// Compare dedicated and shared memory profiles to determine which device should be chosen
				// TODO
			}
		}

		// Assign the current driver as the chosen one
		_activeDriver = chosenDriver;
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
		// Initialize a window
		D3D11RenderWindow* renderWindow = new D3D11RenderWindow(_hInstance, _device, _dxgiFactory);
		renderWindow->create(name, width, height, fullscreen);
		
		// Set as active window
		_activeRenderWindow = renderWindow;
		
		// Return the value
		return renderWindow;
	}

	//*************************************************************************************************
	// Clear buffers before rendering
	//*************************************************************************************************
	void D3D11RenderSystem::clearBuffers()
	{
		// Get the custom attributes from the render window
		ID3D11RenderTargetView* rtv;
		ID3D11DepthStencilView* dsv;
		
		_activeRenderWindow->getAttribute(D3D11_RENDER_TARGET_VIEW, &rtv);
		_activeRenderWindow->getAttribute(D3D11_DEPTH_STENCIL_VIEW, &dsv);
		
		// Clear buffers
		_device.getImmediateContext()->ClearRenderTargetView(rtv, Color::Black.f);
		_device.getImmediateContext()->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}

}	// Namespace