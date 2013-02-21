//*************************************************************************************************
// Title: SumResourceManager.h
// Author: Gael Huber
// Description: Manages all resources and resource types, loading and unloading of files
//
// TODO: Switch over to having resources be configured by "dir" rather than unique names
//*************************************************************************************************
#ifndef __SUMRESOURCEMANAGER_H__
#define __SUMRESOURCEMANAGER_H__

#include "SumInclude.h"
#include "SumConfigurationManager.h"
#include "SumDictionary.h"
#include "SumResource.h"
#include "SumBaseResource.h"

#include <fstream>
#include <dirent.h>

class ResourceManager : public Singleton<ResourceManager>
{
public:
	// Constructor
	ResourceManager();

	// Destructor
	~ResourceManager();

	// Start up the resource manager
	void startUp();

	// Shut down the resource manager
	void shutDown();

	// Get a resource from the resource pool
	template <typename ResourceType>
	ResourceType* getResourceById(const String& name, const String& type);

private:
	// Load the resource file names from configuration
	void loadFromConfig();

	// Load resource files from a directory
	void loadFromDir(const String& dir);

	// Create a resource pool
	void createResourcePool(const String& type);

private:
	// A resource pool
	Dictionary<String, Dictionary<String, BaseResource*>> _resourcePools;

public:
	// Get the singleton instance
	SUMINLINE static ResourceManager& getSingleton()
	{
		assert(singleton);
		return *singleton;
	}

	// Get singleton pointer
	SUMINLINE static ResourceManager* getSingletonPtr()
	{
		return singleton;
	}

};

#include "SumResourceManager.inl"

#endif
