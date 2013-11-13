//*************************************************************************************************
// Title: SumResourceFactory.h
// Author: Gael Huber
// Description: A resource factory that aids in the creation of various assets based on group. 
//*************************************************************************************************
#ifndef __SUMRESOURCEFACTORY_H__
#define __SUMRESOURCEFACTORY_H__

#include "SumResourceGroup.h"

namespace SumEngine
{
	/** \addtogroup Rendering
	*	@{
	*/
	/** \addtogroup Resources
	*	@{
	*/

	class ResourceFactory
	{
	public:
		/** Default constructor
		*/
		ResourceFactory();

		/** Destructor
		*/
		~ResourceFactory();

		/** Create a resource
		*/
		template <class ResourceType : public Resource>
		Resource* createResource();
	};

	/** @} */
	/** @} */

}	// Namespace

#endif // __SUMRESOURCEFACTORY_H__