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
#include "SumRenderCore.h"

class Renderable
{
public:
	// Constructor
	Renderable();

	// Destructor
	~Renderable();

private:
	// Mesh
//	Mesh* _mesh;

	// World matrix of the object
	Float4x4 _world;

// Inline functions
public:
	// Set the mesh for the renderable
//	SUMINLINE void setMesh(Mesh* mesh)
//	{
//		_mesh = mesh;
//	}

	// Retrieve the mesh
//	SUMINLINE const Mesh* mesh() const
//	{
//		return _mesh;
//	}

	// Get the world object
	SUMINLINE const Float4x4& world() const
	{
		return _world;
	}
};

#endif