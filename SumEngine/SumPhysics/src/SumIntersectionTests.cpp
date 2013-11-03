//*************************************************************************************************
// Title: SumIntersectionTests.cpp
// Author: Gael Huber
// Description: Defines the math for various collision tests
//*************************************************************************************************
#include "SumIntersectionTests.h"

//*************************************************************************************************
// Determine whether these two boxes intersect
//*************************************************************************************************
SBOOL TestCollision(const AxisAlignedBox& aabb1, const AxisAlignedBox& aabb2)
{
	// Get the minimum points
	Vector minA = aabb1.getMin();
	Vector maxA = aabb1.getMax();
	Vector minB = aabb2.getMin();
	Vector maxB = aabb2.getMax();

	// Now we will compare minB to minA and maxA to see whether any of the axes fall within the interval of A
	Vector temp1 = VectorGreaterThanEqual(minB, minA);
	Vector temp2 = VectorLessThanEqual(minB, maxA);
	Vector temp3 = VectorGreaterThanEqual(maxB, minA);
	Vector temp4 = VectorLessThanEqual(maxB, maxA);

	// Compare first two results to see whether minB overlaps any intervals of A
	temp1 = VectorAnd(temp1, temp2);

	// Compare second two results to see whether maxB overlaps any intervals of A
	temp3 = VectorAnd(temp3, temp4);

	// Combine results
	temp1 = VectorOr(temp1, temp3);

	// If the movemask is at least 7, all axes are matching
	SUINT mask = VectorMoveMask(temp1);
	return mask >= 7 ? true : false;
}

