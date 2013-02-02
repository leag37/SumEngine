#ifndef __SUMEFFECT_H__
#define __SUMEFFECT_H__

#pragma comment(lib, "d3dx11d.lib")
#pragma comment(lib, "Effects11D.lib")

#include "SumRenderCore.h"

class Effect
{
public:
	// Constructor
	Effect(ID3D11Device* device);

	// Destructor
	virtual ~Effect();

private:

protected:
	// Effect variable
	ID3DX11Effect* _effect;
};

#endif