//*************************************************************************************************
// Title: SumD3D11VertexHardwareBuffer.h
// Author: Gael Huber
// Description: D3D11 specific implementation of a vertex hardware buffer
//*************************************************************************************************
#ifndef __SUMD3D11VERTEXHARDWAREBUFFER_H__
#define __SUMD3D11VERTEXHARDWAREBUFFER_H__

#include "SumVertexHardwareBuffer.h"
#include "SumD3D11Device.h"

namespace SumEngine
{
	/** \addtogroup Rendering
	*	@{
	*/

	class D3D11VertexHardwareBuffer : public VertexHardwareBuffer
	{
	public:
		/** Constructor
		*/
		D3D11VertexHardwareBuffer();

		/** Constructor
		* @param
		*	device D3D11 device
		* @param
		*	numVertices The number of vertices in the buffer
		* @param
		*	vertexSize The size in bytes of each vertex
		*/
		D3D11VertexHardwareBuffer(const D3D11Device& device, SUINT numVertices, SUINT vertexSize);

		/** Destructor
		*/
		~D3D11VertexHardwareBuffer();

	protected:
		/** Implementation method to create the buffer
		*/
		void initBuffer();

	private:
		/** D3D11 Device
		*/
		D3D11Device _device;

		/** The vertex buffer
		*/
		ID3D11Buffer* _buffer;


	};

	/** @} */

}	// Namespace

#endif // __SUMD3D11VERTEXHARDWAREBUFFER_H__