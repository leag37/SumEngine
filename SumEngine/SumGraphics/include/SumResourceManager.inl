//*************************************************************************************************
// Title: SumResourceManager.inl
// Author: Gael Huber
// Description: Manages all resources and resource types, loading and unloading of files
//*************************************************************************************************

//*************************************************************************************************
// Get a resource from the resource map
// @param
//	name The name of the resource
// @param
//	fullName The resources fuull name
// @return
//	ResourceType* A pointer to the resource
//*************************************************************************************************
template <typename ResourceType>
ResourceType* ResourceManager::getResourceById(const String& name, const String& fullName)
{
	ResourceType* resource = 0;

	// Get the resource group type
	ResourceGroupType resourceGroupType = _detectResourceGroup(fullName);
	
	// Get the corresponding resource group
	ResourceGroup* group = _resourceGroups[resourceGroupType];

	// Fetch the resource
	resource = group->getResourceById<ResourceType>(name, fullName);

	// Check if the resource is loaded (otherwise load)
	// TODO: Support asynchronous loading
	if(resource->getStatus() == RESOURCE_STATUS_UNLOADED)
	{
		// Load the resource
		resource->load();
	}

	return resource;

	// Attempt to grab the resource
	/*if(_resources.find(type) != _resources.end())
	{
		Dictionary<String, BaseResource*>& resources = _resources[type];
		
		if(resources.find(name) != resources.end())
		{
			// The resource exists, so we can grab it
			resource = static_cast<ResourceType*>(resources[name]);

			// Is the resource is not loaded
			if(!resource->isLoaded())
			{
				BaseResource* oldResource = static_cast<BaseResource*>(resource);
				resource = new ResourceType(oldResource->name(), oldResource->filePath(), oldResource->fileType());
				delete oldResource;
				resources[name] = resource;
				resource->load();
			}
		}
	}*/

	//return resource;
}