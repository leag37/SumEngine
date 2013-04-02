//*************************************************************************************************
// Title: SumGeometry.cpp
// Author: Gael Huber
// Description: Utility functions to help generate standard pieces of geometry
//*************************************************************************************************
#include "SumGeometry.h"
#include "SumRenderManager.h"

namespace Geometry
{

//*************************************************************************************************
// Create a box and attach it to the resource manager
//*************************************************************************************************
Mesh* CreateBox(const String& name, SFLOAT width, SFLOAT height, SFLOAT depth)
{
	// Mesh data
	MeshData data;

	// Create vertices
	Array<Vertex> v = Array<Vertex>(24);
	SFLOAT w2 = 0.5f * width;
	SFLOAT h2 = 0.5f * height;
	SFLOAT d2 = 0.5f * depth;

	// Fill in vertex data
	v.push_back(Vertex(Float3(+w2, +h2, -d2), Float3(+0.333333f, +0.666667f, -0.666667f)));
	v.push_back(Vertex(Float3(-w2, +h2, -d2), Float3(-0.816497f, +0.408248f, -0.408248f)));
	v.push_back(Vertex(Float3(-w2, +h2, +d2), Float3(-0.333333f, +0.666667f, +0.666667f)));
	v.push_back(Vertex(Float3(+w2, +h2, +d2), Float3(+0.816497f, +0.408248f, +0.408248f)));
	v.push_back(Vertex(Float3(+w2, -h2, -d2), Float3(+0.666667f, -0.666667f, -0.333333f)));
	v.push_back(Vertex(Float3(-w2, -h2, -d2), Float3(-0.408248f, -0.408248f, -0.816497f)));
	v.push_back(Vertex(Float3(-w2, -h2, +d2), Float3(-0.666667f, -0.666667f, +0.333333f)));
	v.push_back(Vertex(Float3(+w2, -h2, +d2), Float3(+0.408248f, -0.408248f, +0.816497f)));

	// Assign to data
	data.vertices = v;

	// Create the indicies
	Array<SUINT> i = Array<SUINT>(36);
	i.push_back(0);	i.push_back(1);	i.push_back(2);
	i.push_back(0);	i.push_back(2);	i.push_back(3);
	i.push_back(0);	i.push_back(4);	i.push_back(5);
	i.push_back(0);	i.push_back(5);	i.push_back(1);
	i.push_back(1);	i.push_back(5);	i.push_back(6);
	i.push_back(1);	i.push_back(6);	i.push_back(2);
	i.push_back(2);	i.push_back(6);	i.push_back(7);
	i.push_back(2);	i.push_back(7);	i.push_back(3);
	i.push_back(3);	i.push_back(7);	i.push_back(4);
	i.push_back(3);	i.push_back(4);	i.push_back(0);
	i.push_back(4);	i.push_back(7);	i.push_back(6);
	i.push_back(4);	i.push_back(6);	i.push_back(5);
	

	// Assign the indices
	data.indices = i;

	// Create the mesh
	Mesh* mesh = new Mesh(name);
	CreateMeshFromData(data, mesh);

	return mesh;
}

//*************************************************************************************************
// Create a mesh from mesh data
//*************************************************************************************************
void CreateMeshFromData(const MeshData& data, Mesh* pOut)
{
	// Buffers
	ID3D11Buffer* vertexBuffer = 0;
	ID3D11Buffer* indexBuffer = 0;

	CreateBuffersFromData(data, &vertexBuffer, &indexBuffer);

	// Set mesh data
	pOut->vertexBuffer(vertexBuffer);
	pOut->indexBuffer(indexBuffer);
	pOut->vertexCount(data.vertices.getCount());
	pOut->indexCount(data.indices.getCount());
}

//*************************************************************************************************
// Create buffers from data
//*************************************************************************************************
void CreateBuffersFromData(const MeshData& data, ID3D11Buffer** vertexBuffer, ID3D11Buffer** indexBuffer)
{	
	// Get the device
	ID3D11Device* device = RenderManager::getSingletonPtr()->d3dDevice();

	// Create the buffer description for vertex buffer
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_IMMUTABLE;
	bd.ByteWidth = sizeof(Vertex) * data.vertices.getCount();
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	
	// Vertex resource data
	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = &data.vertices[0];
	HR(device->CreateBuffer(&bd, &initData, vertexBuffer));

	// Alter buffer description for index buffer
	bd.ByteWidth = sizeof(SUINT) * data.indices.getCount();
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	
	// Index resource data
	initData.pSysMem = &data.indices[0];
	HR(device->CreateBuffer(&bd, &initData, indexBuffer));
}

} // namespace Geometry