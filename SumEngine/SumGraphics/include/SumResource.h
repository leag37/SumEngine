//*************************************************************************************************
// Title: SumResource.h
// Author: Gael Huber
// Description: An engine resource of any given type. This serves as a template for loading
//	specific resources.
//*************************************************************************************************
#ifndef __SUMRESOURCE_H__
#define __SUMRESOURCE_H__

#include "SumInclude.h"
#include "SumString.h"
#include "SumResourceGroup.h"

namespace SumEngine
{
	/** \addtogroup Rendering
	*	@{
	*/

	/** An enum representing the current status of this resource
	*/
	enum ResourceStatus
	{
		RESOURCE_STATUS_UNLOADED = 0,
		RESOURCE_STATUS_LOADING,
		RESOURCE_STATUS_LOADED,
		RESOURCE_STATUS_UNLOADING
	};

	class Resource
	{
	public:
		/** Default constructor
		*/
		Resource();

		/** Constructor
		* @param
		*	name The name of this resource
		* @param
		*	parentGroup The parent group for this resource
		*/
		Resource(const String& name, ResourceGroup* parentGroup);

		/** Destructor
		*/
		virtual ~Resource();

		/** Should this resource be automatically unloaded
		* @return
		*	SBOOL Returns true if this resource should be unloaded automatically when only 1 reference is left
		*/
		SBOOL getAutoUnload();

		/** Fetch the resource status
		* @return
		*	ResourceStatus The current status of this resource
		*/
		ResourceStatus getResourceStatus() const;

		/** Load the resource
		*/
		virtual void load() = 0;

		/** Unload the resource
		*/
		virtual void unload() = 0;

	protected:
		/** Resource name
		*/
		String _name;

		/** Resource status
		*/
		ResourceStatus _status;

		/** Parent resource group
		*/
		ResourceGroup* _parentGroup;
	};

	/** @} */

}	// Namespace

/*template <typename Type>
class Resource
{
public:
	// Constructor
	Resource();

	// Constructor
	Resource(const String& name, const String& filePath, const String& fileType);

	// Destructor
	virtual ~Resource();

	// Get the resource
	Type* resource();

	// Get the name
	const String& name() const;

	// Get the resource path
	const String& filePath() const;

	// Get the resource type
	const String& fileType() const;

	// Get whether the resource is loaded
	const SBOOL isLoaded() const;

	// Load the resource
	void load();

	// Free the resource
	void unload();

protected:
	// The loaded resource
	Type* _resource;

	// The resource name
	String _name;

	// The resource path
	String _filePath;

	// The resource type
	String _fileType;

	// Is the resource loaded
	SBOOL _isLoaded;
};

#include "SumResource.inl"
*/

#endif	// __SUMRESOURCE_H__