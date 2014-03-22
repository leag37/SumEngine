//*************************************************************************************************
// Title: SumMeshSerializer.cpp
// Author: Gael Huber
// Description: A serializer for meshes. This is responsible for loading and correctly reading in
//	mesh data from file.
//*************************************************************************************************
#include "SumMeshSerializer.h"

namespace SumEngine
{
	//*************************************************************************************************
	// Constructor
	// @param
	//	stream The data stream for the mesh
	// @param
	//	mesh Pointer to the mesh being serialized
	//*************************************************************************************************
	Mesh::MeshSerializer::MeshSerializer(FileStreamPtr stream, Mesh* mesh)
		:	_stream(stream), _mesh(mesh)
	{ }

	//*************************************************************************************************
	// Destructor
	//*************************************************************************************************
	Mesh::MeshSerializer::~MeshSerializer()
	{ }

	//*************************************************************************************************
	// Read the mesh
	//*************************************************************************************************
	void Mesh::MeshSerializer::read()
	{
		// First read the file type from the stream
		readFileType();

		if(_fileType == MFT_BINARY)
		{
			bRead();
		}
		else if(_fileType == MFT_PLAIN_TEXT)
		{
			ptRead();
		}
	}

	//*************************************************************************************************
	// Read the file type of the mesh
	//*************************************************************************************************
	void Mesh::MeshSerializer::readFileType()
	{
		// Ensure the file pointer is still good
		if(_stream->isEOF() == false)
		{
			// Read the first line
			String line = String(1);
			_stream->read(line, 1);
			
			// If the first line is 0, it is binary 
			if(line[0] == 0) 
			{
				_fileType = MFT_BINARY;
			}
			// Otherwise, if it's one the file is plain text
			else if(line[0] == 1)
			{
				_fileType = MFT_PLAIN_TEXT;
			}
			// Unknown, this should throw an error
			else
			{
				_fileType = MFT_UNKNOWN;
			}
		}
	}

	//*************************************************************************************************
	// Read the file from a binary file structure
	//*************************************************************************************************
	void Mesh::MeshSerializer::bRead()
	{

	}

	//*************************************************************************************************
	// Read the file from a plain text file structure
	//*************************************************************************************************
	void Mesh::MeshSerializer::ptRead()
	{
		// Read the header
		ptReadHeader();

		// Read body data
		//ptReadBody();
	}

	//*************************************************************************************************
	// Read the header
	//*************************************************************************************************
	void Mesh::MeshSerializer::ptReadHeader()
	{
		// Create a string line
		String line = String(256);

		// Read the rest of the first line
		_stream->readLine(line, 256);
		_stream->readLine(line, 256);

		// Ensure we are reading the header
		if(line == "[Header]")
		{
			// Read number of vertices
			_stream->readLine(line, 256);
			Array<String> parts = line.split('=');
			SUINT numVertices = parts[1].toUInt();
			
			// Read indices
			_stream->readLine(line, 256);
			parts = line.split('=');
			SUINT numIndices = parts[1].toUInt();

			// Read actual vertex data
			_stream->readLine(line, 256);
			parts = line.split('=');
			SUINT vertexElements = parts[1].toUInt();
			SUINT offset = 0;

			for(SUINT i = 0; i < vertexElements; ++i)
			{
				_stream->readLine(line, 256);
				if(line == "float")
				{
					_mesh->_vertexDescription.addElement(VPT_FLOAT1, offset);
					offset += VertexProperty::GetSizeForType(VPT_FLOAT1);
				}
			}

			// Read extra line
			_stream->readLine(line, 256);
		}
	}

}	// Namespace