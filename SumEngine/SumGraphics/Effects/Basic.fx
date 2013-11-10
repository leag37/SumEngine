//*************************************************************************************************
// Title: Basic.fx
// Author: Gael Huber
// Description: Basic effect that supports transformation and lighting
//*************************************************************************************************
#include "LightingHelper.fx"

// Per frame buffer
cbuffer cbPerFrame
{
	DirectionalLight gDirLight;
	PointLight gPointLight;
	float3 gEyePosW;
	float4x4 gViewProj;
};

// Per object buffer
cbuffer cbPerObject
{
	float4x4 gWorld;
	float4x4 gWorldInvTranspose;
	Material gMaterial;
};

struct VertexIn
{
	float3 PosL : POSITION;
	float3 NormalL : NORMAL;
};

struct VertexOut
{
	float4 PosH : SV_POSITION;
	float3 PosW : POSITION;
	float3 NormalW : NORMAL;
};

VertexOut VS(VertexIn vIn)
{
	VertexOut vOut;

	// Transform to world space
	vOut.PosW = mul(float4(vIn.PosL, 1.0f), gWorld).xyz;
	vOut.NormalW = mul(vIn.NormalL, (float3x3)gWorldInvTranspose);

	// Transform to homogeneous clip space
	float4x4 wvp = mul(gWorld, gViewProj);
	vOut.PosH = mul(float4(vIn.PosL, 1.0f), wvp);

	return vOut;
}

float4 PS(VertexOut pIn) : SV_TARGET
{
	// Interpolating normal can unnormalize it, so normalize it
	pIn.NormalW = normalize(pIn.NormalW);

	// The toEye vector is used in lighting
	float3 toEyeW = normalize(gEyePosW - pIn.PosW);

	// Lighting
	// Start with a sum of zero
	float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 spec = float4(0.0f, 0.0f, 0.0f, 0.0f);
	
	// TEMP
	float4 a, d, s;
	ComputeDirectionalLight(gMaterial, gDirLight, pIn.NormalW, toEyeW, a, d, s);
	ambient += a;
	diffuse += d;
	spec += s;

	ComputePointLight(gMaterial, gPointLight, pIn.PosW, pIn.NormalW, toEyeW, a, d, s);
	ambient += a;
	diffuse += d;
	spec += s;

	// Calculate color
	float4 litColor = ambient + diffuse + spec;

	// Common to take alpha from diffuse material
	litColor.a = gMaterial.Diffuse.a;

	return litColor;
}

fxgroup Meow
{
	technique11 Light1
	{
		pass P0
		{
			SetVertexShader(CompileShader(vs_5_0, VS()));
			SetGeometryShader(NULL);
			SetPixelShader(CompileShader(ps_5_0, PS()));
		}
	}
}