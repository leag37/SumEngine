//*************************************************************************************************
// Title: SumVertexProperty.h
// Author: Gael Huber
// Description: Describes a single vertex property for a single element for a given definition.
//*************************************************************************************************
#ifndef __SUMVERTEXPROPERTY_H__
#define __SUMVERTEXPROPERTY_H__

#include "SumInclude.h"

namespace SumEngine
{
	/** \addtogroup Rendering
	*	@{
	*/

	/** Enumeration describing the different types of vertex properties
	*/
	enum VertexPropertyType
	{
		VPT_FLOAT1 = 0,
		VPT_FLOAT2,
		VPT_FLOAT3,
		VPT_FLOAT4,
		VPT_INT1,
		VPT_UINT1,
		VPT_CHAR1,
		VPT_UCHAR1,
		VPT_SHORT1,
		VPT_USHORT1,
		VPT_UNKNOWN
	};

	class VertexProperty
	{
	public:
		/** Constructor
		*/
		VertexProperty();

		/** Constructor
		* @param
		*	type The type of vertex property
		* @param
		*	offset The offset in bytes within the vertex element
		*/
		VertexProperty(VertexPropertyType type, SUINT offset);

		/** Given a property type, get the appropriate element size
		* @param
		*	type The property type
		* @return
		*	SUINT The size in bytes
		*/
		static SUINT GetSizeForType(VertexPropertyType type);

	private:
		/** The vertex property type
		*/
		VertexPropertyType _type;

		/** The element offset within the vertex declaration
		*/
		SUINT _offset;

		/** The size of this element
		*/
		SUINT _size;
	};

	/** @} */

}	// Namespace

#endif // __SUMVERTEXPROPERTY_H__