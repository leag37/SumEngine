//*************************************************************************************************
// Title: SumAxisAlignedBox.h
// Author: Gael Huber
// Description: Defines an Axis-Aligned Bounding Box for a particular body.
//	An AABB is defined by a center point and a vector defining the extrema
//*************************************************************************************************
#ifndef __SUMAXISALIGNEDBOX_H__
#define __SUMAXISALIGNEDBOX_H__

#include "SumInclude.h"
#include "SumMath.h"

class SUM_DECLSPEC_ALIGN_16 AxisAlignedBox
{
public:
	_SUM_ALIGN(AxisAlignedBox);

	// Constructor for the box
	AxisAlignedBox();

	// Destructor
	~AxisAlignedBox();

	// Construct the box
	void constructBox(Vector inPosition, Vector inExtrema);

	// Set the position
	void setPosition(Vector inPosition);

	// Get the position
	Vector getPosition() const;

	// Set the extrema
	void setExtrema(Vector inExtrema);

	// Return the extrema
	Vector getExtrema() const;

private:
	// 3D position of this axis-aligned box
	Vector _position;

	// Vector describing extrema for the box along each axis in the positive direction
	Vector _extrema;
};

#endif // __SUMAXISALIGNEDBOX_H__