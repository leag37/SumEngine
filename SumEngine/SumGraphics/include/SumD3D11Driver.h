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

		/** Get the adapter
		* @return
		*	IDXGIAdapter1 The adapter to be used for the driver
		*/
		IDXGIAdapter1* getAdapter() const;

		/** Get the dedicated system memory of this adapter
		* @return
		*	SUINT The dedicated system memory
		*/
		SUINT getDedicatedSystemMemory() const;

		/** Get the dedicated video memory of this adapter
		* @return
		*	SUINT The dedicated video memory
		*/
		SUINT getDedicatedVideoMemory() const;

		/** Get the shared system memory of this adapter
		* @return
		*	SUINT The shared system memory
		*/
		SUINT getSharedSystemMemory() const;

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