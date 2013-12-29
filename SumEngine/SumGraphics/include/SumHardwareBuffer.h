//*************************************************************************************************
// Title: SumHardwareBuffer.h
// Author: Gael Huber
// Description: Defines a basic hardware buffer for all buffers to inherit from. 
//*************************************************************************************************
#ifndef __SUMHARDWAREBUFFER_H__
#define __SUMHARDWAREBUFFER_H__

#include "SumInclude.h"

namespace SumEngine
{
	/** \addtogroup Rendering
	*	@{
	*/

	/** An enumeration to encapsulate hardware buffer usage options
	*/
	enum HardwareBufferUsage
	{
		HBU_DEFAULT = 0,
		HBU_IMMUTABLE,
		HBU_DYNAMIC,
		HBU_STAGING
	};

	class HardwareBuffer
	{
	protected:
		/** Default constructor
		*/
		HardwareBuffer();

		/** Copy constructor
		*/
		HardwareBuffer(const HardwareBuffer& hb);

	public:
		/** Constructor
		* @param
		*	usage The usage type of this buffer
		*/
		HardwareBuffer(HardwareBufferUsage usage);

		/** Destructor
		*/
		~HardwareBuffer();

	protected:
		/** Implementation method to create the buffer
		*/
		virtual void initBuffer() = 0;

	protected:
		/** The size of this buffer
		*/
		SUINT _bufferSize;

		/** The usage of this buffer
		*/
		HardwareBufferUsage _usage;
	};

	/** @} */

}	// Namespace

#endif // __SUMHARDWAREBUFFER_H__