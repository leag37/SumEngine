//*************************************************************************************************
// Title: SumAxisAlignedBox.cpp
// Author: Gael Huber
// Description: Defines an Axis-Aligned Bounding Box for a particular body.
//	An AABB is defined by a center point and a vector defining the extrema
//*************************************************************************************************
#include "SumAxisAlignedBox.h"

//*************************************************************************************************
// Constructor for the box
//*************************************************************************************************
AxisAlignedBox::AxisAlignedBox()
	:	_position(gVZero), _extrema(gVZero), _rExtrema(gVZero)
{ }

//*************************************************************************************************
// Constructor specifying position and extrema
//*************************************************************************************************
AxisAlignedBox::AxisAlignedBox(Vector inPosition, Vector inExtrema)
	:	_position(inPosition), _extrema(inExtrema), _rExtrema(inExtrema)
{ }

//*************************************************************************************************
// Copy constructor
//*************************************************************************************************
AxisAlignedBox::AxisAlignedBox(const AxisAlignedBox& value)
	:	_position(value._position), _extrema(value._extrema), _rExtrema(value._rExtrema)
{ }

//*************************************************************************************************
// Destructor
//*************************************************************************************************
AxisAlignedBox::~AxisAlignedBox()
{ }

//*************************************************************************************************
// Assignment operator
//*************************************************************************************************
AxisAlignedBox& AxisAlignedBox::operator=(const AxisAlignedBox& value)
{
	_position = value._position;
	_extrema = value._extrema;
	return *this;
}

//*************************************************************************************************
// Equivalence operator
//*************************************************************************************************
SBOOL AxisAlignedBox::operator==(const AxisAlignedBox& value)
{
	return (VectorCompareEqual(_position, value._position) && VectorCompareEqual(_extrema, value._extrema));
}

//*************************************************************************************************
// Non-equivalence operator
//*************************************************************************************************
SBOOL AxisAlignedBox::operator!=(const AxisAlignedBox& value)
{
	return (VectorCompareNotEqual(_position, value._position) || VectorCompareNotEqual(_extrema, value._extrema));
}

//*************************************************************************************************
// Construct the box
//*************************************************************************************************
void AxisAlignedBox::update(Vector inPosition, Quaternion inRotation)
{
	// First, update the position
	_position = inPosition;

	// Next rotate the extrema by the specified value
	Vector rExtrema = QuaternionTransformVector(_extrema, inRotation);

	// Negate the rotated extrema
	Vector nrExtrema = VectorNegate(rExtrema);

	// Choose the max values and assign to the rotated extrema value
	_rExtrema = VectorMax(rExtrema, nrExtrema);
}

//*************************************************************************************************
// Set the position
//*************************************************************************************************
void AxisAlignedBox::setPosition(Vector inPosition)
{
	_position = inPosition;
}

//*************************************************************************************************
// Get the position
//*************************************************************************************************
Vector AxisAlignedBox::getPosition() const
{
	return _position;
}

//*************************************************************************************************
// Set the extrema
//*************************************************************************************************
void AxisAlignedBox::setExtrema(Vector inExtrema)
{
	_extrema = inExtrema;
}

//*************************************************************************************************
// Return the extrema
//*************************************************************************************************
Vector AxisAlignedBox::getExtrema() const
{
	return _extrema;
}
