//*************************************************************************************************
// Title: SumD3D11Device.inl
// Author: Gael Huber
// Description: Encapsulation device for D3D device info. This is useful for both the actual device
//	and the immediate context.
//*************************************************************************************************

namespace SumEngine
{

	/** Allow the device to act immediately as the ID3D11Device.
	* @return
	*	ID3D11Device The encapsulated device
	*/
	SUMINLINE ID3D11Device* D3D11Device::operator->() const
	{
		return _device;
	}

	/** Return the immediate context
	* @return
	*	ID3D11DeviceContext The device's immediate context
	*/
	SUMINLINE ID3D11DeviceContext* D3D11Device::getImmediateContext()
	{
		return _immediateContext;
	}
}