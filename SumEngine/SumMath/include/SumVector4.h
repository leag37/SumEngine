//*************************************************************************************************
// Title: SumVector4.h
// Author: Gael Huber
// Description: Vector 4 mathematics.
//*************************************************************************************************
#ifndef __SUMVECTOR4_H__
#define __SUMVECTOR4_H__

#include "SumMath.h"

// Equality
SBOOL Vec4Equal(const Vector v1, const Vector v2);

// Non-Equality
SBOOL Vec4NotEqual(const Vector v1, const Vector v2);

// Length
Vector Vec4Length(const Vector v);

// Squared length
Vector Vec4LengthSqr(const Vector v);

// Dot product
Vector Vec4Dot(const Vector v1, const Vector v2);

// Add
Vector Vec4Add(const Vector v1, const Vector v2);

// Subtract
Vector Vec4Sub(const Vector v1, const Vector v2);

// Minimize
Vector Vec4Minimize(const Vector v1, const Vector v2);

// Maximize
Vector Vec4Maximize(const Vector v1, const Vector v2);

// Scale
Vector Vec4Scale(const Vector v, float s);

// Scale
Vector Vec4Scale(const Vector v, Vector s);

// Lerp
Vector Vec4Lerp(const Vector v1, const Vector v2, float s);

// Lerp
Vector Vec4Lerp(const Vector v1, const Vector v2, Vector s);

extern "C++"
{
// Cross
Vector Vec4Cross(const Vector v1, const Vector v2, const Vector v3);

// Normalize
Vector Vec4Normalize(const Vector v);

// Hermite interpolation between position V1, tangent T1 (when s == 0)
// and position V2, tangent T2 (when s == 1).
Vector Vec4Hermite(const Vector v1, const Vector t1, const Vector v2, const Vector& t2, float s);

// Hermite interpolation between position V1, tangent T1 (when s == 0)
// and position V2, tangent T2 (when s == 1).
Vector Vec4Hermite(const Vector v1, const Vector t1, const Vector v2, const Vector& t2, const Vector& s);

// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
Vector Vec4CatmullRom(const Vector v0, const Vector v1,	const Vector v2, const Vector& v3, float s);

// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
Vector Vec4CatmullRom(const Vector v0, const Vector v1,	const Vector v2, const Vector& v3, const Vector& s);

// Barycentric coordinates
Vector Vec4Barycentric(const Vector v1, const Vector v2, const Vector v3, float f, float g);

// Barycentric coordinates
Vector Vec4Barycentric(const Vector v1, const Vector v2, const Vector v3, const Vector& f, const Vector& g);

// Transform vector by matrix
Vector Vec4Transform(const Vector v, const Matrix& m);
}

#include "SumVector4.inl"

#endif // SUMVECTOR4