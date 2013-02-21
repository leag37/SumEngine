//*************************************************************************************************
// Title: SumResourceManager.cpp
// Author: Gael Huber
// Description: Manages all resources and resource types, loading and unloading of files
//*************************************************************************************************
#include "SumResourceManager.h"

//*************************************************************************************************
// Initialize the singleton instance of this class to 0
//*************************************************************************************************
template <> ResourceManager* Singleton<ResourceManager>::singleton = 0;

//*************************************************************************************************
// Constructor
//*************************************************************************************************
ResourceManager::ResourceManager()
{ }

//*************************************************************************************************
// Destructor
//*************************************************************************************************
ResourceManager::~ResourceManager()
{ }

//*************************************************************************************************
// Start up the resource manager
//*************************************************************************************************
void ResourceManager::startUp()
{
	// Create the resource pools
	_resourcePools = Dictionary<String, Dictionary<String, BaseResource*>>();

	// Iterate through configurations and load file names
	loadFromConfig();
}

//*************************************************************************************************
// Shut down the resource manager
//*************************************************************************************************
void ResourceManager::shutDown()
{

}

//*************************************************************************************************
// Load the resource file names from configuration
//*************************************************************************************************
void ResourceManager::loadFromConfig()
{
	// Grab the configuration
	Configuration* config = ConfigurationManager::getSingletonPtr()->getConfiguration("Resources");
	Dictionary<String, String> resourceMap = config->configMap();

	// Iterate through the config map
	Dictionary<String, String>::Iterator endItr = resourceMap.end();
	for(Dictionary<String, String>::Iterator itr = resourceMap.begin(); itr != endItr; ++itr)
	{
		// Determine load step for resources

		// Load from a directory
		loadFromDir(itr->getValue());
	}
}


//*************************************************************************************************
// Load resource files from a directory
//*************************************************************************************************
void ResourceManager::loadFromDir(const String& dir)
{
	// Pointer to directory
	DIR* pDir = 0;
	struct dirent* entry;

	// Attempt to open the directory
	pDir = opendir(dir.c_str());

	if(pDir)
	{
		// Read the file entry
		while(entry = readdir(pDir))
		{
			// Grab the file name and type
			String fullName = String(entry->d_name);
			Array<String> fileInfo = fullName.split('.');
			if(fileInfo.getCount() > 0)
			{
				String name = fileInfo[0];
				String type = fileInfo[1];

				// Create an entry for the resource
				Dictionary<String, Dictionary<String, BaseResource*>>::Iterator itr;
				itr = _resourcePools.find(type);
			
				// If the key does not exist, create it
				if(itr == _resourcePools.end())
				{
					_resourcePools[type] = Dictionary<String, BaseResource*>();
				}

				_resourcePools[type][name] = new BaseResource(name, dir + fullName, type);
			}
		} 
		
		// Close the directory
		closedir(pDir);
	}

}


// Create a resource pool
void ResourceManager::createResourcePool(const String& type)
{
	_resourcePools[type] = Dictionary<String, BaseResource*>();
}
