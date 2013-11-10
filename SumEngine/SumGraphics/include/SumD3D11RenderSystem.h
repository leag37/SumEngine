//*************************************************************************************************
// Title: SumD3D11RenderSystem.h
// Author: Gael Huber
// Description: D3D11 Render System wrapper
//*************************************************************************************************
#ifndef __SUMD3D11RENDERSYSTEM_H__
#define __SUMD3D11RENDERSYSTEM_H__

#include "SumArray.h"
#include "SumRenderSystem.h"
#include "SumD3D11RenderWindow.h"
#include "SumD3D11Driver.h"
#include "SumRenderCore.h"

namespace SumEngine
{
	/** \addtogroup Rendering
	*	@{
	*/

	class D3D11RenderSystem : public RenderSystem
	{
	public:
		/** Default constructor */
		D3D11RenderSystem();

		/** Destructor */
		~D3D11RenderSystem();

		/** Initialize the rendering system */
		void init();

		/** Set the lighting status of the rendering system
		*/
		void setLightingEnabled(SBOOL enabled);

		/**
		* Create a render window.
		* @param
		*	name The name of the window (this name must be unique as the window is mapped to a dictionary)
		* @param
		*	width The window's outer width (inner width will be slightly smaller due to borders)
		* @param
		*	height The window's outer height (inner height wil be slightly smaller due to borders)
		* @param
		*	fullscreen Should the window be created in fullscreen
		* @return
		*	RenderWindow The render window created for the engine
		*/
		RenderWindow* createRenderWindow(const String& name, SUINT width, SUINT height, SBOOL fullscreen);

		/** Clear buffers before rendering
		*/
		void clearBuffers();

	protected:
		/** Build the render system capabilities
		*/
		void _buildRenderSystemCapabilities();

	private:
		/** Create the DXGI factory instance
		*/
		void _createDXGIFactory();

		/** Create the device or detect the best option if there are no config settings
		*/
		void _createD3D11Device();

		/** Create the list of valid drivers for this system
		*/
		void _buildD3D11DriverList();

		/** Choose the most appropriate D3D11 Driver
		*/
		void _chooseD3D11Driver();

	private:
		/** Keep track of the application instance
		*/
		HINSTANCE _hInstance;

		/** List of available D3D Drivers
		*/
		Array<D3D11Driver*> _drivers;
		
		/** D3D Device
		*/
		D3D11Device _device;

		/** DXGI Factory instance for detecting available devices and choosing best option
		*/
		IDXGIFactory1* _dxgiFactory;

		/** The active D3D11 driver
		*/
		D3D11Driver* _activeDriver;

		/** Active render window
		*/
		D3D11RenderWindow* _activeRenderWindow;
	};

	/** @} */

}	// Namespace

#endif // __SUMD3D11RENDERSYSTEM_H__