//*************************************************************************************************
// Title: SumMesh.cpp
// Author: Gael Huber
// Description: Contains basic mesh data.
//*************************************************************************************************
#include "SumMesh.h"

//*************************************************************************************************
// Constructor
//*************************************************************************************************
Mesh::Mesh()
	:	BaseResource(),
		_vertexBuffer(0),
		_indexBuffer(0),
		_vertexCount(0),
		_indexCount(0)
{ }

//*************************************************************************************************
// Constructor
//*************************************************************************************************
Mesh::Mesh(const String& name, const String& filePath, const String& fileType)
	:	BaseResource(name, filePath, fileType),
		_vertexBuffer(0),
		_indexBuffer(0),
		_vertexCount(0),
		_indexCount(0)
{ }

//*************************************************************************************************
// Constructor from name
//*************************************************************************************************
Mesh::Mesh(const String& name)
	:	_vertexBuffer(0),
		_indexBuffer(0),
		_vertexCount(0),
		_indexCount(0)
{ }

//*************************************************************************************************
// Create the mesh
//*************************************************************************************************
Mesh::Mesh(const String& name, ID3D11Buffer* vertexBuffer, ID3D11Buffer* indexBuffer, SUINT vertexCount, SUINT indexCount)
	:	_vertexBuffer(vertexBuffer), 
		_indexBuffer(indexBuffer), 
		_vertexCount(vertexCount), 
		_indexCount(indexCount)
{ }

//*************************************************************************************************
// Destructor
//*************************************************************************************************
Mesh::~Mesh()
{
	ReleaseCOM(_vertexBuffer);
	ReleaseCOM(_indexBuffer);
}

//*************************************************************************************************
// Load the mesh
//*************************************************************************************************
void Mesh::load()
{
	std::fstream stream(_filePath);

	// Line type (0 = vert, 1 = index)
	SINT type = -1;

	// Iterate through the file
	if(stream.is_open())
	{
		while(stream.good())
		{
			// Grab the raw line
			std::string tmpLine;
			std::getline(stream, tmpLine);
			String raw = tmpLine.c_str();

			// Determine the line type
			if(raw.getLength() > 0 && raw.at(0) != '#')
			{
				if(raw.at(0) == '[' && raw.at(raw.getLength() - 1) == ']')
				{
					String lineType = raw.substring(++raw.begin(), --raw.end());
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
					Array<String> line = raw.split(' ');

					// Process vertex data
					if(type == 0)
					{
						_data.vertices.push_back(
							Vertex(
								line[0].toFloat(), line[1].toFloat(), line[2].toFloat(),
								line[3].toFloat(), line[4].toFloat(), line[5].toFloat()
							));
					}

					// Process index data
					else if(type == 1)
					{
						_data.indices.push_back(line[0].toUInt());
						_data.indices.push_back(line[1].toUInt());
						_data.indices.push_back(line[2].toUInt());
					}
				}
			}
		}
	}

	// Now that we have constructed the mesh, create it
	Geometry::CreateBuffersFromData(_data, &_vertexBuffer, &_indexBuffer);

	// Set vertex counts
	_vertexCount = _data.vertices.getCount();
	_indexCount = _data.indices.getCount();

	// Is loaded is now true
	_isLoaded = true;
}

//*************************************************************************************************
// Free the mesh
//*************************************************************************************************
void Mesh::unload()
{
	
}