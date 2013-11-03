//*************************************************************************************************
// Title: SumIntersectionTests.h
// Author: Gael Huber
// Description: Defines the math for various collision tests
//*************************************************************************************************
#ifndef __SUMINTERSECTIONTESTS_H__
#define __SUMINTERSECTIONTESTS_H__

#include "SumAxisAlignedBox.h"

extern "C++"
{

// Determine whether these two boxes intersect
SBOOL TestCollision(const AxisAlignedBox& aabb1, const AxisAlignedBox& aabb2);

}

#endif // __SUMINTERSECTIONTESTS_H__