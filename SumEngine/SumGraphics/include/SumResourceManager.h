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
#include "SumFileSystem.h"
#include "SumBaseResource.h"
#include "SumResourceGroup.h"

#include <fstream>
#include <dirent.h>

namespace SumEngine
{
	/** \addtogroup Rendering
	*	@{
	*/
	/** \addtogroup Resources
	*	@{
	*/

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

		/** Get a resource from the resource map
		* @param
		*	name The name of the resource
		* @param
		*	fullName The resources fuull name
		* @return
		*	ResourceType* A pointer to the resource
		*/
		template <class ResourceType>
		ResourceType* getResourceById(const String& name, const String& fullName);
	
		/** Search the archive for information about a given file
		* @param 
		*	fullName The full filename of the file we are searching for
		* @return
		*	FileInfo Information related to the file
		*/
		FileInfo getFileInfo(const String& fullName);

		/** Add a resource factory to a specified group type
		* @param
		*	factory The factory pointer
		* @param
		*	resourceGroup The resource group to assign the factory
		*/
		void addResourceFactoryForGroup(ResourceFactory* factory, ResourceGroupType resourceGroup);

	private:
		/** Create resource file system
		*/
		void _createFileSystem();

		/** Initialize the resource groups for this system
		*/
		void _createResourceGroups();

		/** Detect the resource group that this resource request falls under
		* @param
		*	fullName The full name of the resource -- including extension
		* @return
		*	ResourceGroupType The corresponding resource group id
		*/
		ResourceGroupType _detectResourceGroup(const String& fullName);

		/** Fetch the corresponding resource group
		* @param
		*	resourceGroupType The type of the resource group
		* @return
		*	ResourceGroup* A pointer to the corresponding resource group
		*/
		ResourceGroup* _getResourceGroup(ResourceGroupType type);

		// Load the resource file names from configuration
		void loadFromConfig();

		// Load resource files from a directory
		void loadFromDir(const String& dir);

	private:
		// A resource pool
		//Dictionary<String, Dictionary<String, BaseResource*>> _resources;

		/** File System mapping resources to files
		*/
		FileSystem* _fileSystem;

		/** Array of possible resource groups
		*/
		ResourceGroup* _resourceGroups[MAX_RESOURCE_GROUPS];

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

	/** @} */
	/** @} */

	#include "SumResourceManager.inl"

}	// Namespace

#endif	// __SUMRESOURCEMANAGER_H__
