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

		/** Copy contents of this buffer to another buffer.
		* @param
		*	destBuffer The destination buffer
		*/
		virtual void copyToBuffer(HardwareBuffer* destBuffer) = 0;

		/** Copy contents of the source buffer to this buffer.
		* @param
		*	srcBuffer The source buffer
		*/
		virtual void copyFromBuffer(HardwareBuffer* srcBuffer) = 0;

		/** Lock the buffer to permit access to the data
		* @return
		*	void* Pointer to the locked data in memory
		*/
		virtual void* lock() = 0;

		/** Unlock the locked data
		*/
		virtual void unlock() = 0;

		/** Is this hardware buffer locked
		* @return
		*	SBOOL The lock status of the buffer
		*/
		SBOOL isLocked() const;

		/** Get the usage of the buffer
		* @return
		*	HardwareBufferUsage The usage type of the buffer
		*/
		HardwareBufferUsage getUsage() const;

	protected:
		/** Implementation method to create the buffer
		*/
		virtual void initBuffer() = 0;

	protected:
		/** The usage of this buffer
		*/
		HardwareBufferUsage _usage;

		/** Is the buffer locked
		*/
		SBOOL _isLocked;
	};

	/** @} */

}	// Namespace

#endif // __SUMHARDWAREBUFFER_H__