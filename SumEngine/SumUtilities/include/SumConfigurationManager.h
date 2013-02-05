//*************************************************************************************************
// Title: SumConfigurationManager.h
// Author: Gael Huber
// Description: Configuration manager for engine.
//
// TODO: Switch to use SumEngine string
//*************************************************************************************************
#ifndef __SUMCONFIGURATIONMANAGER_H__
#define __SUMCONFIGURATIONMANAGER_H__

#include "SumInclude.h"
#include "SumDictionary.h"
#include "SumString.h"
#include "SumArray.h"
#include <fstream>
#include <string>

// Configuration structure
class Configuration
{
public:
	// Constructor
	Configuration(String name)
		:	_name(name)
	{}

public:
	SUMINLINE const String& name() const
	{
		return _name;
	}

	SUMINLINE const String& retrieveValue(const String& key)
	{
		return _configMap.find(key)->getValue();
	}

	SUMINLINE void addConfigPair(const String& key, const String& value)
	{
		_configMap[key] = value;
	}

private:
	// Name
	String _name;

	// Configuration keys
	Dictionary<String, String> _configMap;
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
	Dictionary<String, Configuration*> _configurations;

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