//*************************************************************************************************
// Title: SumHardwareBufferManager.cpp
// Author: Gael Huber
// Description: A manager for creating and tracking hardware buffers.
//*************************************************************************************************
#include "SumHardwareBufferManager.h"
#include "SumRenderSystem.h"

template<> SumEngine::HardwareBufferManager* Singleton<SumEngine::HardwareBufferManager>::singleton = 0;

namespace SumEngine
{
	//*************************************************************************************************
	// Default constructor
	//*************************************************************************************************
	HardwareBufferManager::HardwareBufferManager()
		:	_nextBufferId(0)
	{ }

	//*************************************************************************************************
	// Constructor based on render system
	// @param
	//	renderSystem The render system currently in use
	//*************************************************************************************************
	HardwareBufferManager::HardwareBufferManager(const RenderSystem* renderSystem)
		:	_nextBufferId(0)
	{ }
	

}	// Namespace