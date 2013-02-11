//*************************************************************************************************
// Title: SumGeometry.h
// Author: Gael Huber
// Description: Utility functions to help generate standard pieces of geometry
//
// TODO: Improve box mesh (can be simplified to 8 vertices...)
//*************************************************************************************************
#ifndef __SUMGEOMETRY_H__
#define __SUMGEOMETRY_H__

#include "SumRenderCore.h"

class Mesh;

namespace Geometry
{
	// Create a box and attach it to the resource manager
	Mesh* CreateBox(const String& name, SFLOAT width, SFLOAT height, SFLOAT depth);

	// Create a mesh from mesh data
	void CreateMeshFromData(const MeshData& data, Mesh* pOut);
}

#endif