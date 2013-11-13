//*************************************************************************************************
// Title: SumResourceManager.cpp
// Author: Gael Huber
// Description: Manages all resources and resource types, loading and unloading of files
//*************************************************************************************************
#include "SumResourceManager.h"

//*************************************************************************************************
// Initialize the singleton instance of this class to 0
//*************************************************************************************************
template <> SumEngine::ResourceManager* Singleton<SumEngine::ResourceManager>::singleton = 0;

namespace SumEngine
{
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
		// Initialize the file system
		_createFileSystem();

		// Create the resource groups
		_createResourceGroups();

		//// Create the resource pools
		//_resources = Dictionary<String, Dictionary<String, BaseResource*>>();

		//// Iterate through configurations and load file names
		//loadFromConfig();
	}

	//*************************************************************************************************
	// Shut down the resource manager
	//*************************************************************************************************
	void ResourceManager::shutDown()
	{

	}

	//*************************************************************************************************
	// Create resource file system
	//*************************************************************************************************
	void ResourceManager::_createFileSystem()
	{
		// Create the file system
		_fileSystem = new FileSystem("resources");

		// Grab the configuration
		Configuration* config = ConfigurationManager::getSingletonPtr()->getConfiguration("Resources");
		Dictionary<String, String> resourceMap = config->configMap();

		// Iterate through the config map
		Dictionary<String, String>::Iterator endItr = resourceMap.end();
		for(Dictionary<String, String>::Iterator itr = resourceMap.begin(); itr != endItr; ++itr)
		{
			// Add the directory to the file system
			_fileSystem->addDirectory(itr->getValue());
		}
	}

	//*************************************************************************************************
	// Initialize the resource groups for this system
	//*************************************************************************************************
	void ResourceManager::_createResourceGroups()
	{
		_resourceGroups[RESOURCE_GROUP_TYPE_MESH] = new ResourceGroup("meshGroup", RESOURCE_GROUP_TYPE_MESH, this);
		_resourceGroups[RESOURCE_GROUP_TYPE_MATERIAL] = new ResourceGroup("materialGroup", RESOURCE_GROUP_TYPE_MATERIAL, this);
		_resourceGroups[RESOURCE_GROUP_TYPE_SHADER] = new ResourceGroup("shaderGroup", RESOURCE_GROUP_TYPE_SHADER, this);
	}

	//*************************************************************************************************
	// Detect the resource group that this resource request falls under
	// @param
	//	fullName The full name of the resource -- including extension
	// @return
	//	ResourceGroupType The corresponding resource group id
	//*************************************************************************************************
	ResourceGroupType ResourceManager::_detectResourceGroup(const String& fullName)
	{
		// Type
		ResourceGroupType group = RESOURCE_GROUP_TYPE_DEFAULT;

		// Find the index of the delimiter
		Array<String> arrName = fullName.split('.');
		String type = arrName[1];
		if(type == "mesh")
		{
			group = RESOURCE_GROUP_TYPE_MESH;
		}
		else if(type == "material")
		{
			group = RESOURCE_GROUP_TYPE_MATERIAL;
		}
		else if(type == "shader")
		{
			group = RESOURCE_GROUP_TYPE_SHADER;
		}

		return group;
	}

	//*************************************************************************************************
	// Search the archive for information about a given file
	// @param 
	//	fullName The full filename of the file we are searching for
	// @return
	//	FileInfo Information related to the file
	//*************************************************************************************************
	FileInfo ResourceManager::getFileInfo(const String& fullName)
	{
		// Search the filesystem for related file info
		return _fileSystem->findFile(fullName);
	}

	//*************************************************************************************************
	// Add a resource factory to a specified group type
	// @param
	//	factory The factory pointer
	// @param
	//	resourceGroup The resource group to assign the factory
	//*************************************************************************************************
	void ResourceManager::addResourceFactoryForGroup(ResourceFactory* factory, ResourceGroupType resourceGroup)
	{
		_resourceGroups[resourceGroup]->setResourceFactory(factory);
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
	/*	DIR* pDir = 0;
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
					itr = _resources.find(type);
			
					// If the key does not exist, create it
					if(itr == _resources.end())
					{
						_resources[type] = Dictionary<String, BaseResource*>();
					}

					String path = dir;
					path.append('/');
					path += fullName;
					_resources[type][name] = new BaseResource(name, path, type);
				}
			} 
		
			// Close the directory
			closedir(pDir);
		}*/
	}

}	// Namespace