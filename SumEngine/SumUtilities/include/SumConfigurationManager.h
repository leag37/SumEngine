//*************************************************************************************************
// Title: SumConfigurationManager.h
// Author: Gael Huber
// Description: Configuration manager for engine.
//
// TODO: Switch accessors to have const and non-const modifiers
// TODO: Switch from using a map to a multimap
// TODO: Switch configuraton such that it doesn't need unique names (i.e. file and dir)
//*************************************************************************************************
#ifndef __SUMCONFIGURATIONMANAGER_H__
#define __SUMCONFIGURATIONMANAGER_H__

#include "SumInclude.h"
#include "SumDictionary.h"
#include "SumString.h"
#include "SumArray.h"
#include <fstream>

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

	SUMINLINE const String& retrieveValue(const String& key) const
	{
		return _configMap.find(key)->getValue();
	}

	SUMINLINE void addConfigPair(const String& key, const String& value)
	{
		_configMap[key] = value;
	}

	SUMINLINE const Dictionary<String, String> configMap() const
	{
		return _configMap;
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

	// Retrieve a configuration
	Configuration* getConfiguration(const String& key);
	//const Configuration* getConfiguration(const String& key) const;

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