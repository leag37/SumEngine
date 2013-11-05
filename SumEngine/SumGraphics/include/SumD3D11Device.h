//*************************************************************************************************
// Title: SumD3D11Device.h
// Author: Gael Huber
// Description: Encapsulation device for D3D device info. This is useful for both the actual device
//	and the immediate context.
//*************************************************************************************************
#ifndef __SUMD3D11DEVICE_H__
#define __SUMD3D11DEVICE_H__

#include "SumRenderCore.h"

namespace SumEngine
{
	/** \addtogroup Rendering
	*	@{
	*/

	class D3D11Device
	{
	public:
		/** Base constructor
		*/
		D3D11Device();

		/** Constructor
		* @param
		*	device The I	D3DDevice to encapsulate
		*/
		D3D11Device(ID3D11Device* device);

		/** Destructor
		*/
		~D3D11Device();

		/** Allow the device to act immediately as the ID3D11Device.
		* @return
		*	ID3D11Device The encapsulated device
		*/
		ID3D11Device* operator->() const;

		/** Return the immediate context
		* @return
		*	ID3D11DeviceContext The device's immediate context
		*/
		ID3D11DeviceContext* getImmediateContext();


	private:
		/** D3D device
		*/
		ID3D11Device* _device;

		/** Immediate context of the device
		*/
		ID3D11DeviceContext* _immediateContext; 
	};

	/** @} */

}	// Namespace

#include "SumD3D11Device.inl"

#endif // __SUMD3D11DEVICE_H__