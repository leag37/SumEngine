//*************************************************************************************************
// Title: SumVector2.h
// Author: Gael Huber
// Description: Describes a vector 2 and related functionality
//*************************************************************************************************
#ifndef __SUMVECTOR2_H__
#define __SUMVECTOR2_H__

#include "SumMath.h"

// Equality
SBOOL Vec2Equal(const Vector v1, const Vector v2);

// Non-Equality
SBOOL Vec2NonEqual(const Vector v1, const Vector v2);

// Length
Vector Vec2Length(const Vector v);

// Squared length
Vector Vec2LengthSqr(const Vector v);

// Dot product
Vector Vec2Dot(const Vector v1, const Vector v2);

// Z component of cross product
Vector Vec2CCW(const Vector v1, const Vector v2);

// Addition
Vector Vec2Add(const Vector v1, const Vector v2);

// Subtraction
Vector Vec2Sub(const Vector v1, const Vector v2);

// Minimize each component
Vector Vec2Minimize(const Vector v1, const Vector v2);

// Maximize each component
Vector Vec2Maximize(const Vector v1, const Vector v2);

// Scale the vector
Vector Vec2Scale(const Vector v, float s);

// Scale the vector
Vector Vec2Scale(const Vector v, const Vector s);

// Linear interpolation V1 + s(V2 - V1)
Vector Vec2Lerp(const Vector v1, const Vector v2, float s);

// Linear interpolation V1 + s(V2 - V1)
Vector Vec2Lerp(const Vector v1, const Vector v2, const Vector s);

// Normalize
Vector Vec2Normalize(const Vector v);

extern "C++"
{
// Hermite interpolation between position V1, tangent T1 (when s == 0)
// and position V2, tangent T2 (when s == 1).
Vector Vec2Hermite(const Vector v1, const Vector t1, 
	const Vector v2, const Vector& t2, float s);

// Hermite interpolation between position V1, tangent T1 (when s == 0)
// and position V2, tangent T2 (when s == 1).
Vector Vec2Hermite(const Vector v1, const Vector t1, 
	const Vector v2, const Vector& t2, const Vector& s);

// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
Vector Vec2CatmullRom(const Vector v0, const Vector v1,
	const Vector v2, const Vector& v3, float s);

// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
Vector Vec2CatmullRom(const Vector v0, const Vector v1,
	const Vector v2, const Vector& v3, const Vector& s);

// Barycentric coordinates V1 + f(V2 - V1) + g(V3 - V1)
Vector Vec2Barycentric(const Vector v1, const Vector v2, const Vector v3,
	float f, float g);

// Barycentric coordinates V1 + f(V2 - V1) + g(V3 - V1)
Vector Vec2Barycentric(const Vector v1, const Vector v2, const Vector v3,
	const Vector& f, const Vector& g);

// Transform by matrix (x, y, 0, 1)
Vector Vec2Transform(const Vector v, const Matrix& m);

// Transform coords by matrix (x, y, 0, 1)
Vector Vec2TransformCoord(const Vector v, const Matrix& m);

// Transform normal by matrix (x, y, 0, 0)
Vector Vec2TransformNormal(const Vector v, const Matrix& m);
}

#include "SumVector2.inl"

#endif // SUMVECTOR2