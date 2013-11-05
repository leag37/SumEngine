//*************************************************************************************************
// Title: SumD3D11RenderSystem.h
// Author: Gael Huber
// Description: D3D11 Render System wrapper
//*************************************************************************************************
#ifndef __SUMD3D11RENDERSYSTEM_H__
#define __SUMD3D11RENDERSYSTEM_H__

#include "SumRenderSystem.h"
#include "SumD3D11RenderWindow.h"
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

	protected:
		// Build the render system capabilities
		void _buildRenderSystemCapabilities();

	private:
		/** D3D Device
		*/
		D3D11Device _device;

	};

	/** @} */

}	// Namespace

#endif // __SUMD3D11RENDERSYSTEM_H__