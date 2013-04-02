//*************************************************************************************************
// Title: SumEffect.cpp
// Author: Gael Huber
// Description: Define a basic effect wrapper to group an effect and its variables.
//*************************************************************************************************
#include "SumEffect.h"

Effect::Effect(ID3D11Device* device, const String& filename)
	:	_effect(0)
{
	std::ifstream fin(filename.c_str(), std::ios::binary);

	fin.seekg(0, std::ios_base::end);
	int size = (int)fin.tellg();
	fin.seekg(0, std::ios_base::beg);
	Array<char> compiledShader(size);

	fin.read(&compiledShader[0], size);
	fin.close();

	HR(D3DX11CreateEffectFromMemory(&compiledShader[0], size, 0, device, &_effect));
}

Effect::~Effect()
{
	ReleaseCOM(_effect);
}


// Constructor
PrimitiveEffect::PrimitiveEffect(ID3D11Device* device, const String& filename)
	: Effect(device, filename)
{
	_technique = _effect->GetTechniqueByName("ColorTech");
	_viewProj = _effect->GetVariableByName("gViewProj")->AsMatrix();
	_world = _effect->GetVariableByName("gWorld")->AsMatrix();
}

// Destructor
PrimitiveEffect::~PrimitiveEffect()
{

}

BasicEffect::BasicEffect(ID3D11Device* device, const String& filename)
	: Effect(device, filename)
{
	_light1Tech = _effect->GetTechniqueByName("Light1");
	_light2Tech = _effect->GetTechniqueByName("Light2");
	_light3Tech = _effect->GetTechniqueByName("Light3");

	_light0TexTech = _effect->GetTechniqueByName("Light0Tex");
	_light1TexTech = _effect->GetTechniqueByName("Light1Tex");
	_light2TexTech = _effect->GetTechniqueByName("Light2Tex");
	_light3TexTech = _effect->GetTechniqueByName("Light3Tex");

	_viewProj = _effect->GetVariableByName("gViewProj")->AsMatrix();
	_worldInvTranspose = _effect->GetVariableByName("gWorldViewProj")->AsMatrix();
	_eyePosW = _effect->GetVariableByName("gEyePosW")->AsVector();
	_dirLights = _effect->GetVariableByName("gDirLights");
	_material = _effect->GetVariableByName("gMaterial");
	_diffuseMap = _effect->GetVariableByName("gDiffuseMap")->AsShaderResource();
}

BasicEffect::~BasicEffect()
{ }
