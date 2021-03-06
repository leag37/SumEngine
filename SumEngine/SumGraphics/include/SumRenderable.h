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

class Mesh;

class SUM_DECLSPEC_ALIGN_16 Renderable
{
public:
	_SUM_ALIGN(Renderable);

public:
	// Constructor
	Renderable();

	// Constructor
	Renderable(const String& name, const String& mesh);

	// Destructor
	~Renderable();

	// Set the position in XYZ coordinates
	void setPosition(SFLOAT x, SFLOAT y, FLOAT z);

private:
	// Renderable name
	String _name;

	// Mesh
	Mesh* _mesh;

	// World information matrix
	Matrix _world;

// Inline functions
public:
	// Get the name
	SUMINLINE const String& name() const
	{
		return _name;
	}

	// Retrieve the mesh
	SUMINLINE Mesh* mesh() const
	{
		return _mesh;
	}

	// Get the world
	SUMINLINE const Matrix& world()
	{
		return _world;
	}
};

#endif