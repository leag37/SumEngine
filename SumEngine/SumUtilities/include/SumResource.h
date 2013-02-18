//*************************************************************************************************
// Title: SumResource.h
// Author: Gael Huber
// Description: An engine resource of any given type. This serves as a template for loading
//	specific resources.
//*************************************************************************************************
#ifndef __SUMRESOURCE_H__
#define __SUMRESOURCE_H__

#include "SumInclude.h"
#include "SumString.h"

template <typename Type>
class Resource
{
public:
	// Constructor
	Resource(const String& name);

	// Constructor
	Resource(const String& name, String& filePath);

	// Destructor
	~Resource();

	// Get the resource
	Type* resource();

	// Get the name
	const String& name() const;

protected:
	// Load the resource
	virtual void _load();

protected:
	// The loaded resource
	Type* _resource;

	// The resource name
	String _name;

	// The resource path
	String _filePath;

	// Is the resource loaded
	SBOOL _isLoaded;
};

#endif