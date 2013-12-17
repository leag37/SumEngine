//*************************************************************************************************
// Title: SumD3D11Mesh.cpp
// Author: Gael Huber
// Description: A D3D11-supported mesh.
//*************************************************************************************************
#include "SumD3D11Mesh.h"

namespace SumEngine
{

	//*************************************************************************************************
	// Default constructor 
	//*************************************************************************************************
	D3D11Mesh::D3D11Mesh()
		:	Mesh()
	{ }

	//*************************************************************************************************
	// Constructor specifying device
	// @param
	//	name The name of this resource
	// @param
	//	parentGroup The parent group for this resource
	// @param
	//	device The D3D11 Device used to initialize
	//*************************************************************************************************
	D3D11Mesh::D3D11Mesh(const String& name, ResourceGroup* parentGroup, const D3D11Device& device)
		:	Mesh(name, parentGroup),
			_device(device)
	{ }

	//*************************************************************************************************
	// Constructor
	// @param
	//	name The name of this resource
	// @param
	//	parentGroup The parent group for this resource
	// @param
	//	fullName The full name of the file associated with this resource
	//*************************************************************************************************
	D3D11Mesh::D3D11Mesh(const String& name, ResourceGroup* parentGroup, const String& fullName, const D3D11Device& device)
		:	Mesh(name, parentGroup, fullName),
			_device(device)
	{ }

}	// Namespace