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
	:	_position(VectorZero()), _extrema(VectorZero())
{ }

//*************************************************************************************************
// Constructor specifying position and extrema
//*************************************************************************************************
AxisAlignedBox::AxisAlignedBox(Vector inPosition, Vector inExtrema)
	:	_position(inPosition), _extrema(inExtrema)
{ }

////*************************************************************************************************
//// Copy constructor
////*************************************************************************************************
//AxisAlignedBox::AxisAlignedBox(const AxisAlignedBox& value);
//
////*************************************************************************************************
//// Destructor
////*************************************************************************************************
//AxisAlignedBox::~AxisAlignedBox();
//
////*************************************************************************************************
//// Assignment operator
////*************************************************************************************************
//AxisAlignedBox& AxisAlignedBox::operator=(const AxisAlignedBox& value);
//
////*************************************************************************************************
//// Equivalence operator
////*************************************************************************************************
//SBOOL AxisAlignedBox::operator==(const AxisAlignedBox& value);
//
////*************************************************************************************************
//// Non-equivalence operator
////*************************************************************************************************
//SBOOL AxisAlignedBox::operator!=(const AxisAlignedBox& value);
//
////*************************************************************************************************
//// Construct the box
////*************************************************************************************************
//void AxisAlignedBox::constructBox(Vector inPosition, Vector inExtrema);
//
////*************************************************************************************************
//// Set the position
////*************************************************************************************************
//void AxisAlignedBox::setPosition(Vector inPosition);
//
////*************************************************************************************************
//// Get the position
////*************************************************************************************************
//Vector AxisAlignedBox::getPosition() const;
//
////*************************************************************************************************
//// Set the extrema
////*************************************************************************************************
//void AxisAlignedBox::setExtrema(Vector inExtrema);
//
////*************************************************************************************************
//// Return the extrema
////*************************************************************************************************
//Vector AxisAlignedBox::getExtrema() const
