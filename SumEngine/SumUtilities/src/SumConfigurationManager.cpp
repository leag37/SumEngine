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
	std::fstream fin("SumConfig.cfg");

	if(fin.is_open())
	{
		std::string line;
		while(fin.good())
		{
			std::getline(fin, line);
		}
	}

	fin.seekg(0, std::ios_base::end);
	int size = (int)fin.tellg();
	fin.seekg(0, std::ios_base::beg);
	Array<char> compiledShader(size);

	fin.read(&compiledShader[0], size);
	fin.close();
}
