//*************************************************************************************************
// Title: SumEffect.h
// Author: Gael Huber
// Description: Define a basic effect wrapper to group an effect and its variables.
//
// TODO: Switch over to use SumEngine data structures intead of STL
// TODO: Come up with a better way to store effect names -> probably from configuration
// TODO: Split effects out into multiple files
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
	Effect(ID3D11Device* device, const std::string& filename);

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
	PrimitiveEffect(ID3D11Device* device, const std::string& filename);

	// Destructor
	~PrimitiveEffect();

private:
	// Technique
	ID3DX11EffectTechnique* _technique;

	// Camera buffer
	ID3DX11EffectMatrixVariable* _worldViewProj;

public:
	SUMINLINE ID3DX11EffectTechnique* technique()
	{
		return _technique;
	}

	SUMINLINE ID3DX11EffectMatrixVariable* worldViewProj()
	{
		return _worldViewProj;
	}
};

// A basic effect supporting up to 3 light sources
class BasicEffect : public Effect
{
public:
	// Constructor
	BasicEffect(ID3D11Device* device, const std::string& filename);

	// Destructor
	~BasicEffect();

	void setWorldViewProj(const Matrix& m);
	void setWorld(const Matrix& m);
	void setWorldInvTranspose(const Matrix& m);
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

};

#include "SumEffect.inl"

#endif