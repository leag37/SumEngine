//*************************************************************************************************
// Title: SumD3D11Mesh.h
// Author: Gael Huber
// Description: A D3D11-supported mesh.
//*************************************************************************************************
#ifndef __SUMD3D11MESH_H__
#define __SUMD3D11MESH_H__

#include "SumMesh.h"
#include "SumD3D11Device.h"

namespace SumEngine
{
	/** \addtogroup Rendering
	*	@{
	*/
	/** \addtogroup Resources
	*	@{
	*/

	class D3D11Mesh : public Mesh
	{
	public:
		/** Default constructor 
		*/
		D3D11Mesh();

		/** Constructor specifying device
		* @param
		*	name The name of this resource
		* @param
		*	parentGroup The parent group for this resource
		* @param
		*	device The D3D11 Device used to initialize
		*/
		D3D11Mesh(const String& name, ResourceGroup* parentGroup, const D3D11Device& device);

	private:
		/** A copy of the device used to create the mesh
		*/
		D3D11Device _device;

	};

	/** @} */
	/** @} */

}	// Namespace

#endif // __SUMD3D11MESH_H__