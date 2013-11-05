//*************************************************************************************************
// Title: SumRenderSystemFactory.cpp
// Author: Gael Huber
// Description: Factory for render systems. The resultant rendering system is based on the value
//	within the config.
//*************************************************************************************************
#include "SumRenderSystemFactory.h"

namespace SumEngine
{
	//************************************************************************************************
	// Default constructor
	//************************************************************************************************
	RenderSystemFactory::RenderSystemFactory()
	{ }

	//************************************************************************************************
	// Destructor
	//************************************************************************************************
	RenderSystemFactory::~RenderSystemFactory()
	{ }

	//************************************************************************************************
	// Create a render system based on config features
	//************************************************************************************************
	RenderSystem* RenderSystemFactory::createRenderSystem()
	{
		// Fetch the config
		ConfigurationManager* configManager = ConfigurationManager::getSingletonPtr();
		Configuration* config = configManager->getConfiguration("Engine");
		String renderSystemType = config->retrieveValue("renderSystem");

		// Initialize the rendering system
		RenderSystem* renderSystem = 0;
		if(renderSystemType == "D3D11")
		{
			renderSystem = new D3D11RenderSystem();
		}
		
		// If we successfully constructed the render system, initialize it here
		if(renderSystem != 0)
		{
			renderSystem->init();
		}

		return renderSystem;
	}

}	// Namespace