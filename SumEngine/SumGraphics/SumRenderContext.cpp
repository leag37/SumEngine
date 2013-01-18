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

}

//*************************************************************************************************
// Create the device
//*************************************************************************************************
SBOOL RenderContext::createDevice()
{
	// Set the desired feature level
	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

	// Create the device
	HRESULT hr = D3D11CreateDevice(
		0,	// Default adapter
		_d3dDriverType,
		0,
		0,	// ONLY support non-debug mode right now
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
SBOOL createSwapChain(HWND clientWindow, SUINT clientWidth, SUINT clientHeight)
{

	return true;
}
