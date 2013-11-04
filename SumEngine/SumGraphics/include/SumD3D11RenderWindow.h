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

namespace SumEngine
{
	/**	\addtogroup Rendering
	*	@{
	*/

	class D3D11RenderWindow : public RenderWindow
	{
	public:
		/** Default constructor
		*/
		D3D11RenderWindow();

		/** Constructor
		*/
		D3D11RenderWindow(HINSTANCE instance, D3D11Device& device, IDXGIFactory1* dxgiFactory);

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

	private:
		/** Process instance
		*/
		HINSTANCE _hInstance;;

		/** Window handle
		*/
		HWND _handle;

		/** D3D11 Device
		*/
		D3D11Device& _device;

	};
	/** @} */

}	// Namespace

#endif // __SUMD3D11RENDERWINDOW_H__