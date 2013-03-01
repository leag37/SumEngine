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
		_d3dDriverType(D3D_DRIVER_TYPE_HARDWARE),
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
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// Set the desired feature level
	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

	// Create the device
	HRESULT hr = D3D11CreateDevice(
		0,	// Default adapter
		_d3dDriverType,
		0,
		createDeviceFlags,	// Support debug mode
		0, 0,	// Default feature level array
		D3D11_SDK_VERSION,
		&_d3dDevice,
		&featureLevel,
		&_d3dImmediateContext
		);
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
