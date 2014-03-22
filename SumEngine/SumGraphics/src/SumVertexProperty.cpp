//*************************************************************************************************
// Title: SumVertexProperty.cpp
// Author: Gael Huber
// Description: Describes a single vertex property for a single element for a given definition.
//*************************************************************************************************
#include "SumVertexProperty.h"

namespace SumEngine
{
	//*************************************************************************************************
	// Constructor
	//*************************************************************************************************
	VertexProperty::VertexProperty()
		:	_type(VPT_UNKNOWN), _offset(0), _size(0)
	{ }

	//*************************************************************************************************
	// Constructor
	// @param
	//	type The type of vertex property
	// @param
	//	offset The offset in bytes within the vertex element
	//*************************************************************************************************
	VertexProperty::VertexProperty(VertexPropertyType type, SUINT offset)
		:	_type(type),
			_offset(offset),
			_size(GetSizeForType(type))
	{ }

	//*************************************************************************************************
	// Given a property type, get the appropriate element size
	// @param
	//	type The property type
	// @return
	//	SUINT The size in bytes
	//*************************************************************************************************
	SUINT VertexProperty::GetSizeForType(VertexPropertyType type)
	{
		switch(type)
		{
		case VPT_FLOAT1:
		case VPT_INT1:
			return 4;

		case VPT_FLOAT2:
			return 8;

		case VPT_FLOAT3:
			return 12;

		case VPT_FLOAT4:
			return 16;

		case VPT_UNKNOWN:
		default:
			return 0;
		}

		return 0;
	}

} // Namespace