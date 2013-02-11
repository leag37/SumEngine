//*************************************************************************************************
// Title: Primitive.fx
// Author: Gael Huber
// Description: Primitive effect file to render an object. No particular support for color.
//*************************************************************************************************

cbuffer cbPerFrame
{
	float4x4 gViewProj;
};

cbuffer cbPerObject
{
	float4x4 gWorld;
};

struct VertexIn
{
	float3 Pos : POSITION;
};

struct VertexOut
{
	float4 PosH : SV_POSITION;
};

// Set rasterizer state
RasterizerState rsWireFrame
{
	FillMode = WireFrame;
};

VertexOut VS(VertexIn vIn)
{
	VertexOut vOut;

	// Transform to homogeneous clip space
	float4x4 wvp = mul(gWorld, gViewProj);
	vOut.PosH = mul(float4(vIn.Pos, 1.0f), wvp);

	// Return vertex
	return vOut;
}

float4 PS(VertexOut pIn) : SV_TARGET
{
	return float4(1.0f, 0.0f, 0.0f, 1.0f);
}

technique11 ColorTech
{
	pass P0
	{
		SetRasterizerState(rsWireFrame);
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
}
