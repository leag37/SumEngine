//*************************************************************************************************
// Title: SumVertexHardwareBuffer.h
// Author: Gael Huber
// Description: Defines the basis of a vertex hardware buffer
//*************************************************************************************************
#ifndef __SUMVERTEXHARDWAREBUFFER_H__
#define __SUMVERTEXHARDWAREBUFFER_H__

#include "SumHardwareBuffer.h"
#include "SumSharedPtr.h"

namespace SumEngine
{
	/** \addtogroup Rendering
	*	@{
	*/

	class VertexHardwareBuffer : public HardwareBuffer
	{
	public:
		/** Constructor
		*/
		VertexHardwareBuffer();

		/** Constructor
		* @param
		*	numVertices The number of vertices in the buffer
		* @param
		*	vertexSize The size in bytes of each vertex
		* @param
		*	usage The usage type for this hardware buffer
		*/
		VertexHardwareBuffer(SUINT numVertices, SUINT vertexSize, HardwareBufferUsage usage);

		/** Destructor
		*/
		~VertexHardwareBuffer();

		/** The number of vertices in the buffer
		* @return
		*	SUINT The number of vertices
		*/
		SUINT getNumVertices() const;

		/** The size of each vertex in bytes
		* @return
		*	SUINT The size of each vertex in bytes
		*/
		SUINT getVertexSize() const;

	protected:
		/** The number of vertices
		*/
		SUINT _numVertices;

		/** The vertex size
		*/
		SUINT _vertexSize;
	};

	/** Shared pointer for vertex hardware buffers
	*/
	class VertexHardwareBufferPtr : public SharedPtr<VertexHardwareBuffer>
	{
	public:
		/** Constructor
		* @param
		*	vhb The vertex hardware buffer
		*/
		VertexHardwareBufferPtr(VertexHardwareBuffer* vhb);

		/** Destructor
		*/
		~VertexHardwareBufferPtr();
	};

	/** @} */

}	// Namespace

#endif // __SUMVERTEXHARDWAREBUFFER_H__