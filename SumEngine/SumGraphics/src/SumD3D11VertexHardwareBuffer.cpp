//*************************************************************************************************
// Title: SumD3D11VertexHardwareBuffer.cpp
// Author: Gael Huber
// Description: D3D11 specific implementation of a vertex hardware buffer
//*************************************************************************************************
#include "SumD3D11VertexHardwareBuffer.h"

namespace SumEngine
{
	//*************************************************************************************************
	// Constructor
	//*************************************************************************************************
	D3D11VertexHardwareBuffer::D3D11VertexHardwareBuffer()
		: VertexHardwareBuffer()
	{ }

	//*************************************************************************************************
	// Constructor
	// @param
	//	device D3D11 device
	// @param
	//	vertexSize The size in bytes of each vertex
	// @param
	//	numVertices The number of vertices in the buffer
	// @param
	//	usage The usage of the hardware buffer
	//*************************************************************************************************
	D3D11VertexHardwareBuffer::D3D11VertexHardwareBuffer(const D3D11Device& device, SUINT vertexSize, SUINT numVertices, HardwareBufferUsage usage)
		:	VertexHardwareBuffer(numVertices, vertexSize, usage),
			_device(device)
	{
		initBuffer();
	}

	//*************************************************************************************************
	// Destructor
	//*************************************************************************************************
	D3D11VertexHardwareBuffer::~D3D11VertexHardwareBuffer()
	{
		// Todo
	}

	//*************************************************************************************************
	// Implementation method to create the buffer
	//*************************************************************************************************
	void D3D11VertexHardwareBuffer::initBuffer()
	{
		// Create the buffer description
		D3D11_BUFFER_DESC bufferDesc;

		// Populate usage data
		switch(_usage)
		{
		case HBU_IMMUTABLE:
			bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
			bufferDesc.CPUAccessFlags = 0;
			break;

		case HBU_DYNAMIC:
			bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
			bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			break;

		case HBU_STAGING:
			bufferDesc.Usage = D3D11_USAGE_STAGING;
			bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
			break;

		case HBU_DEFAULT:
		default:
			bufferDesc.Usage = D3D11_USAGE_DEFAULT;
			bufferDesc.CPUAccessFlags = 0;
			break;
		}

		bufferDesc.ByteWidth = _vertexSize * _numVertices;
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.MiscFlags = 0;

		// Initialize the buffer
		_device->CreateBuffer(&bufferDesc, 0, &_buffer);
	}

	//*************************************************************************************************
	// Copy contents of this buffer to another buffer.
	// @param
	//	destBuffer The destination buffer
	//*************************************************************************************************
	void D3D11VertexHardwareBuffer::copyToBuffer(HardwareBuffer* destBuffer)
	{
		// Ensure the destination buffer is not immutable
		if(destBuffer->getUsage() != HBU_IMMUTABLE)
		{
			// Convert the buffer to a usable type
			D3D11VertexHardwareBuffer* vBuffer = reinterpret_cast<D3D11VertexHardwareBuffer*>(destBuffer);
			_device.getImmediateContext()->CopyResource(vBuffer->getID3D11Buffer(), _buffer);
		}
	}

	//*************************************************************************************************
	// Copy contents of the source buffer to this buffer.
	// @param
	//	srcBuffer The source buffer
	//*************************************************************************************************
	void D3D11VertexHardwareBuffer::copyFromBuffer(HardwareBuffer* srcBuffer)
	{
		// Ensure the destination buffer is not immutable
		if(_usage != HBU_IMMUTABLE)
		{
			// Convert the buffer to a usable type
			D3D11VertexHardwareBuffer* vBuffer = reinterpret_cast<D3D11VertexHardwareBuffer*>(srcBuffer);
			_device.getImmediateContext()->CopyResource(_buffer, vBuffer->getID3D11Buffer());
		}
	}

	//*************************************************************************************************
	// Lock the buffer to permit access to the data
	// @return
	//	void* Pointer to the locked data in memory
	//*************************************************************************************************
	void* D3D11VertexHardwareBuffer::lock()
	{
		// Early return for locked data
		if(_isLocked == true)
		{
			return 0;
		}
		
		// Lock the buffer
		_isLocked = true;

		// Map the sub resource
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		D3D11_MAP map;

		switch(_usage)
		{
		case HBU_IMMUTABLE:
			// Todo
			break;

		case HBU_DYNAMIC:
			map = D3D11_MAP_WRITE_DISCARD;
			break;

		case HBU_STAGING:
			map = D3D11_MAP_READ_WRITE;
			break;

		case HBU_DEFAULT:
			// Todo
			break;

		default:
			// Default behavior is to initialize to D3D11_MAP_WRITE_NO_OVERWRITE
			map = D3D11_MAP_WRITE_NO_OVERWRITE;
			break;
		}

		_device.getImmediateContext()->Map(_buffer, 0, map, 0, &mappedResource);

		return mappedResource.pData;
	}

	//*************************************************************************************************
	// Unlock the locked data
	//*************************************************************************************************
	void D3D11VertexHardwareBuffer::unlock()
	{
		// Unmap the resource
		_device.getImmediateContext()->Unmap(_buffer, 0);

		// Remove the lock
		_isLocked = false;
	}

	//************************************************************************************************* 
	// Return a pointer to the buffer
	// @return
	//	ID3D11Buffer* A pointer to the buffer
	//*************************************************************************************************
	ID3D11Buffer* D3D11VertexHardwareBuffer::getID3D11Buffer() const
	{
		return _buffer;
	}

}	// Namespace