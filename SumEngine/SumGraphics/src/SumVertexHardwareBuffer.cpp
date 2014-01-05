//*************************************************************************************************
// Title: SumVertexHardwareBuffer.cpp
// Author: Gael Huber
// Description: Defines the basis of a vertex hardware buffer
//*************************************************************************************************
#include "SumVertexHardwareBuffer.h"

namespace SumEngine
{
	//*************************************************************************************************
	// Constructor
	//*************************************************************************************************
	VertexHardwareBuffer::VertexHardwareBuffer()
		:	HardwareBuffer()
	{ }

	//*************************************************************************************************
	// Constructor
	// @param
	//	numVertices The number of vertices in the buffer
	// @param
	//	vertexSize The size in bytes of each vertex
	//*************************************************************************************************
	VertexHardwareBuffer::VertexHardwareBuffer(SUINT numVertices, SUINT vertexSize, HardwareBufferUsage usage)
		:	HardwareBuffer(usage),
			_numVertices(numVertices),
			_vertexSize(vertexSize)
	{ }

	//*************************************************************************************************
	// Destructor
	//*************************************************************************************************
	VertexHardwareBuffer::~VertexHardwareBuffer()
	{
		// Todo
	}

	//*************************************************************************************************
	// The number of vertices in the buffer
	// @return
	//	SUINT The number of vertices
	//*************************************************************************************************
	SUINT VertexHardwareBuffer::getNumVertices() const
	{
		return _numVertices;
	}

	//*************************************************************************************************
	// The size of each vertex in bytes
	// @return
	//	SUINT The size of each vertex in bytes
	//*************************************************************************************************
	SUINT VertexHardwareBuffer::getVertexSize() const
	{
		return _vertexSize;
	}

}	// Namespace