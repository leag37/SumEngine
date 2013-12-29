//*************************************************************************************************
// Title: SumD3D11HardwareBufferManager.cpp
// Author: Gael Huber
// Description: A D3D11-specific manager for all hardware buffers.
//*************************************************************************************************
#include "SumD3D11HardwareBufferManager.h"
#include "SumD3D11RenderSystem.h"

namespace SumEngine
{
	//*************************************************************************************************
	// Constructor
	// @param
	//	renderSystem The render system currently in use
	//*************************************************************************************************
	D3D11HardwareBufferManager::D3D11HardwareBufferManager(const RenderSystem* renderSystem)
		:	HardwareBufferManager(renderSystem)
	{
		const D3D11RenderSystem* d3dRenderSystem = static_cast<const D3D11RenderSystem*>(renderSystem);
		_device = d3dRenderSystem->getD3D11Device();
	}

}	// Namespace