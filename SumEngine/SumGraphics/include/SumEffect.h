//*************************************************************************************************
// Title: SumEffect.h
// Author: Gael Huber
// Description: Define a basic effect wrapper to group an effect and its variables.
//
// TODO: Switch over to use SumEngine data structures intead of STL
// TODO: Come up with a better way to store effect names -> probably from configuration
// TODO: Split effects out into multiple files
// TODO: Move inline functions to .inl files
// TODO: Make effect more generic by adding technique and variable maps
//*************************************************************************************************
#ifndef __SUMEFFECT_H__
#define __SUMEFFECT_H__

#include "SumRenderCore.h"
#include "SumArray.h"
#include <fstream>

// Base class for all effects
class Effect
{
public:
	// Constructor
	Effect(ID3D11Device* device, const String& filename);

	// Destructor
	virtual ~Effect();

private:

protected:
	// Effect variable
	ID3DX11Effect* _effect;
};

// A primitive effect with support for position only
class PrimitiveEffect : public Effect
{
public:
	// Constructor
	PrimitiveEffect(ID3D11Device* device, const String& filename);

	// Destructor
	~PrimitiveEffect();

private:
	// Technique
	ID3DX11EffectTechnique* _technique;

	// Camera buffer
	ID3DX11EffectMatrixVariable* _viewProj;
	ID3DX11EffectMatrixVariable* _world;

public:
	SUMINLINE ID3DX11EffectTechnique* technique()
	{
		return _technique;
	}

	SUMINLINE ID3DX11EffectMatrixVariable* viewProj()
	{
		return _viewProj;
	}

	SUMINLINE ID3DX11EffectMatrixVariable* world()
	{
		return _world;
	}
};

// A basic effect supporting up to 3 light sources
class BasicEffect : public Effect
{
public:
	// Constructor
	BasicEffect(ID3D11Device* device, const String& filename);

	// Destructor
	~BasicEffect();

	void setViewProj(const Matrix& m)
	{
		_viewProj->SetMatrix(reinterpret_cast<const float*>(&m));
	}
	void setWorld(const Matrix& m)
	{
		_world->SetMatrix(reinterpret_cast<const float*>(&m));
	}
	void setWorldInvTranspose(const Matrix& m)
	{
		_worldInvTranspose->SetMatrix(reinterpret_cast<const float*>(&m));
	}
	void setTexTransform(const Matrix& m);
	void setEyePosW(const Float3& v);
	void setDirLights(const DirectionalLight* lights);
	void setMaterial(const Material& material);
	void setDiffuseMap(ID3D11ShaderResourceView* tex);

	ID3DX11EffectTechnique* light1Tech();

private:
	// Light techniques
	ID3DX11EffectTechnique* _light1Tech;
	ID3DX11EffectTechnique* _light2Tech;
	ID3DX11EffectTechnique* _light3Tech;

	ID3DX11EffectTechnique* _light0TexTech;
	ID3DX11EffectTechnique* _light1TexTech;
	ID3DX11EffectTechnique* _light2TexTech;
	ID3DX11EffectTechnique* _light3TexTech;

	// Effect variables
	ID3DX11EffectMatrixVariable* _viewProj;
	ID3DX11EffectMatrixVariable* _world;
	ID3DX11EffectMatrixVariable* _worldInvTranspose;
	ID3DX11EffectVectorVariable* _eyePosW;
	ID3DX11EffectVariable* _dirLights;
	ID3DX11EffectVariable* _material;
	ID3DX11EffectShaderResourceVariable* _diffuseMap;
};

#include "SumEffect.inl"

#endif