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
		virtual ~ResourceFactory();

		/** Create a resource
		*/
		virtual Resource* createResource() = 0;

	private:
		/** Resource factory name
		*/
		String _name;
	};

	/** @} */
	/** @} */

}	// Namespace

#endif // __SUMRESOURCEFACTORY_H__