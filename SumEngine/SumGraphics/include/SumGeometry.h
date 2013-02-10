//*************************************************************************************************
// Title: SumGeometry.h
// Author: Gael Huber
// Description: Utility functions to help generate standard pieces of geometry
//*************************************************************************************************
#ifndef __SUMGEOMETRY_H__
#define __SUMGEOMETRY_H__

#include "SumRenderCore.h"

class Mesh;

namespace Geometry
{
	// Create a box and attach it to the resource manager
	Mesh* CreateBox(SFLOAT width, SFLOAT height, SFLOAT depth);

}

#endif