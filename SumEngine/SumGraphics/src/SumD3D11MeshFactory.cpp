//*************************************************************************************************
// Title: SumD3D11MeshFactory.cpp
// Author: Gael Huber
// Description: Loads and creates D3D11 mesh resources
//*************************************************************************************************
#include "SumD3D11MeshFactory.h"

namespace SumEngine
{
	//*************************************************************************************************
	// Default constructor
	//*************************************************************************************************
	D3D11MeshFactory::D3D11MeshFactory()
		:	MeshFactory()
	{ }
		
	//*************************************************************************************************
	// Constructor
	// @param
	//	name The name of this factory
	// @param
	//	device The D3D11 device used for constructing mesh from data
	//*************************************************************************************************
	D3D11MeshFactory::D3D11MeshFactory(const String& name, D3D11RenderSystem* renderSystem)
		:	MeshFactory(name),
			_device(renderSystem->getD3D11Device())
	{ }

	//*************************************************************************************************
	// Destructor
	//*************************************************************************************************
	D3D11MeshFactory::~D3D11MeshFactory()
	{ }

	//*************************************************************************************************
	// Create a resource
	// @param
	//	name The name of the resource
	// @param
	//	parentGroup The parent group for this resource (this should be passed in here due to the
	//	possibility of having multiple parentGroups.
	//*************************************************************************************************
	Resource* D3D11MeshFactory::createResource(const String& name, ResourceGroup* parentGroup)
	{
		// Create a new resource instance
		D3D11Mesh* mesh = new D3D11Mesh(name, parentGroup, _device);
		return mesh;
	}

	//*************************************************************************************************
	// Create a resource
	// @param
	//	name The name of the resource
	// @param
	//	parentGroup The parent group for this resource (this should be passed in here due to the
	//	possibility of having multiple parentGroups.
	// @param
	//	fullName The full filename associated with this resource
	//*************************************************************************************************
	Resource* D3D11MeshFactory::createResource(const String& name, ResourceGroup* parentGroup, const String& fullName)
	{
		D3D11Mesh* mesh = new D3D11Mesh(name, parentGroup, fullName, _device);
		return mesh;
	}

}	// Namespace