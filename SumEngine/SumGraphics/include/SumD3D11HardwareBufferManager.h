//*************************************************************************************************
// Title: SumD3D11HardwareBufferManager.h
// Author: Gael Huber
// Description: A D3D11-specific manager for all hardware buffers.
//*************************************************************************************************
#ifndef __SUMD3D11HARDWAREBUFFERMANAGER_H__
#define __SUMD3D11HARDWAREBUFFERMANAGER_H__

#include "SumHardwareBufferManager.h"
#include "SumD3D11Device.h"

namespace SumEngine
{
	/** \addtogroup Rendering
	*	@{
	*/

	class D3D11HardwareBufferManager : public HardwareBufferManager
	{
	public:
		/** Constructor
		* @param
		*	renderSystem The render system currently in use
		*/
		D3D11HardwareBufferManager(const RenderSystem* renderSystem);

	private:
		/** The D3D11Device
		*/
		D3D11Device _device;
	};

	/** @} */

}	// Namespace

#endif // __SUMD3D11HARDWAREBUFFERMANAGER_H__