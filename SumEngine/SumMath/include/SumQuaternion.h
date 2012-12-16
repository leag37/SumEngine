//*************************************************************************************************
// Title: SumQuaternion.h
// Author: Gael Huber
// Description: Quaternion mathematics
//*************************************************************************************************
#ifndef __SUMQUATERNION_H__
#define __SUMQUATERNION_H__

#include "SumMath.h"

// Add
Vector QuaternionAdd(const Vector q1, const Vector q2);

// Subtract
Vector QuaternionSub(const Vector q1, const Vector q2);

// Scale
Vector QuaternionScale(const Vector q, float s);

// Scale
Vector QuaternionScale(const Vector q, const Vector s);

// Length
Vector QuaternionLength(const Vector q);

// Length squared, or "norm"
Vector QuaternionLengthSqr(const Vector q);

// Dot
Vector QuaternionDot(const Vector q1, const Vector q2);

// Identity (0, 0, 0, 1)
Vector QuaternionIdentity();

// Is identity
SBOOL QuaternionIsIdentity(const Vector q);

// Conjugate (-x, -y, -z, -w)
Vector QuaternionConjugate(const Vector q);

extern "C++"
{

//// Compute a quaternion's axis and angle of rotation (expects unit quaternions)
//void QuaternionToAxisAngle(const Vector pQ, Vector3* pAxis, float* pAngle);
//
//// Build a quaternion from a rotation matrix
//Vector QuaternionRotationMatrix(const Matrix* pM);
//
//// Rotation about an arbitrary axis
//Vector QuaternionRotationAxis(const Vector3* pV, float angle);
//
//// Yaw around the Y axis, a pitch around the X axis, a roll around the Z axis
//Vector QuaternionRotationYawPitchRoll(float yaw, float pitch, float roll);
//
//// Quaternion multiplication (Q2 * Q1)
//Vector QuaternionMultiply(const Vector pQ1, const Vector pQ2);
//
//// Multiply a quaternion by a Vector3
//Vector3* QuaternionMultiply(const Vector pQ, const Vector3* pV);
//
//// Normalize
//Vector QuaternionNormalize(const Vector pQ);
//
//// Conjugate and re-norm
//Vector QuaternionInverse(const Vector pQ);
//
//// Expects unit quaternions. If q = (cos(theta), sin(theta) * v); ln(q) = (0, theta * v)
//Vector QuaternionLn(const Vector pQ);
//
//// Expects pure quaternions. (w == 0) w is ignored in calculation. If q = (0, theta * v);
//// exp(q) = (cos(theta), sin(theta) * v)
//Vector QuaternionExp(const Vector pQ);
//
//// Spherical linear interpolation between Q1 (t == 0) and Q2 (t == 1). Expects unit quaternions
//Vector QuaternionSlerp(const Vector pQ1, const Vector pQ2, float t);
//
//// Spherical quadrangle interpolation (Slerp(Slerp(Q1, C, t), Slerp(A, B, t), 2t(1-t))
//Vector QuaternionSquad(const Vector pQ1, const Vector pA, 
//	const Vector pB, const Vector pC, float t);
//
//// Setup control points for spherical quadrangle interpolation from Q1 to Q2.  The control points 
//// are chosen in such a way to ensure the continuity of tangents with adjacent segments.
//void QuaternionSquadSetup(Vector pAOut, Vector pBOut, Vector pCOut, 
//	const Vector pQ0, const Vector pQ1, const Vector pQ2, const Vector pQ3);
//
//// Barycentric interpolation. Slerp(Slerp(Q1, Q2, f+g), Slerp(Q1, Q3, f+g), g/(f+g))
//Vector QuaternionBarycentric(Vector pOut, const Vector pQ1, const Vector pQ2, const Vector pQ3, float f, float g);
}

#include "SumQuaternion.inl"

#endif