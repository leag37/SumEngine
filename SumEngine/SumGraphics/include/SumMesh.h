//*************************************************************************************************
// Title: SumMesh.h
// Author: Gael Huber
// Description: Contains basic mesh data.
//*************************************************************************************************
#ifndef __SUMMESH_H__
#define __SUMMESH_H__

#include "SumInclude.h"

class Mesh
{
public:
	// Constructor
	Mesh();

	// Create the mesh
	Mesh(ID3D11Buffer* vertexBuffer, ID3D11Buffer* indexBuffer, SUINT indexCount);

	// Destructor
	~Mesh();

private:
	// Vertex buffer
	ID3D11Buffer* _vertexBuffer;

	// Index buffer
	ID3D11Buffer* _indexBuffer;

	// Index count
	SUINT _indexCount;

// Inline functions
public:
	// Return the vertex buffer
	SUMINLINE ID3D11Buffer* vertexBuffer() const
	{
		return _vertexBuffer;
	}

	// Return the index buffer
	SUMINLINE ID3D11Buffer* indexBuffer() const
	{
		return _indexBuffer;
	}

	// Return the index count
	SUMINLINE SUINT indexCount() const
	{
		return _indexCount;
	}
};

#endif