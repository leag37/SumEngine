//*************************************************************************************************
// Title: LightingHelper.fx
// Author: Gael Huber
// Description: Helper functions for lighting.
//*************************************************************************************************

// Directional light
struct DirectionalLight
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
	float3 Direction;
	float pad;
};

// Point light
struct PointLight
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;

	float3 Position;
	float Range;

	float3 Att;
	float pad;
};

// Spot light
struct SpotLight
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;

	float3 Position;
	float Range;

	float3 Direction;
	float Spot;

	float3 Att;
	float pad;
};

// Material
struct Material
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;	// w = SpecPower
	float4 Reflect;
};

// Toon shader
float CalcDiffuse(float diffFactor)
{
	[flatten]
	if(diffFactor <= 0.0f)
	{
		diffFactor = 0.4f;
	}
	else if(diffFactor <= 0.5f)
	{
		diffFactor = 0.6f;
	}
	else if(diffFactor <= 1.0f)
	{
		diffFactor = 1.0f;
	}
	return diffFactor;
}

float CalcSpecular(float specFactor)
{
	[flatten]
	if(specFactor >= 0.0f && specFactor <= 1.0f)
	{
		specFactor = 0.0f;
	}
	else if(specFactor <= 0.8f)
	{
		specFactor = 0.5f;
	}
	else if(specFactor <= 1.0f)
	{
		specFactor = 0.8f;
	}
	return specFactor;
}

//*************************************************************************************************
// Computes the ambient, diffuse, and specular terms in the lighting equation from a directional
// light. We need to output the terms separately because later we will modify the individual terms.
//*************************************************************************************************
void ComputeDirectionalLight(Material mat, DirectionalLight L, float3 normal, float3 toEye,
	out float4 ambient, out float4 diffuse, out float4 spec)
{
	// Initialize outputs
	ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	spec = float4(0.0f, 0.0f, 0.0f, 0.0f);

	// The light vector aims in the opposite direction from the light rays travel
	float3 lightVec = -L.Direction;

	// Add the ambient term
	ambient = mat.Ambient * L.Ambient;

	// Add diffuse and specular term, provided the surface is in the line of sight of the light
	float diffuseFactor = dot(lightVec, normal);
	//diffuseFactor = CalcDiffuse(diffuseFactor);

	// Flatten to avoid dynamic branching
	[flatten]
	if(diffuseFactor > 0.0f)
	{
		float3 v = reflect(-lightVec, normal);
		float specFactor = pow(max(dot(v, toEye), 0.0f), mat.Specular.w);
		//specFactor = CalcSpecular(specFactor);

		diffuse = diffuseFactor * mat.Diffuse * L.Diffuse;
		spec = specFactor * mat.Specular * L.Specular;
	}
}

//*************************************************************************************************
// Computes the ambient, diffuse, and specular terms in the lighting equation from a point light.
// We need to output the terms separately because later we will modify the individual terms.
//*************************************************************************************************
void ComputePointLight(Material mat, PointLight L, float3 pos, float3 normal, float3 toEye,
	out float4 ambient, out float4 diffuse, out float4 spec)
{
	// Initialize outputs
	ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	spec = float4(0.0f, 0.0f, 0.0f, 0.0f);

	// The vector from the surface to the light
	float3 lightVec = L.Position - pos;

	// The distance from surface to light
	float d = length(lightVec);

	// Range test
	if(d > L.Range)
		return;

	// Normalize the light vector
	lightVec /= d;

	// Ambient term
	ambient = mat.Ambient * L.Ambient;

	// Add diffuse and specular term provided the surface is in line of sight of the light
	float diffuseFactor = dot(lightVec, normal);
	//diffuseFactor = CalcDiffuse(diffuseFactor);

	// Flatten to avoid dynamic branching
	[flatten]
	if(diffuseFactor > 0.0f)
	{
		float3 v = reflect(-lightVec, normal);
		float specFactor = pow(max(dot(v, toEye), 0.0f), mat.Specular.w);
		//specFactor = CalcSpecular(specFactor);

		diffuse = diffuseFactor * mat.Diffuse * L.Diffuse;
		spec = specFactor * mat.Specular * L.Specular;
	}

	// Attenuate
	float att = 1.0f / dot(L.Att, float3(1.0f, d, d * d));

	diffuse *= att;
	spec *= att;
}

//*************************************************************************************************
// Computes the ambient, diffuse and specular terms in the lighting equation from a spotlight. We
// need to output the terms separately because later we will modify the individual terms.
//*************************************************************************************************
void ComputeSpotLight(Material mat, SpotLight L, float3 pos, float3 normal, float3 toEye, 
	out float4 ambient, out float4 diffuse, out float4 spec)
{
	// Initialize outputs
	ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	spec = float4(0.0f, 0.0f, 0.0f, 0.0f);

	// The vector from the surface to the light
	float3 lightVec = L.Position - pos;

	// The distance from the surface to the light
	float d = length(lightVec);

	// Range test
	if(d > L.Range)
		return;

	// Normalize the light vector
	lightVec /= d;

	// Ambient term
	ambient = mat.Ambient * L.Ambient;

	// Add diffuse and specular term, provided the surface is in the line of sight of the light
	float diffuseFactor = dot(lightVec, normal);
	//diffuseFactor = CalcDiffuse(diffuseFactor);

	// Flatten to avoid dynamic branching
	if(diffuseFactor > 0.0f)
	{
		float3 v = reflect(-lightVec, normal);
		float specFactor = pow(max(dot(v, toEye), 0.0f), mat.Specular.w);
		//specFactor = CalcSpecular(specFactor);

		diffuse = diffuseFactor * mat.Diffuse * L.Diffuse;
		spec = specFactor * mat.Specular * L.Specular;
	}

	// Scale the spotlight factor and attenuate
	float spot = pow(max(dot(-lightVec, L.Direction), 0.0f), L.Spot);
	float att = spot / dot(L.Att, float3(1.0f, d, d * d));

	ambient *= spot;
	diffuse *= att;
	spec *= att;
}