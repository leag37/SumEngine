//*************************************************************************************************
// Title: SumMeshFactory.cpp
// Author: Gael Huber
// Description: A resource factory that creates meshes.
//*************************************************************************************************
#include "SumMeshFactory.h"

namespace SumEngine
{
	/** Default constructor
	*/
	MeshFactory::MeshFactory()
		:	ResourceFactory()
	{ }

	/** Constructor specifying name
	* @param
	*	name The name for this factory
	*/
	MeshFactory::MeshFactory(const String& name)
		:	ResourceFactory(name)
	{ }

	/** Destructor
	*/
	MeshFactory::~MeshFactory()
	{ }

}	// Namespace