//*************************************************************************************************
// Title: SumMeshSerializer.h
// Author: Gael Huber
// Description: A serializer for meshes. This is responsible for loading and correctly reading in
//	mesh data from file.
//*************************************************************************************************
#ifndef __SUMMESHSERIALIZER_H__
#define __SUMMESHSERIALIZER_H__

#include "SumHardwareBuffer.h"
#include "SumFileStream.h"

namespace SumEngine
{
	/** \addtogroup Rendering
	*	@{
	*/

	class MeshSerializer
	{
	public:
		/** Constructor
		* @param
		*	stream The data stream for the mesh
		* @param
		*	vbUsage The usage of the vertex buffer
		* @param
		*	ibUsage The usage of the index buffer
		*/
		MeshSerializer(FileStreamPtr stream);

		/** Destructor
		*/
		~MeshSerializer();

		/** Read the mesh header data
		*/


	private:
	};

	/** @} */

}	// Namespace

#endif // __SUMMESHSERIALIZER_H__