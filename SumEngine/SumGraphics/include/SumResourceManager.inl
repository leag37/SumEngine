//*************************************************************************************************
// Title: SumResourceManager.inl
// Author: Gael Huber
// Description: Manages all resources and resource types, loading and unloading of files
//*************************************************************************************************

//*************************************************************************************************
// Get a resource from the resource pool
//*************************************************************************************************
template <typename ResourceType>
ResourceType* ResourceManager::getResourceById(const String& name, const String& type)
{
	ResourceType* resource = 0;

	// Attempt to grab the resource
	if(_resources.find(type) != _resources.end())
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
	}

	return resource;
}