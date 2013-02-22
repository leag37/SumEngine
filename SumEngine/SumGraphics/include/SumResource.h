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

	// Get the resource path
	const String& filePath() const;

	// Get the resource type
	const String& fileType() const;

	// Get whether the resource is loaded
	const SBOOL isLoaded() const;

	// Load the resource
	void load();

	// Free the resource
	void unload();

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