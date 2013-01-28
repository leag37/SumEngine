//*************************************************************************************************
// Title: SumRenderViewport.h
// Author: Gael Huber
// Description: Render viewport is the graphical viewport where rendering should happen. Each
//	viewport will be attached to a given window and will configure itself according to a given
//	context.
//*************************************************************************************************

//*************************************************************************************************
// Clear the viewports
//*************************************************************************************************
SUMINLINE void RenderViewport::clearViewport(const RenderContext* context)
{
	// Clear the render target
	context->d3dImmediateContext()->ClearRenderTargetView(_renderTargetView, Color::Black.f);
	
	// Clear the depth stencil
	context->d3dImmediateContext()->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}
