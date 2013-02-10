//*************************************************************************************************
// Title: SumVertex.h
// Author: Gael Huber
// Description: Defines a vertex used for rendering data
//*************************************************************************************************
#ifndef __SUMVERTEX_H__
#define __SUMVERTEX_H__

#include "SumRenderCore.h"

class Vertex
{
public:
	// Constructor
	Vertex();

	// Constructor
	Vertex(const Float3& p);

	// Constructor
	Vertex(SFLOAT px, SFLOAT py, SFLOAT pz);

public:
	const Float3& position();
//	const Float3& normal();
//	const Float3& tangentU();
//	const Float2& texC();

private:
	Float3 _position;
//	Float3 _normal;
//	Float3 _tangentU;
//	Float2 _texC;
};

#include "SumVertex.inl"

#endif