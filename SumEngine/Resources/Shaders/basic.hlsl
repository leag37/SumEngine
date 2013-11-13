// Title: basic.hlsl
// Author: Gael Huber

// Per object buffer
cbuffer cbPerObject
{
	float4x4 gWorldViewProj;		// World-view-projection matrix
};

// Structure passed into vertex shader
struct VertexIn
{
	float4 Pos : POSITION;	
};

// Structure returned from the vertex shader
struct VertexOut
{
	float4 Pos : SV_POSITION;	
};

// Vertex shader
VertexOut basic_vs(VertexIn vIn)
{
	VertexOut vOut;

	// Transform the in-position to the out position
	vOut.Pos = mul(vIn.pos, gWorldViewProj);

	return vOut;
}

// Pixel shader
float4 basic_ps(VertexOut pIn) : SV_TARGET
{
	// Return the color as a function of the position
	float4 color = pIn.Pos;
	color.a = 1.0;
}