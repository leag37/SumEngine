//*************************************************************************************************
// Title: SumMaterial.h
// Author: Gael Huber
// Description: Texture material descriptions
//*************************************************************************************************
#ifndef __SUMMATERIAL_H__
#define __SUMMATERIAL_H__

#include "SumRenderCore.h"

// Material structure
struct Material
{
	SUMINLINE Material()
	{
		ZeroMemory(this, sizeof(this));
	}

	Float4 ambient;
	Float4 diffuse;
	Float4 specular;
	Float4 reflect;
};

#endif