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
		*	vertexSize The size in bytes of each vertex
		* @param
		*	numVertices The number of vertices in the buffer
		* @param
		*	usage The usage of the hardware buffer
		*/
		D3D11VertexHardwareBuffer(const D3D11Device& device, SUINT vertexSize, SUINT numVertices, HardwareBufferUsage usage);

		/** Destructor
		*/
		~D3D11VertexHardwareBuffer();

		/** Copy contents of this buffer to another buffer.
		* @param
		*	destBuffer The destination buffer
		*/
		void copyToBuffer(HardwareBuffer* destBuffer);

		/** Copy contents of the source buffer to this buffer.
		* @param
		*	srcBuffer The source buffer
		*/
		void copyFromBuffer(HardwareBuffer* srcBuffer);

		/** Lock the buffer to permit access to the data
		* @return
		*	void* Pointer to the locked data in memory
		*/
		void* lock();

		/** Unlock the locked data
		*/
		void unlock();

		/** Return a pointer to the buffer
		* @return
		*	ID3D11Buffer* A pointer to the buffer
		*/
		ID3D11Buffer* getID3D11Buffer() const;

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