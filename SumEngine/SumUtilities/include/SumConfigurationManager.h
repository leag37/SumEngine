//*************************************************************************************************
// Title: SumConfigurationManager.h
// Author: Gael Huber
// Description: Configuration manager for engine.
//*************************************************************************************************
#ifndef __SUMCONFIGURATIONMANAGER_H__
#define __SUMCONFIGURATIONMANAGER_H__

#include "SumInclude.h"
#include "SumDictionary.h"
#include "SumString.h"
#include <fstream>
#include <string>

// Configuration structure
struct Configuration
{
	// Constructor
	Configuration(String name);

	// Name
	String name;

	// Configuration keys
	Dictionary<String, String> configMap;
};

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
	// Read the primary configuration file
	void loadPrimaryConfig();

private:
	// Dictionary of configurations
	Dictionary<String, Configuration> _configurations;

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