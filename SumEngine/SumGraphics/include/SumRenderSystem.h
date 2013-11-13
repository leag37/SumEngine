//*************************************************************************************************
// Title: SumRenderSystem.h
// Author: Gael Huber
// Description: Interface for encapsulating basic requirements of a rendering system. This will
//	manage API layer needed for rendering.
//*************************************************************************************************
#ifndef __SUMRENDERSYSTEM_H__
#define __SUMRENDERSYSTEM_H__

#include "SumRenderCore.h"
#include "SumRenderWindow.h"
#include "SumRenderSystemCapabilities.h"

namespace SumEngine
{
	/** \addtogroup Rendering
	*	@{
	*/

	/** Enum for render system types
	*/
	enum RenderSystemType
	{
		RENDER_SYSTEM_TYPE_D3D11 = 0,
		RENDER_SYSTEM_TYPE_D3D10,
		RENDER_SYSTEM_TYPE_OPENGL4,
		RENDER_SYSTEM_TYPE_OPENGL3
	};

	class RenderSystem
	{
	public:
		/** Default constructor
		*/
		RenderSystem();

		/** Destructor
		*/
		virtual ~RenderSystem();

		virtual void init() = 0;

		virtual void setLightingEnabled(SBOOL enabled) = 0;

		virtual RenderWindow* createRenderWindow(const String& name, SUINT width, SUINT height, SBOOL fullscreen) = 0;

		/** Destroy the render window
		*/
		virtual void destroyRenderWindow(const String& name);

		/** Clear buffers before rendering
		*/
		virtual void clearBuffers() = 0;

		//virtual void setWorldMatrix(const Matrix& m) = 0;
		//virtual void setViewMatrix(const Matrix& m) = 0;
		//virtual void setProjectionMatrix(const Matrix& m) = 0;
		//virtual void render();
		//const RenderSystemCapabilities* getCapabilities() const;

		/** Return the render system type
		* @return
		*	RenderSystemType The specified API type we are using for this render system
		*/
		RenderSystemType getRenderSystemType() const;
		
		// Shader program stuff

	protected:
		/** Build the render system capabilities
		*/
		virtual void _buildRenderSystemCapabilities() = 0;

		/** The render system capabilities
		*/
		RenderSystemCapabilities _renderSystemCapabilities;

		/** The active render window for the system
		*/
		RenderWindow* _renderWindow;

		/** The render system type
		*/
		RenderSystemType _renderSystemType;

	};

	/** @} */

}	// Namespace

#endif // __SUMRENDERSYSTEM_H__