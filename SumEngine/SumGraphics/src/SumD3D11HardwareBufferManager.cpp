//*************************************************************************************************
// Title: SumD3D11HardwareBufferManager.cpp
// Author: Gael Huber
// Description: A D3D11-specific manager for all hardware buffers.
//*************************************************************************************************
#include "SumD3D11HardwareBufferManager.h"
#include "SumD3D11RenderSystem.h"
#include "SumD3D11VertexHardwareBuffer.h"

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

	//*************************************************************************************************
	// Create a vertex buffer
	// @param
	//	vertexSize The size of each vertex
	// @param
	//	numVertices The numer of vertices in the buffer
	// @param
	//	usage The buffer usage type
	//*************************************************************************************************
	VertexHardwareBuffer* D3D11HardwareBufferManager::createVertexBuffer(SUINT vertexSize, SUINT numVertices, HardwareBufferUsage usage)
	{
		// Initialize the hardware buffer
		VertexHardwareBuffer* buffer = new D3D11VertexHardwareBuffer(_device, vertexSize, numVertices, usage);

		// Assign the buffer an ID and bind to a map
		//bindBufferToMap(buffer);

		// Return the buffer
		return buffer;
	}

}	// Namespace