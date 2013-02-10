//*************************************************************************************************
// Title: SumGeometry.cpp
// Author: Gael Huber
// Description: Utility functions to help generate standard pieces of geometry
//*************************************************************************************************
#include "SumGeometry.h"

namespace Geometry
{

// Create a box and attach it to the resource manager
Mesh* CreateBox(SFLOAT width, SFLOAT height, SFLOAT depth)
{
	// Create vertices
	Vertex v[24];
	SFLOAT w2 = 0.5f * width;
	SFLOAT h2 = 0.5f * height;
	SFLOAT d2 = 0.5f * depth;

	return 0;
}

}