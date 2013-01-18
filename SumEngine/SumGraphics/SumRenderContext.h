//*************************************************************************************************
// Title: SumRenderContext.h
// Author: Gael Huber
// Description: Provides a render context for the application. This includes information about 
//	the current instance of DirectX and driver information.
//
// TODO: Expand to support multiple feature levels
// TODO: Expand to support loading in a configuration
// TODO: Add support for debug mode
//*************************************************************************************************
#ifndef __SUMRENDERCONTEXT_H__
#define __SUMRENDERCONTEXT_H__

#include "SumInclude.h"
#include <D3DX11.h>
#include <DxErr.h>

class RenderContext
{
public:
	// Constructor 
	RenderContext(HWND clientWindow, SUINT clientWidth, SUINT clientHeight);

	// Destructor
	~RenderContext();

private:
	// Create the device
	SBOOL createDevice();

	// Check for multisampling
	SBOOL checkMultisampling();

	// Create the swap chain for the device
	SBOOL createSwapChain(HWND clientWindow, SUINT clientWidth, SUINT clientHeight);

private:
	// Application instance
	HINSTANCE _hAppInstance;

	// D3D device
	ID3D11Device* _d3dDevice;

	// Driver type
	D3D_DRIVER_TYPE _d3dDriverType;

	// Immediate context
	ID3D11DeviceContext* _d3dImmediateContext;

	// Swap chain used for rendering
	IDXGISwapChain* _swapChain;

	// Multisampling quality
	SUINT _4xMsaaQuality;
	
// INLINE FUNCTIONS
public:
	// Get the swap chain
	SUMINLINE IDXGISwapChain* swapChain()
	{
		return _swapChain;
	}
};

#define ReleaseCOM { if(x) x->Release(); x = 0; }


#endif