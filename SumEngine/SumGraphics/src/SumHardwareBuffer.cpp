//*************************************************************************************************
// Title: SumHardwareBuffer.cpp
// Author: Gael Huber
// Description: Defines a basic hardware buffer for all buffers to inherit from. 
//*************************************************************************************************
#include "SumHardwareBuffer.h"

namespace SumEngine
{
	//*************************************************************************************************
	// Default constructor
	//*************************************************************************************************
	HardwareBuffer::HardwareBuffer()
		:	_isLocked(false)
	{ }

	//*************************************************************************************************
	// Copy constructor
	//*************************************************************************************************
	HardwareBuffer::HardwareBuffer(const HardwareBuffer& hb)
	{ }

	//*************************************************************************************************
	// Constructor
	// @param
	//	usage The usage type of this buffer
	//*************************************************************************************************
	HardwareBuffer::HardwareBuffer(HardwareBufferUsage usage)
		:	_usage(usage),
			_isLocked(false)
	{ }

	//*************************************************************************************************
	// Destructor
	//*************************************************************************************************
	HardwareBuffer::~HardwareBuffer()
	{ }

	//*************************************************************************************************
	// Is this hardware buffer locked
	// @return
	//	SBOOL The lock status of the buffer
	//*************************************************************************************************
	SBOOL HardwareBuffer::isLocked() const
	{
		return _isLocked;
	}

	//*************************************************************************************************
	// Get the usage of the buffer
	// @return
	//	HardwareBufferUsage The usage type of the buffer
	//*************************************************************************************************
	HardwareBufferUsage HardwareBuffer::getUsage() const
	{
		return _usage;
	}

}	// Namespace