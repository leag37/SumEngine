//*************************************************************************************************
// Title: SumMeshFactory.h
// Author: Gael Huber
// Description: A resource factory that creates meshes.
//*************************************************************************************************
#ifndef __SUMMESHFACTORY_H__
#define __SUMMESHFACTORY_H__

#include "SumResourceFactory.h"

namespace SumEngine
{
	/** \addtogroup Rendering
	*	@{
	*/
	/** \addtogroup Resources
	*	@{
	*/

	class MeshFactory : public ResourceFactory
	{
	public:
		/** Default constructor
		*/
		MeshFactory();

		/** Constructor specifying name
		* @param
		*	name The name for this factory
		*/
		MeshFactory(const String& name);

		/** Destructor
		*/
		virtual ~MeshFactory();
	};

	/** @} */
	/** @} */

}	// Namespace

#endif // __SUMMESHFACTORY_H__