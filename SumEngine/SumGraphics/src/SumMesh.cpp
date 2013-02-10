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
	:	_vertexBuffer(0),
		_indexBuffer(0),
		_vertexCount(0),
		_indexCount(0)
{ }

//*************************************************************************************************
// Create the mesh
//*************************************************************************************************
Mesh::Mesh(ID3D11Buffer* vertexBuffer, ID3D11Buffer* indexBuffer, SUINT vertexCount, SUINT indexCount)
	:	_vertexBuffer(vertexBuffer), _indexBuffer(indexBuffer), _vertexCount(vertexCount), _indexCount(indexCount)
{ }

//*************************************************************************************************
// Destructor
//*************************************************************************************************
Mesh::~Mesh()
{
	ReleaseCOM(_vertexBuffer);
	ReleaseCOM(_indexBuffer);
}

