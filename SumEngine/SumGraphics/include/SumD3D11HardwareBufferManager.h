//*************************************************************************************************
// Title: SumD3D11HardwareBufferManager.h
// Author: Gael Huber
// Description: A D3D11-specific manager for all hardware buffers.
//*************************************************************************************************
#ifndef __SUMD3D11HARDWAREBUFFERMANAGER_H__
#define __SUMD3D11HARDWAREBUFFERMANAGER_H__

#include "SumHardwareBufferManager.h"
#include "SumD3D11Device.h"

namespace SumEngine
{
	/** \addtogroup Rendering
	*	@{
	*/

	class D3D11HardwareBufferManager : public HardwareBufferManager
	{
	public:
		/** Constructor
		* @param
		*	renderSystem The render system currently in use
		*/
		D3D11HardwareBufferManager(const RenderSystem* renderSystem);

		/** Create a vertex buffer
		* @param
		*	vertexSize The size of each vertex
		* @param
		*	numVertices The numer of vertices in the buffer
		* @param
		*	usage The buffer usage type
		*/
		VertexHardwareBuffer* createVertexBuffer(SUINT vertexSize, SUINT numVertices, HardwareBufferUsage usage);

	private:
		/** The D3D11Device
		*/
		D3D11Device _device;
	};

	/** @} */

}	// Namespace

#endif // __SUMD3D11HARDWAREBUFFERMANAGER_H__