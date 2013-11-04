//*************************************************************************************************
// Title: SumRenderViewport.h
// Author: Gael Huber
// Description: Render viewport is the graphical viewport where rendering should happen. Each
//	viewport will be attached to a given window and will configure itself according to a given
//	context.
//
// TODO: Allow for on-the-fly reconfiguration of a viewport
//*************************************************************************************************
#ifndef __SUMRENDERVIEWPORT_H__
#define __SUMRENDERVIEWPORT_H__

#include "SumRenderContext.h"
#include "SumInclude.h"
#include "SumRenderWindow.h"

class RenderContext;

class RenderViewport
{
public:
	// Constructor
	RenderViewport();

	// Destructor
	~RenderViewport();

	// Configure the viewport
	void configure(const RenderContext* context, const SumEngine::RenderWindow* window);

	// Clear the viewports
	void clearViewport(const RenderContext* context);

private:
	// Clean the viewport
	void clean();

private:
	// The render target view
	ID3D11RenderTargetView* _renderTargetView;

	// Viewport
	D3D11_VIEWPORT _d3dViewport;

	// Depth stencil buffer
	ID3D11Texture2D* _depthStencilBuffer;

	// Depth stencil view
	ID3D11DepthStencilView* _depthStencilView;
};

#include "SumRenderViewport.inl"

#endif