//*************************************************************************************************
// Title: SumRenderWindow.h
// Author: Gael Huber
// Description: Maintains a physical window for the client to attach the render context.
//*************************************************************************************************
#ifndef __SUMD3D11RENDERWINDOW_H__
#define __SUMD3D11RENDERWINDOW_H__

#include "SumRenderCore.h"
#include "SumRenderWindow.h"
#include "SumD3D11Device.h"
#include "SumWindowEventHandler.h"

namespace SumEngine
{
	/**	\addtogroup Rendering
	*	@{
	*/

	/** Attributes for this render window
	*/
	enum D3D11RenderWindowAttribute
	{
		D3D11_RENDER_TARGET_VIEW = 0,
		D3D11_DEPTH_STENCIL_VIEW = 1
	};

	class D3D11RenderWindow : public RenderWindow
	{
	public:
		/** Default constructor
		*/
		D3D11RenderWindow();

		/** Constructor
		* @param
		*	hInstance The application instance
		* @param
		*	device The D3D11 Device used to create this window and the swap chain of the render target
		* @param
		*	dxgiFactory Used to create the swap chain for this window
		*/
		D3D11RenderWindow(HINSTANCE hInstance, D3D11Device& device, IDXGIFactory1* dxgiFactory);

		/** Destructor 
		*/
		~D3D11RenderWindow();

		/** Initializes the window
		* @param
		*	name The name of the window
		* @param
		*	width The width of the window resolution
		* @param
		*	height The window height
		* @param
		*	fullscreen The window will be created in fullscreen if true
		*/
		void create(const String& name, SUINT width, SUINT height, SBOOL fullscreen);

		/** Destroy the window
		*/
		void destroy();

		/** Change the window position
		* @param
		*	x The x position of the window's top-left corner
		* @param
		*	y The y position of the window's top-left corner
		*/
		void setPosition(SUINT x, SUINT y);

		/** Change the window's fullscreen parameter and adjust as necessary
		* @param
		*	fullscreen Set the window to fullscreen if true, windowed if false
		*/
		void setFullscreen(SBOOL fullscreen);

		/** Swap the buffers for the window
		*/
		void swapBuffers();

		/** Get an attribute of the render window
		* @param
		*	attribute A pointer to the desired class type
		* @param 
		*	data Pointer to the data being retrieved
		*/
		void getAttribute(SUINT attribute, void* data);

		/** Get the render target view
		* @return
		*	ID3D11RenderTargetView* The render target view associated with this window
		*/
		ID3D11RenderTargetView* getRenderTargetView();

		/** Get the depth stencil view
		* @return
		*	ID3D11DepthStencilView* The depth stencil view associated with this window
		*/
		ID3D11DepthStencilView* getDepthStencilView();

	private:
		/** Create the device swap chain
		*/
		void _createSwapChain();

	private:
		/** Process instance
		*/
		HINSTANCE _hInstance;;

		/** Window handle
		*/
		HWND _handle;

		/** D3D11 Device
		*/
		D3D11Device _device;

		/** DXGI Factory
		*/
		IDXGIFactory1* _dxgiFactory;

		/** Device swap chain
		*/
		IDXGISwapChain* _swapChain;

		/** Swap chain description
		*/
		DXGI_SWAP_CHAIN_DESC _swapChainDescription;

		/** Render target view for the swap chain
		*/
		ID3D11RenderTargetView* _renderTargetView;

		/** Depth stencil view for the swap chain
		*/
		ID3D11DepthStencilView* _depthStencilView;

		/** Back buffer for the swap chain
		*/
		ID3D11Texture2D* _backBuffer;
	};
	/** @} */

}	// Namespace

#endif // __SUMD3D11RENDERWINDOW_H__