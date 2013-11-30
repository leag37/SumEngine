//*************************************************************************************************
// Title: SumResourceFactory.cpp
// Author: Gael Huber
// Description: A resource factory that aids in the creation of various assets based on group. 
//*************************************************************************************************
#include "SumResourceFactory.h"

namespace SumEngine
{
	//*************************************************************************************************
	// Default constructor
	//*************************************************************************************************
	ResourceFactory::ResourceFactory()
	{ }

	//*************************************************************************************************
	// Destructor
	//*************************************************************************************************
	ResourceFactory::~ResourceFactory()
	{ }

	//*************************************************************************************************
	// Constructor specifying name
	// @param
	//	name The name for this factory
	//*************************************************************************************************
	ResourceFactory::ResourceFactory(const String& name)
		:	_name(name)
	{ }

}	// Namespace