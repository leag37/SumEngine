//*************************************************************************************************
// Title: SumResourceGroup.inl
// Author: Gael Huber
// Description: A resource group holds all references to a particular resource type. Actual
//	resource creation is handled by a ResourceFactory which based on the type will return the
//	appropriate resource type for the ResourceGroup.
//
// For example, given the resource type RESOURCE_TYPE_MESH, the group would create a new resource
//	via ResourceFactory::createResource(RESOURCE_TYPE_MESH, name, etc.)
//*************************************************************************************************

namespace SumEngine
{
	/** Get a resource from the resource map
	* @param
	*	name The name of the resource
	* @param
	*	fullName The resources fuull name
	* @return
	*	ResourceType* A pointer to the resource
	*/
	template <class ResourceType>
	ResourceType* ResourceGroup::getResourceById(const String& name, const String& fullName)
	{
		ResourceType* resource = 0;

		// First, check if we have this value in our dictionary
		Dictionary<String, Resource*>::Iterator itr = _resourceMap.find(fullName);

		// If we have the value, store it
		if(itr != _resourceMap.end())
		{
			resource = itr->getValue();
		}
		// Not found, so we have to create it and insert it into the tree
		else
		{
			// We must first find the file info
			FileInfo info = _parentManager->getFileInfo(fullName);

			// TODO:
			// Create the resource in question
			//_resourceFactory->create<ResourceType>(name, info);
		}

		return resource;
	}

}	// Namespace