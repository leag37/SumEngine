//*************************************************************************************************
// Title: SumMesh.h
// Author: Gael Huber
// Description: Contains basic mesh data.
//
// TODO: Write unload function for mesh
//*************************************************************************************************
#ifndef __SUMMESH_H__
#define __SUMMESH_H__

#include "SumRenderCore.h"
#include "SumBaseResource.h"

class Mesh : public BaseResource
{
public:
	// Constructor
	Mesh();

	// Constructor
	Mesh(const String& name, const String& filePath, const String& fileType);

	// Constructor from name
	Mesh(const String& name);

	// Create the mesh
	Mesh(const String& name, ID3D11Buffer* vertexBuffer, ID3D11Buffer* indexBuffer, SUINT vertexCount, SUINT indexCount);

	// Destructor
	~Mesh();

	// Load the mesh
	void load();

	// Free the mesh
	void unload();

	// Return the mesh data for this object
	const MeshData& getMeshData() const;

private:
	// Vertex buffer
	ID3D11Buffer* _vertexBuffer;

	// Index buffer
	ID3D11Buffer* _indexBuffer;

	// Vertex count
	SUINT _vertexCount;

	// Index count
	SUINT _indexCount;

	// Mesh data for this mesh
	MeshData _data;

// Inline functions
public:
	SUMINLINE ID3D11Buffer* vertexBuffer()
	{
		return _vertexBuffer;
	}

	// Return the vertex buffer
	SUMINLINE ID3D11Buffer** vertexBufferPtr()
	{
		return &_vertexBuffer;
	}

	// Release the existing buffer and set the new one
	SUMINLINE void vertexBuffer(ID3D11Buffer* rhs)
	{
		ReleaseCOM(_vertexBuffer);
		_vertexBuffer = rhs;
	}

	// Return the index buffer
	SUMINLINE ID3D11Buffer* indexBuffer() const
	{
		return _indexBuffer;
	}

	// Release the existing buffer and set the new one
	SUMINLINE void indexBuffer(ID3D11Buffer* rhs)
	{
		ReleaseCOM(_indexBuffer);
		_indexBuffer = rhs;
	}

	// Get the vertex count
	SUMINLINE SUINT vertexCount() const
	{
		return _vertexCount;
	}

	// Set the vertex count
	SUMINLINE void vertexCount(SUINT rhs)
	{
		_vertexCount = rhs;
	}

	// Return the index count
	SUMINLINE SUINT indexCount() const
	{
		return _indexCount;
	}

	// Set the index count
	SUMINLINE void indexCount(SUINT rhs)
	{
		_indexCount = rhs;
	}

	// Return the mesh data
	SUMINLINE const MeshData& data() const
	{
		return _data;
	}
	
};

#endif