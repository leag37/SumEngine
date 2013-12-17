//*************************************************************************************************
// Title: SumResourceFactory.h
// Author: Gael Huber
// Description: A resource factory that aids in the creation of various assets based on group. 
//*************************************************************************************************
#ifndef __SUMRESOURCEFACTORY_H__
#define __SUMRESOURCEFACTORY_H__

//#include "SumResourceGroup.h"
#include "SumInclude.h"
#include "SumString.h"

namespace SumEngine
{
	/** \addtogroup Rendering
	*	@{
	*/
	/** \addtogroup Resources
	*	@{
	*/

	class Resource;
	class ResourceGroup;

	class ResourceFactory
	{
	public:
		/** Default constructor
		*/
		ResourceFactory();

		/** Constructor specifying name
		* @param
		*	name The name for this factory
		*/
		ResourceFactory(const String& name);

		/** Destructor
		*/
		virtual ~ResourceFactory();

		/** Create a resource
		* @param
		*	name The name of the resource
		* @param
		*	parentGroup The parent group for this resource (this should be passed in here due to the
		*	possibility of having multiple parentGroups.
		*/
		virtual Resource* createResource(const String& name, ResourceGroup* parentGroup) = 0;

		/** Create a resource
		* @param
		*	name The name of the resource
		* @param
		*	parentGroup The parent group for this resource (this should be passed in here due to the
		*	possibility of having multiple parentGroups.
		* @param
		*	fullName The full filename associated with this resource
		*/
		virtual Resource* createResource(const String& name, ResourceGroup* parentGroup, const String& fullName) = 0;

	private:
		/** Resource factory name
		*/
		String _name;
	};

	/** @} */
	/** @} */

}	// Namespace

#endif // __SUMRESOURCEFACTORY_H__