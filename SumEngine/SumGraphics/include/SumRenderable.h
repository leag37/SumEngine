//*************************************************************************************************
// Title: SumRenderable.h
// Author: Gael Huber
// Description: A basic renderable item. This allows us primitive access to renderable attributes
//	such as mesh data, texture data, etc.
//
// TODO: Move mesh data into a separate MESH object
// TODO: Move texture data into a separate MATERIAL object
//*************************************************************************************************
#ifndef __SUMRENDERABLE_H__
#define __SUMRENDERABLE_H__

#include "SumInclude.h"
#include "SumMath.h"

class Renderable
{
public:
	// Constructor
	Renderable();

	// Destructor
	~Renderable();

private:
	// Vertex buffer
	ID3D11Buffer* _vertexBuffer;

	// Index buffer
	ID3D11Buffer* _indexBuffer;

	// Number of indices in the mesh
	SUINT _indexCount;

	// World matrix of the object
	FLOAT4x4 _world;
};

#endif