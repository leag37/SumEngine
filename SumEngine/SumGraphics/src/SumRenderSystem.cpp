//*************************************************************************************************
// Title: SumRenderSystem.cpp
// Author: Gael Huber
// Description: Interface for encapsulating basic requirements of a rendering system. This will
//	manage API layer needed for rendering.
//*************************************************************************************************
#include "SumRenderSystem.h"

namespace SumEngine
{
	//*************************************************************************************************
	// Default constructor
	//*************************************************************************************************
	RenderSystem::RenderSystem()
	{
		// TODO
	}

	//*************************************************************************************************
	// Destructor
	//*************************************************************************************************
	RenderSystem::~RenderSystem()
	{
		// TODO
	}

	//*************************************************************************************************
	// Destroy the render window
	//*************************************************************************************************
	void RenderSystem::destroyRenderWindow(const String& name)
	{
		// TODO
	}

	//*************************************************************************************************
	// Return the render system type
	// @return
	//	RenderSystemType The specified API type we are using for this render system
	//*************************************************************************************************
	RenderSystemType RenderSystem::getRenderSystemType() const
	{
		return _renderSystemType;
	}

}	// Namespace