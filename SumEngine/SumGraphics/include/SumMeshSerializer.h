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
#include "SumMesh.h"

namespace SumEngine
{
	/** \addtogroup Rendering
	*	@{
	*/

	enum MeshFileType
	{
		MFT_BINARY = 0,
		MFT_PLAIN_TEXT,
		MFT_UNKNOWN
	};

	class Mesh::MeshSerializer
	{
	public:
		/** Constructor
		* @param
		*	stream The data stream for the mesh
		* @param
		*	mesh Pointer to the mesh being serialized
		*/
		MeshSerializer(FileStreamPtr stream, Mesh* mesh);

		/** Destructor
		*/
		~MeshSerializer();

		/** Read the mesh
		*/
		void read();

	private:
		/** Read the file type of the mesh
		*/
		void readFileType();

		/** Read the file from a binary file structure
		*/
		void bRead();

		/** Read the file from a plain text file structure
		*/
		void ptRead();

		/** Read the header
		*/
		void ptReadHeader();

		/** Read the body data
		*/
		void ptReadBody();

	private:
		/** Pointer to the mesh being serialized
		*/
		Mesh* _mesh;

		/** Relevant filestream for this mesh
		*/
		FileStreamPtr _stream;

		/** File type
		*/
		MeshFileType _fileType;
	};

	/** @} */

}	// Namespace

#endif // __SUMMESHSERIALIZER_H__