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

	_viewProj = _effect->GetVariableByName("gViewProj")->AsMatrix();
	_world = _effect->GetVariableByName("gWorld")->AsMatrix();
	_worldInvTranspose = _effect->GetVariableByName("gWorldInvTranspose")->AsMatrix();
	_eyePosW = _effect->GetVariableByName("gEyePosW")->AsVector();
	_dirLight = _effect->GetVariableByName("gDirLight");
	_pointLight = _effect->GetVariableByName("gPointLight");
	_material = _effect->GetVariableByName("gMaterial");
}

BasicEffect::~BasicEffect()
{ }
