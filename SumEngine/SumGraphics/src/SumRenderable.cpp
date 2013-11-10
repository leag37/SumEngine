//*************************************************************************************************
// Title: SumRenderable.cpp
// Author: Gael Huber
// Description: A basic renderable item. This allows us primitive access to renderable attributes
//	such as mesh data, texture data, etc.
//*************************************************************************************************
#include "SumRenderable.h"

namespace SumEngine
{
	//*************************************************************************************************
	// Constructor
	//*************************************************************************************************
	Renderable::Renderable()
		:	_name(""),
			_mesh(0)
	{
		_world = MatrixIdentity();
	}

	//*************************************************************************************************
	// Constructor
	//*************************************************************************************************
	Renderable::Renderable(const String& name, const String& mesh)
		:	_name(name)
	{
		// Set world
		_world = MatrixIdentity();

		// Load the mesh
		_mesh = ResourceManager::getSingletonPtr()->getResourceById<Mesh>(mesh, "mesh");
	}

	//*************************************************************************************************
	// Destructor
	//*************************************************************************************************
	Renderable::~Renderable()
	{
		_mesh = 0;
	}

	//*************************************************************************************************
	// Set the position in XYZ coordinates 
	//*************************************************************************************************
	void Renderable::setPosition(SFLOAT x, SFLOAT y, FLOAT z)
	{
		MatrixSetTranslation(_world, x, y, z);	
	}



}	// Namespace