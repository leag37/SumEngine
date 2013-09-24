//*************************************************************************************************
// Title: SumRenderContext.cpp
// Author: Gael Huber
// Description: Provides a render context for the application. This includes information about 
//	the current instance of DirectX and driver information.
//*************************************************************************************************
#include "SumRenderContext.h"

//*************************************************************************************************
// Constructor
//*************************************************************************************************
RenderContext::RenderContext(HWND clientWindow, SUINT clientWidth, SUINT clientHeight)
	:	_d3dDevice(0),
		_swapChain(0),
		_d3dImmediateContext(0),
		_d3dDriverType(D3D_DRIVER_TYPE_UNKNOWN),
		_4xMsaaEnabled(false)
{
	// Initialize the render context
	SBOOL success = false;

	// Create the Direct3D device
	success = createDevice();

	// Check for multisampling
	if(success == true)
	{
		success = checkMultisampling();
	}

	// Create the swap chain for the device
	if(success == true)
	{
		success = createSwapChain(clientWindow, clientWidth, clientHeight);
	}
}

//*************************************************************************************************
// Destructor
//*************************************************************************************************
RenderContext::~RenderContext()
{
	ReleaseCOM(_swapChain);

	if(_d3dImmediateContext)
	{
		_d3dImmediateContext->ClearState();
	}

	ReleaseCOM(_d3dImmediateContext);
	ReleaseCOM(_d3dDevice);
}

//*************************************************************************************************
// Create the device
//*************************************************************************************************
SBOOL RenderContext::createDevice()
{
	// Create the device and device context
	UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
	//createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	HRESULT hr = S_OK;

	// Set the desired feature level
	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL targetLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};
	SUINT numFeatureLevels = 1;

	// Create a device factory so that we can find a DX11 compatible device
	IDXGIFactory* factory = 0;
	IDXGIAdapter* adapter = 0;
	hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&factory));
	if(FAILED(hr))
	{
		MessageBox(0, "Failed to create IDXGIFactory.", 0, 0);
		return false;
	}

	// Get selected device if it is part of the config
	Configuration* config = ConfigurationManager::getSingletonPtr()->getConfiguration("Engine");
	String configAdapter = config->retrieveValue("adapter");

	// Iterate through adapters to find a compatible one
	DXGI_ADAPTER_DESC adapterDesc;
	for(SINT i = 0; factory->EnumAdapters(i, &adapter) != DXGI_ERROR_NOT_FOUND; ++i)
	{
		// Get the adapter description
		adapter->GetDesc(&adapterDesc);

		// See whether this adapter matches the one we selected
		if(configAdapter == adapterDesc.Description)
		{
			// Use this adapter
			break;
		}
		
	}

	if(adapter)
	{
		// Create the device using the specified adapter
		_d3dDriverType = D3D_DRIVER_TYPE_UNKNOWN;
		hr = D3D11CreateDevice(
			adapter,	// Selected adapter
			_d3dDriverType,
			0,
			createDeviceFlags,	// Support debug mode
			targetLevels,		// Target feature levels
			numFeatureLevels,	// Number of supported feature levels
			D3D11_SDK_VERSION,
			&_d3dDevice,
			&featureLevel,
			&_d3dImmediateContext
			);
	}
	else
	{
		_d3dDriverType = D3D_DRIVER_TYPE_HARDWARE;
		hr = D3D11CreateDevice(
			0,
			_d3dDriverType,
			0,
			createDeviceFlags,
			targetLevels,
			numFeatureLevels,
			D3D11_SDK_VERSION,
			&_d3dDevice,
			&featureLevel,
			&_d3dImmediateContext
			);
	}
	if(FAILED(hr))
	{
		MessageBox(0, "D3DCreateDevice Failed", 0, 0);
		return false;
	}

	// Check for DX11 support
	if(featureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		MessageBox(0, "DirectX 11 is not supported on this device", 0, 0);
		return false;
	}

	// Creation of device succeeded
	return true;
}

//*************************************************************************************************
// Check for multisampling
//*************************************************************************************************
SBOOL RenderContext::checkMultisampling()
{
	// Check for 4x Msaa
	_d3dDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &_4xMsaaQuality);
	assert(_4xMsaaQuality > 0);

	Configuration* config = ConfigurationManager::getSingletonPtr()->getConfiguration("Engine");
	String configMsaa = config->retrieveValue("4xMsaa");

	if(configMsaa == "enabled")
	{
		_4xMsaaEnabled = true;
	}
	else
	{
		_4xMsaaEnabled = false;
	}

	// Multisampling checked successfully
	return true;
}

//*************************************************************************************************
// Create the swap chain for the device
//*************************************************************************************************
SBOOL RenderContext::createSwapChain(HWND clientWindow, SUINT clientWidth, SUINT clientHeight)
{
	// Fill out DXGI swap chain description
	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width = clientWidth;
	sd.BufferDesc.Height = clientHeight;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// Use 4x Msaa
	if(_4xMsaaEnabled)
	{
		sd.SampleDesc.Count = 4;
		sd.SampleDesc.Quality = _4xMsaaQuality - 1;
	}

	// No Msaa
	else
	{
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
	}

	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = clientWindow;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	// Generate an IDXGI factory to properly initialize the swap chain
	IDXGIDevice* dxgiDevice = 0;
	HR(_d3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice));

	IDXGIAdapter* dxgiAdapter = 0;
	HR(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter));

	IDXGIFactory* dxgiFactory = 0;
	HR(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory));

	HR(dxgiFactory->CreateSwapChain(_d3dDevice, &sd, &_swapChain));

	ReleaseCOM(dxgiDevice);
	ReleaseCOM(dxgiAdapter);
	ReleaseCOM(dxgiFactory);	

	return true;
}
