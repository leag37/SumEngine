//*************************************************************************************************
// Title: SumRenderSystemFactory.h
// Author: Gael Huber
// Description: Factory for render systems. The resultant rendering system is based on the value
//	within the config.
//*************************************************************************************************
#ifndef __SUMRENDERSYSTEMFACTORY_H__
#define __SUMRENDERSYSTEMFACTORY_H__

#include "SumRenderSystem.h"
#include "SumD3D11RenderSystem.h"
#include "SumConfigurationManager.h"

namespace SumEngine
{
	/**	\addtogroup Rendering
	*	@{
	*/

	class RenderSystemFactory
	{
	public:
		/** Default constructor
		*/
		RenderSystemFactory();

		/** Destructor
		*/
		~RenderSystemFactory();

		/** Create a render system based on config features
		*/
		RenderSystem* createRenderSystem();
	};

	/** @} */

}	// Namespace

#endif // __SUMRENDERSYSTEMFACTORY_H__