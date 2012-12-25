//*************************************************************************************************
// Title: SumMiscMath.h
// Author: Gael Huber
// Description: Miscellaneous mathematics functions
//*************************************************************************************************
#ifndef __SUMMISCMATH_H__
#define __SUMMISCMATH_H__

#include "SumMath.h"

//Vector VectorASin(const Vector v);
//Vector VectorACos(const Vector v);
//Vector VectorATan(const Vector v);
Vector VectorSin(const Vector v);
Vector VectorCos(const Vector v);
//Vector VectorTan(const Vector v);
//Vector VectorSinh(const Vector v);
//Vector VectorCosh(const Vector v);
//Vector VectorTanh(const Vector v);
void VectorSinCos(Vector* pSin, Vector* pCos, const Vector v);
//Vector VectorPow(const Vector v1, const Vector v2);


// sin(V) ~= V - V^3 / 3! + V^5 / 5! - V^7 / 7! + V^9 / 9! - V^11 / 11! + V^13 / 13! - 
//           V^15 / 15! + V^17 / 17! - V^19 / 19! + V^21 / 21! - V^23 / 23! (for -PI <= V < PI)

// cos(V) ~= 1 - V^2 / 2! + V^4 / 4! - V^6 / 6! + V^8 / 8! - V^10 / 10! + V^12 / 12! - 
//           V^14 / 14! + V^16 / 16! - V^18 / 18! + V^20 / 20! - V^22 / 22! (for -PI <= V < PI)

// Cody and Waite algorithm to compute tangent.

// asin(V) = V * (C0 + C1 * V + C2 * V^2 + C3 * V^3 + C4 * V^4 + C5 * V^5) + (1 - V) * rsq(1 - V) * 
//           V * (C6 + C7 * V + C8 * V^2 + C9 * V^3 + C10 * V^4 + C11 * V^5)

// acos(V) = PI / 2 - asin(V)

// Cody and Waite algorithm to compute inverse tangent.

// Return the inverse tangent of Y / X in the range of -Pi to Pi with the following exceptions:
//     Y == 0 and X is Negative         -> Pi with the sign of Y
//     y == 0 and x is positive         -> 0 with the sign of y
//     Y != 0 and X == 0                -> Pi / 2 with the sign of Y
//     Y != 0 and X is Negative         -> atan(y/x) + (PI with the sign of Y)
//     X == -Infinity and Finite Y      -> Pi with the sign of Y
//     X == +Infinity and Finite Y      -> 0 with the sign of Y
//     Y == Infinity and X is Finite    -> Pi / 2 with the sign of Y
//     Y == Infinity and X == -Infinity -> 3Pi / 4 with the sign of Y
//     Y == Infinity and X == +Infinity -> Pi / 4 with the sign of Y

#include "SumMiscMath.inl"

#endif