//*************************************************************************************************
// Title: SumD3D11MeshFactory.h
// Author: Gael Huber
// Description: Loads and creates D3D11 mesh resources
//*************************************************************************************************
#ifndef __SUMD3D11MESHFACTORY_H__
#define __SUMD3D11MESHFACTORY_H__

#include "SumMeshFactory.h"
#include "SumD3D11Mesh.h"
#include "SumD3D11RenderSystem.h"

namespace SumEngine
{
	/** \addtogroup Rendering
	*	@{
	*/
	/** \addtogroup Resources
	*	@{
	*/

	class D3D11MeshFactory : public MeshFactory
	{
	public:
		/** Default constructor
		*/
		D3D11MeshFactory();
		
		/** Constructor
		* @param
		*	name The name of this factory
		* @param
		*	device The D3D11 device used for constructing mesh from data
		*/
		D3D11MeshFactory(const String& name, D3D11RenderSystem* renderSystem);

		/** Destructor
		*/
		~D3D11MeshFactory();

		/** Create a resource
		* @param
		*	name The name of the resource
		* @param
		*	parentGroup The parent group for this resource (this should be passed in here due to the
		*	possibility of having multiple parentGroups.
		*/
		Resource* createResource(const String& name, ResourceGroup* parentGroup);

	private:
		/** The device used to initialize D3D11 resources
		*/
		D3D11Device _device;

	};

	/** @} */
	/** @} */

}	// Namespace

#endif // __SUMD3D11MESHFACTORY_H__