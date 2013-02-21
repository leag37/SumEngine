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
	Resource();

	// Constructor
	Resource(const String& name, const String& filePath, const String& fileType);

	// Destructor
	virtual ~Resource();

	// Get the resource
	Type* resource();

	// Get the name
	const String& name() const;

protected:
	// Load the resource
	void _load();

	// Free the resource
	void _unload();

protected:
	// The loaded resource
	Type* _resource;

	// The resource name
	String _name;

	// The resource path
	String _filePath;

	// The resource type
	String _fileType;

	// Is the resource loaded
	SBOOL _isLoaded;
};

#include "SumResource.inl"

#endif