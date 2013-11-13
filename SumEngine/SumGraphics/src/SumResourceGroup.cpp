//*************************************************************************************************
// Title: SumResourceGroup.cpp
// Author: Gael Huber
// Description: A resource group holds all references to a particular resource type. Actual
//	resource creation is handled by a ResourceFactory which based on the type will return the
//	appropriate resource type for the ResourceGroup.
//
// For example, given the resource type RESOURCE_TYPE_MESH, the group would create a new resource
//	via ResourceFactory::createResource(RESOURCE_TYPE_MESH, name, etc.)
//*************************************************************************************************
#include "SumResourceGroup.h"

namespace SumEngine
{

	//*************************************************************************************************
	// Default constructor
	//*************************************************************************************************
	ResourceGroup::ResourceGroup()
		:	_parentManager(0),
			_resourceFactory(0)
	{ }

	//*************************************************************************************************
	// Constructor
	// @param
	//	name The name of the resource group
	// @param
	//	type The type of resource group
	// @param
	//	parentManager The parent resource manager for this group
	//*************************************************************************************************
	ResourceGroup::ResourceGroup(const String& name, ResourceGroupType type, ResourceManager* parentManager)
		:	_name(name), 
			_resourceGroupType(type), 
			_parentManager(parentManager),
			_resourceFactory(0)
	{
	}

	//*************************************************************************************************
	// Set the resource factory instance for this group
	// @param
	//	resourceFactory The specialized factory for this group type
	//*************************************************************************************************
	void ResourceGroup::setResourceFactory(ResourceFactory* resourceFactory)
	{
		_resourceFactory = resourceFactory;
	}

}	// Namespace