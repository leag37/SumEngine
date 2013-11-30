//*************************************************************************************************
// Title: SumResource.cpp
// Author: Gael Huber
// Description: An engine resource of any given type. This serves as a template for loading
//	specific resources.
//*************************************************************************************************
#include "SumResource.h"

namespace SumEngine
{
	//*************************************************************************************************
	// Default constructor
	//*************************************************************************************************
	Resource::Resource()
		:	_parentGroup(0),
			_status(RESOURCE_STATUS_UNLOADED)
	{ }

	//*************************************************************************************************
	//Constructor
	// @param
	//	name The name of this resource
	// @param
	//	parentGroup The parent group for this resource
	//*************************************************************************************************
	Resource::Resource(const String& name, ResourceGroup* parentGroup)
		:	_name(name),
			_parentGroup(parentGroup),
			_status(RESOURCE_STATUS_UNLOADED)
	{ }

	//*************************************************************************************************
	// Destructor
	//*************************************************************************************************
	Resource::~Resource()
	{
		// TODO: Unload the resource


		// Set parent group to 0
		_parentGroup = 0;
	}

}	// Namespace