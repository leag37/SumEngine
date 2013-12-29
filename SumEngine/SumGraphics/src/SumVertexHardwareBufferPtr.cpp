//*************************************************************************************************
// Title: SumVertexHardwareBufferPtr.cpp
// Author: Gael Huber
// Description: Shared pointer for VertexHardwareBuffer objects
//*************************************************************************************************	
#include "SumVertexHardwareBuffer.h"

namespace SumEngine
{
	//*************************************************************************************************	
	// Constructor
	// @param
	//	vhb The vertex hardware buffer
	//*************************************************************************************************	
	VertexHardwareBufferPtr::VertexHardwareBufferPtr(VertexHardwareBuffer* vbh)
		:	SharedPtr(vbh)
	{ }

	//*************************************************************************************************	
	// Destructor
	//*************************************************************************************************	
	VertexHardwareBufferPtr::~VertexHardwareBufferPtr()
	{ }

}	 // Namespace