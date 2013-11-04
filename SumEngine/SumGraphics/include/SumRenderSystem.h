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

namespace SumEngine
{
	/** \addtogroup Rendering
	*	@{
	*/

	class RenderSystem
	{
	public:
		RenderSystem();

		virtual void init() = 0;

		virtual void setLightingEnabled(SBOOL enabled) = 0;

		virtual RenderWindow* createRenderWindow(const String& name, SUINT width, SUINT height, SBOOL fullscreen) = 0;

		virtual void destroyRenderWindow(const String& name);

		//virtual void setWorldMatrix(const Matrix& m) = 0;
		//virtual void setViewMatrix(const Matrix& m) = 0;
		//virtual void setProjectionMatrix(const Matrix& m) = 0;
		//virtual void render();
		//const RenderSystemCapabilities* getCapabilities() const;
		
		// Shader program stuff

	protected:
	};

	/** @} */

}	// Namespace

#endif // __SUMRENDERSYSTEM_H__