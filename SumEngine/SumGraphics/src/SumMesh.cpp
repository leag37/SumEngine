//*************************************************************************************************
// Title: SumMesh.cpp
// Author: Gael Huber
// Description: Contains basic mesh data.
//*************************************************************************************************
#include "SumMesh.h"

namespace SumEngine
{
	//*************************************************************************************************
	// Default constructor
	//*************************************************************************************************
	Mesh::Mesh()
		:	Resource()
	{ }

	//*************************************************************************************************
	//Constructor
	// @param
	//	name The name of this resource
	// @param
	//	parentGroup The parent group for this resource
	//*************************************************************************************************
	Mesh::Mesh(const String& name, ResourceGroup* parentGroup)
		:	Resource(name, parentGroup)
	{ }

	//*************************************************************************************************
	// Constructor
	// @param
	//	name The name of this resource
	// @param
	//	parentGroup The parent group for this resource
	// @param
	//	fullName The full name of the file associated with this resource
	//*************************************************************************************************
	Mesh::Mesh(const String& name, ResourceGroup* parentGroup, const String& fullName)
		:	Resource(name, parentGroup, fullName)
	{ }

	//*************************************************************************************************
	// Destructor
	//*************************************************************************************************
	Mesh::~Mesh()
	{ }

	//*************************************************************************************************
	// Load the resource
	//*************************************************************************************************
	void Mesh::load()
	{
		// Set the resource status to loading
		_status = RESOURCE_STATUS_LOADING;

		// Request an open stream from the parent manager
		FileStreamPtr stream = _parentGroup->openResourceFile(_fullName);

		// Line type (0 = vert, 1 = index)
		SINT type = -1;

		// Iterate through the file
		if(stream->isOpen())
		{
			String line = String(256);
			while(stream->isEOF() == false)
			{
				// Grab the raw line
				stream->readLine(line, 256);

				// Determine the line type
				if(line.getLength() > 0 && line.at(0) != '#')
				{
					if(line.at(0) == '[' && line.at(line.getLength() - 1) == ']')
					{
						String lineType = line.substring(++line.begin(), --line.end());
						if(lineType == "Vertex")
						{
							type = 0;
						}
						else if(lineType == "Index")
						{
							type = 1;
						}
					}
					else
					{
						// Parse the line
						Array<String> aLine = line.split(' ');

						// Process vertex data
						if(type == 0)
						{
							/*_data.vertices.push_back(
								Vertex(
									aLine[0].toFloat(), aLine[1].toFloat(), aLine[2].toFloat(),
									aLine[3].toFloat(), aLine[4].toFloat(), aLine[5].toFloat()
								));*/
						}

						// Process index data
						else if(type == 1)
						{
							/*_data.indices.push_back(line[0].toUInt());
							_data.indices.push_back(line[1].toUInt());
							_data.indices.push_back(line[2].toUInt());*/
						}
					}
				}
			}
		
	}

	//*************************************************************************************************
	// Unload the resource
	//*************************************************************************************************
	void Mesh::unload()
	{

	}

	////*************************************************************************************************
	//// Constructor
	////*************************************************************************************************
	//Mesh::Mesh()
	//	:	_vertexBuffer(0),
	//		_indexBuffer(0),
	//		_vertexCount(0),
	//		_indexCount(0)
	//{ }

	////*************************************************************************************************
	//// Constructor
	////*************************************************************************************************
	//Mesh::Mesh(const String& name, const String& filePath, const String& fileType)
	//	:	_vertexBuffer(0),
	//		_indexBuffer(0),
	//		_vertexCount(0),
	//		_indexCount(0)
	//{ }

	////*************************************************************************************************
	//// Constructor from name
	////*************************************************************************************************
	//Mesh::Mesh(const String& name)
	//	:	_vertexBuffer(0),
	//		_indexBuffer(0),
	//		_vertexCount(0),
	//		_indexCount(0)
	//{ }

	////*************************************************************************************************
	//// Create the mesh
	////*************************************************************************************************
	//Mesh::Mesh(const String& name, ID3D11Buffer* vertexBuffer, ID3D11Buffer* indexBuffer, SUINT vertexCount, SUINT indexCount)
	//	:	_vertexBuffer(vertexBuffer), 
	//		_indexBuffer(indexBuffer), 
	//		_vertexCount(vertexCount), 
	//		_indexCount(indexCount)
	//{ }

	////*************************************************************************************************
	//// Destructor
	////*************************************************************************************************
	//Mesh::~Mesh()
	//{
	//	ReleaseCOM(_vertexBuffer);
	//	ReleaseCOM(_indexBuffer);
	//}

	////*************************************************************************************************
	//// Load the mesh
	////*************************************************************************************************
	//void Mesh::load()
	//{
	//	std::fstream stream("");//_filePath);

	//	// Line type (0 = vert, 1 = index)
	//	SINT type = -1;

	//	// Iterate through the file
	//	if(stream.is_open())
	//	{
	//		while(stream.good())
	//		{
	//			// Grab the raw line
	//			std::string tmpLine;
	//			std::getline(stream, tmpLine);
	//			String raw = tmpLine.c_str();

	//			// Determine the line type
	//			if(raw.getLength() > 0 && raw.at(0) != '#')
	//			{
	//				if(raw.at(0) == '[' && raw.at(raw.getLength() - 1) == ']')
	//				{
	//					String lineType = raw.substring(++raw.begin(), --raw.end());
	//					if(lineType == "Vertex")
	//					{
	//						type = 0;
	//					}
	//					else if(lineType == "Index")
	//					{
	//						type = 1;
	//					}
	//				}
	//				else
	//				{
	//					// Parse the line
	//					Array<String> line = raw.split(' ');

	//					// Process vertex data
	//					if(type == 0)
	//					{
	//						_data.vertices.push_back(
	//							Vertex(
	//								line[0].toFloat(), line[1].toFloat(), line[2].toFloat(),
	//								line[3].toFloat(), line[4].toFloat(), line[5].toFloat()
	//							));
	//					}

	//					// Process index data
	//					else if(type == 1)
	//					{
	//						_data.indices.push_back(line[0].toUInt());
	//						_data.indices.push_back(line[1].toUInt());
	//						_data.indices.push_back(line[2].toUInt());
	//					}
	//				}
	//			}
	//		}
	//	}

	//	// Now that we have constructed the mesh, create it
	//	//Geometry::CreateBuffersFromData(_data, &_vertexBuffer, &_indexBuffer);

	//	// Set vertex counts
	//	//_vertexCount = _data.vertices.getCount();
	//	//_indexCount = _data.indices.getCount();

	//	// Is loaded is now true
	//	//_isLoaded = true;
	//}

	////*************************************************************************************************
	//// Free the mesh
	////*************************************************************************************************
	//void Mesh::unload()
	//{
	//
	//}

	////*************************************************************************************************
	//// Return the mesh data for this object
	////*************************************************************************************************
	//const MeshData& Mesh::getMeshData() const
	//{
	//	return _data;
	//}

}	// Namespace