//*************************************************************************************************
// Title: SumLight.h
// Author: Gael Huber
// Description: Lighting types and descriptions
//*************************************************************************************************
#ifndef __SUMLIGHT_H__
#define __SUMLIGHT_H__

#include "SumRenderCore.h"

// A directional light
struct DirectionalLight
{
	// Constructor
	SUMINLINE DirectionalLight()
	{
		ZeroMemory(this, sizeof(this));
	}

	Float4 ambient;
	Float4 diffuse;
	Float4 specular;
	Float3 direction;
	SFLOAT pad;		// Pad the last float so we can set an array of lights
};

// Point light
struct PointLight
{
	SUMINLINE PointLight()
	{
		ZeroMemory(this, sizeof(this));
	}

	Float4 ambient;
	Float4 diffuse;
	Float4 specular;
	
	Float3 position;
	SFLOAT range;

	Float3 att;
	float pad;
};

// Spot light
struct SpotLight
{
	SUMINLINE SpotLight()
	{
		ZeroMemory(this, sizeof(this));
	}

	Float4 ambient;
	Float4 diffuse;
	Float4 specular;

	Float3 position;
	SFLOAT range;

	Float3 direction;
	SFLOAT spot;

	Float3 att;
	SFLOAT pad;
};

#endif