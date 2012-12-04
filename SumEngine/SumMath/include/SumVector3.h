//*************************************************************************************************
// Title: SumVector3.h
// Author: Gael Huber
// Description: Vector3 mathematics
//*************************************************************************************************
#ifndef __SUMVECTOR3_H__
#define __SUMVECTOR3_H__

#include "SumMath.h"

// Length
Vector Vec3Length(const Vector v);

// Squared length
Vector Vec3LengthSqr(const Vector v);

// Dot
Vector Vec3Dot(const Vector v1, const Vector v2);

// Cross
Vector Vec3Cross(const Vector v1, const Vector v2);

// Add
Vector Vec3Add(const Vector v1, const Vector v2);

// Subtract
Vector Vec3Sub(const Vector v1, const Vector v2);

// Minimize
Vector Vec3Minimize(const Vector v1, const Vector v2);

// Maximize
Vector Vec3Maximize(const Vector v1, const Vector v2);

// Scale
Vector Vec3Scale(const Vector v, float s);

// Scale
Vector Vec3Scale(const Vector v, Vector s);

// Lerp
Vector Vec3Lerp(const Vector v1, const Vector v2, float s);

// Lerp
Vector Vec3Lerp(const Vector v1, const Vector v2, Vector s);

// Normalize
Vector Vec3Normalize(const Vector v);

extern "C"
{
// Hermite interpolation between position V1, tangent T1 (when s == 0)
// and position V2, tangent T2 (when s == 1).
Vector Vec3Hermite(const Vector v1, const Vector t1, const Vector v2, const Vector t2, float s);

// Hermite interpolation between position V1, tangent T1 (when s == 0)
// and position V2, tangent T2 (when s == 1).
Vector Vec3Hermite(const Vector v1, const Vector t1, const Vector v2, const Vector t2, const Vector s);

// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
Vector Vec3CatmullRom(const Vector v0, const Vector v1, const Vector v2, const Vector v3, float s);

// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
Vector Vec3CatmullRom(const Vector v0, const Vector v1, const Vector v2, const Vector v3, const Vector s);

//
//// Barycentric
//Vector3* Vec3Barycentric(Vector3* pOut, const Vector3* pV1, const Vector3* pV2, const Vector3* pV3,
//	float f, float g);
//
//// Transform by matrix (x, y, z, 1)
//Vector4* Vec3Transform(Vector4* pOut, const Vector3* pV, const Matrix* pM);
//
//// Transform coord by matrix (x, y, z, 1)
//Vector3* Vec3TransformCoord(Vector3* pOut, const Vector3* pV, const Matrix* pM);
//
//// Transform normal by matix (x, y, z, 0)
//Vector3* Vec3TransformNormal(Vector3* pOut, const Vector3* pV, const Matrix* pM);
//
//// Project from object space into screen space
//Vector3* Vec3Project(Vector3* pOut, const Vector3* pV, const Viewport* pViewport, 
//	const Matrix* pProjection, const Matrix* pView, const Matrix* pWorld);
//
//// Project from screen space into object space
//Vector3* Vec3Unproject(Vector3* pOut, const Vector3* pV, const Viewport* pViewport, 
//	const Matrix* pProjection, const Matrix* pView, const Matrix* pWorld);
}

#include "SumVector3.inl"

#endif