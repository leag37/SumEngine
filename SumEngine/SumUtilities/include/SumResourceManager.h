//*************************************************************************************************
// Title: SumResourceManager.h
// Author: Gael Huber
// Description: Manages all resources and resource types, loading and unloading of files
//*************************************************************************************************
#ifndef __SUMRESOURCEMANAGER_H__
#define __SUMRESOURCEMANAGER_H__

#include "SumInclude.h"
#include "SumConfigurationManager.h"
#include "Resource.h"


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

private:


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

#endif
