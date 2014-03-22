//*************************************************************************************************
// Title: SumVertexDescription.cpp
// Author: Gael Huber
// Description: This class defines a vertex schema for any given buffer. Each description should
//	consist of multiple vertex properties that compose the vertex.
//*************************************************************************************************
#include "SumVertexDescription.h"

namespace SumEngine
{
	//*************************************************************************************************
	// Constructor
	//*************************************************************************************************
	VertexDescription::VertexDescription()
		:	_size(0)
	{ }

	//*************************************************************************************************
	// Add a vertex property to this description
	// @param
	//	type The type of property
	// @param
	//	offset The offset of the property within the buffer
	// @param
	//	size The size of the property in bytes
	//
	void VertexDescription::addElement(VertexPropertyType type, SUINT offset)
	{
		_vertexProperties.push_back(VertexProperty(type, offset));
		_size += VertexProperty::GetSizeForType(type);
	}

}	// Namespace