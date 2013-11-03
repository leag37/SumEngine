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

	// Constructor specifying position and extrema
	AxisAlignedBox(Vector inPosition, Vector inExtrema);

	// Copy constructor
	AxisAlignedBox(const AxisAlignedBox& value);

	// Destructor
	~AxisAlignedBox();

	// Assignment operator
	AxisAlignedBox& operator=(const AxisAlignedBox& value);

	// Equivalence operator
	SBOOL operator==(const AxisAlignedBox& value);

	// Non-equivalence operator
	SBOOL operator!=(const AxisAlignedBox& value);

	// Construct the box
	void update(Vector inPosition, Quaternion inRotation);

	// Set the position
	void setPosition(Vector inPosition);

	// Get the position
	Vector getPosition() const;

	// Set the extrema
	void setExtrema(Vector inExtrema);

	// Return the extrema
	Vector getExtrema() const;

	// Return the maximum points of the box
	Vector getMax() const;

	// Return the minimum points of the box
	Vector getMin() const;

private:
	// Construct the box
	void init();

private:
	// 3D position of this axis-aligned box
	Vector _position;

	// Vector describing the original extrema for the box along each axis in the positive direction of the identity orientation
	Vector _extrema;

	// Vector describing extrema of the bounding box for the current rotational angle
	Vector _rExtrema;
};

#endif // __SUMAXISALIGNEDBOX_H__