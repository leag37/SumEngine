//*************************************************************************************************
// Title: SumConfigurationManager.h
// Author: Gael Huber
// Description: Configuration manager for engine.
//*************************************************************************************************
#ifndef __SUMCONFIGURATIONMANAGER_H__
#define __SUMCONFIGURATIONMANAGER_H__

#include "SumInclude.h"

class ConfigurationManager : public Singleton<ConfigurationManager>
{
public:
	// Constructor
	ConfigurationManager();

	// Destructor
	~ConfigurationManager();

	// Start up the configuration manager
	void startUp();

	// Shut down the configuration manager
	void shutDown();

private:


public:
	// Get the singleton instance
	SUMINLINE static ConfigurationManager& getSingleton()
	{
		assert(singleton);
		return *singleton;
	}

	// Get singleton pointer
	SUMINLINE static ConfigurationManager* getSingletonPtr()
	{
		return singleton;
	}
};

#endif