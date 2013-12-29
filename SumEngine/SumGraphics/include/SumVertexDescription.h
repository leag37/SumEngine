//*************************************************************************************************
// Title: SumVertexDescription.h
// Author: Gael Huber
// Description: This class defines a vertex schema for any given buffer. Each description should
//	consist of multiple vertex properties that compose the vertex.
//*************************************************************************************************
#ifndef __SUMVERTEXDESCRIPTION_H__
#define __SUMVERTEXDESCRIPTION_H__

#include "SumVertexProperty.h"
#include "SumList.h"

namespace SumEngine
{
	/** \addtogroup Rendering
	*	@{
	*/

	class VertexDescription
	{
	public:


		/** Add a vertex property to this description
		* @param
		*	type The type of property
		* @param
		*	offset The offset of the property within the buffer
		* @param
		*	size The size of the property in bytes
		*/
		void addElement(VertexPropertyType type, SUINT offset, SUINT size);

	private:
		/** A list of the vertex properties
		*/
		List<VertexProperty> _vertexProperties;
	};

	/** @} */

}	// Namespace

#endif // __SUMVERTEXDESCRIPTION_H__