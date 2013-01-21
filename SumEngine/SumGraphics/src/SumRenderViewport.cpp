//*************************************************************************************************
// Title: SumRenderViewport.cpp
// Author: Gael Huber
// Description: Render viewport is the graphical viewport where rendering should happen. Each
//	viewport will be attached to a given window and will configure itself according to a given
//	context.
//*************************************************************************************************
#include "SumRenderViewport.h"

//*************************************************************************************************
// Constructor
//*************************************************************************************************
RenderViewport::RenderViewport()
	:	_renderTargetView(0),
		_depthStencilBuffer(0),
		_depthStencilView(0)
{ }

//*************************************************************************************************
// Destructor
//*************************************************************************************************
RenderViewport::~RenderViewport()
{
	clean();
}

//*************************************************************************************************
// Configure the viewport
//*************************************************************************************************
void RenderViewport::configure(const RenderContext* context, const RenderWindow* window)
{
	// Clean the current configuration
	clean();

	// Size the swap chain and create the render target view
	HR(context->swapChain()->ResizeBuffers(
		1, 
		window->clientWidth(), 
		window->clientHeight(), 
		DXGI_FORMAT_R8G8B8A8_UNORM, 
		0));

	ID3D11Texture2D* backBuffer;
	HR(context->swapChain()->GetBuffer(
		0,
		__uuidof(ID3D11Texture2D),
		reinterpret_cast<void**>(&backBuffer)));
	HR(context->d3dDevice()->CreateRenderTargetView(backBuffer, 0, &_renderTargetView));
	ReleaseCOM(backBuffer);

	// Create the new depth/stencil buffer and view
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = window->clientWidth();
	depthStencilDesc.Height = window->clientHeight();
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	// Should we enable 4x Msaa in viewport
	if(context->msaaEnabled())
	{
		depthStencilDesc.SampleDesc.Count = 4;
		depthStencilDesc.SampleDesc.Quality = context->msaaQuality() - 1;
	}
	else
	{
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
	}

	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	HR(context->d3dDevice()->CreateTexture2D(&depthStencilDesc, 0, &_depthStencilBuffer));
	HR(context->d3dDevice()->CreateDepthStencilView(_depthStencilBuffer, 0, &_depthStencilView));

	// Bind the render target view and depth/stencil view to the pipeline
	context->d3dImmediateContext()->OMSetRenderTargets(1, &_renderTargetView, _depthStencilView);

	// Set viewport transform
	_d3dViewport.TopLeftX = 0;
	_d3dViewport.TopLeftY = 0;
	_d3dViewport.Width = static_cast<float>(window->clientWidth());
	_d3dViewport.Height = static_cast<float>(window->clientHeight());
	_d3dViewport.MinDepth = 0.0f;
	_d3dViewport.MaxDepth = 1.0f;

	context->d3dImmediateContext()->RSSetViewports(1, &_d3dViewport);
}

//*************************************************************************************************
// Clean the viewport
//*************************************************************************************************
void RenderViewport::clean()
{
	ReleaseCOM(_renderTargetView);
	ReleaseCOM(_depthStencilView);
	ReleaseCOM(_depthStencilBuffer);
}

