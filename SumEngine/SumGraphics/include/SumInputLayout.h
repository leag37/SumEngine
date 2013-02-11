//*************************************************************************************************
// Title: SumInputLayout.h
// Author: Gael Huber
// Description: Encompasses various vertex types.
//
// TODO: Make input layout system more intelligent about initialization.
// TODO: Make load from config.
//*************************************************************************************************
#ifndef __SUMINPUTLAYOUT_H__
#define __SUMINPUTLAYOUT_H__

#include "SumRenderCore.h"
#include "SumEffectsManager.h"

namespace VertexTypes
{
	// Position
	struct Pos
	{
		Float3 pos;
	};

	// Position normal (used for strictly lighting)
	struct PosNormal
	{
		Float3 pos;
		Float3 normal;
	};

	// Standard vertex
	struct Basic32
	{
		Float3 pos;
		Float3 normal;
		Float2 tex;
	};
}

class InputLayoutDesc
{
public:
	// Init like const int A::a[4] = {0, 1, 2, 3}; in .cpp file
	static const D3D11_INPUT_ELEMENT_DESC Pos[1];
	static const D3D11_INPUT_ELEMENT_DESC PosNormal[2];
	static const D3D11_INPUT_ELEMENT_DESC Basic32[3];
};

class InputLayouts
{
public:
	static void InitAll(ID3D11Device* device);
	static void DestroyAll();

	static ID3D11InputLayout* Pos;
	static ID3D11InputLayout* PosNormal;
	static ID3D11InputLayout* Basic32;
};

#endif