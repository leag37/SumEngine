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

//// Add
//Vector3* Vec3Add(Vector3* pOut, const Vector3* pV1, const Vector3* pV2);
//
//// Subtract
//Vector3* Vec3Sub(Vector3* pOut, const Vector3* pV1, const Vector3* pV2);
//
//// Minimize
//Vector3* Vec3Minimize(Vector3* pOut, const Vector3* pV1, const Vector3* pV2);
//
//// Maximize
//Vector3* Vec3Maximize(Vector3* pOut, const Vector3* pV1, const Vector3* pV2);
//
//// Scale
//Vector3* Vec3Scale(Vector3* pOut, const Vector3* pV, float s);
//
//// Lerp
//Vector3* Vec3Lerp(Vector3* pOut, const Vector3* pV1, const Vector3* pV2, float s);
//
//// Normalize
//Vector3* Vec3Normalize(Vector3* pOut, const Vector3* pV);
//
//extern "C"
//{
//// Hermite interpolation between position V1, tangent T1 (when s == 0)
//// and position V2, tangent T2 (when s == 1).
//Vector3* Vec3Hermite(Vector3* pOut, const Vector3* pV1, const Vector3* pT1, 
//	const Vector3* pV2, const Vector3* pT2, float s);
//
//// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
//Vector3* Vec3CatmullRom(Vector3* pOut, const Vector3* pV0, const Vector3* pV1,
//	const Vector3* pV2, const Vector3* pV3, float s);
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
//}

#include "SumVector3.inl"

#endif