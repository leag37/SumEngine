//*************************************************************************************************
// Title: SumResourceGroup.h
// Author: Gael Huber
// Description: A resource group holds all references to a particular resource type. Actual
//	resource creation is handled by a ResourceFactory which based on the type will return the
//	appropriate resource type for the ResourceGroup.
//
// For example, given the resource type RESOURCE_TYPE_MESH, the group would create a new resource
//	via ResourceFactory::createResource(RESOURCE_TYPE_MESH, name, etc.)
//*************************************************************************************************
#ifndef __SUMRESOURCEGROUP_H__
#define __SUMRESOURCEGROUP_H__

#include "SumDictionary.h"
#include "SumString.h"
#include "SumFileSystem.h"

namespace SumEngine
{
	/** \addtogroup Rendering
	*	@{
	*/
	/** \addtogroup Resources
	*	@{
	*/
	
	class Resource;
	class ResourceFactory;
	class ResourceManager;

// The maximum number of resource groups allowed
#define MAX_RESOURCE_GROUPS 4

	/** The allowed resource group types
	*/
	enum ResourceGroupType
	{
		RESOURCE_GROUP_TYPE_MESH = 0,
		RESOURCE_GROUP_TYPE_MATERIAL,
		RESOURCE_GROUP_TYPE_SHADER,
		RESOURCE_GROUP_TYPE_DEFAULT
	};

	class ResourceGroup
	{
	public:
		/** Default constructor
		*/
		ResourceGroup();

		/** Constructor
		* @param
		*	name The name of the resource group
		* @param
		*	type The type of resource group
		* @param
		*	parentManager The parent resource manager for this group
		*/
		ResourceGroup(const String& name, ResourceGroupType type, ResourceManager* parentManager);

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
	
		/** Set the resource factory instance for this group
		* @param
		*	resourceFactory The specialized factory for this group type
		*/
		void setResourceFactory(ResourceFactory* resourceFactory);

	private:
		/** Group name
		*/
		String _name;

		/** The group type
		*/
		ResourceGroupType _resourceGroupType;

		/** The resource group factory for this group
		*/
		ResourceFactory* _resourceFactory;

		/** Map of resources belonging to group
		*/
		Dictionary<String, Resource*> _resourceMap;

		/** Parent manger
		*/
		ResourceManager* _parentManager;
	};

	/** @} */
	/** @} */
}	// Namespace

#include "SumResourceGroup.inl"

#endif	// __SUMRESOURCEGROUP_H__