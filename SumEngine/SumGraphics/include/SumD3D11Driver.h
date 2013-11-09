//*************************************************************************************************
// Title: SumD3D11Driver.h
// Author: Gael Huber
// Description: A class representative of each graphic card/driver available to the engine.
//*************************************************************************************************
#ifndef __SUMD3D11DRIVER_H__
#define __SUMD3D11DRIVER_H__

#include "SumRenderCore.h"

namespace SumEngine
{
	/** \addtogroup Rendering
	*	@{
	*/

	class D3D11Driver
	{
	public:
		/** Default constructor
		*/
		D3D11Driver();

		/** Constructor
		* @param
		*	adapter The DXGIAdapter1 pointer representing the particular D3D driver
		*/
		D3D11Driver(IDXGIAdapter1* adapter);

		/** Destructor
		*/
		~D3D11Driver();

	private:
		/** The IDXGIAdapter
		*/
		IDXGIAdapter1* _adapter;

		/** The description for the adapter
		*/
		DXGI_ADAPTER_DESC1 _adapterDescription;

	};

	/** @} */

}	// Namespace

#endif // __SUMD3D11DRIVER_H__