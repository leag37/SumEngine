//*************************************************************************************************
// Title: SumConfigurationManager.cpp
// Author: Gael Huber
// Description: Configuration manager for engine.
//*************************************************************************************************
#include "SumConfigurationManager.h"

//*************************************************************************************************
// Initialize the singleton instance of this class to 0
//*************************************************************************************************
template <> ConfigurationManager* Singleton<ConfigurationManager>::singleton = 0;

//*************************************************************************************************
// Constructor
//*************************************************************************************************
ConfigurationManager::ConfigurationManager()
{
}

//*************************************************************************************************
// Destructor
//*************************************************************************************************
ConfigurationManager::~ConfigurationManager()
{

}

//*************************************************************************************************
// Start up the configuration manager
//*************************************************************************************************
void ConfigurationManager::startUp()
{
	// Load the primary configuration file
	loadPrimaryConfig();
}

//*************************************************************************************************
// Shut down the configuration manager
//*************************************************************************************************
void ConfigurationManager::shutDown()
{

}

//*************************************************************************************************
// Read the primary configuration file
//*************************************************************************************************
void ConfigurationManager::loadPrimaryConfig()
{
	// Open the file
	std::fstream fin("SumConfig.cfg");

	// Ensure the file is good
	if(fin.is_open())
	{
		std::string tmpLine;
		String line;

		Configuration* config;

		while(fin.good())
		{
			// Get the line
			std::getline(fin, tmpLine);
			line = tmpLine.c_str();

			// Parse the line
			//-------------------
			
			// Ensure valid line
			if(line.getLength() == 0 || line.at(0) == '#')
			{
				continue;
			}

			// Section
			if(line.at(0) == '[' && line.at(line.getLength() - 1) == ']')
			{
				// Pull the section name
				String section = line.substring(1, line.getLength() - 2);
				
				// Create the new configuration
				config = new Configuration(section);

				// Attach the config to the map
				_configurations[section] = config;
			}

			// Property
			else if(line.find('=') != -1)
			{
				// Parse line
				Array<String> values = line.split('=');
				config->addConfigPair(values[0], values[1]);
			}
		}

		// Close the stream
		fin.close();
	}
}
