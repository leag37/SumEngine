//*************************************************************************************************
// Title: SumQuaternion.h
// Author: Gael Huber
// Description: Quaternion mathematics. An important thing to note is that while traditionally
//	quaternions are represented as Q = [ w v ] with w being the real component and v being the
//	imaginary vector component, we will in fact represent quaternions in the form of Q = [ v w ].
//	This will act as an optimization for SIMD multiplications and to avoid shifting around values
//	unnecessarily.
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
//void QuaternionToAxisAngle(const Vector q, Vector3* pAxis, float* pAngle);

// Build a quaternion from a rotation matrix
Vector QuaternionRotationMatrix(const Matrix& m);

// Build a quaternion from axes
Vector QuaternionFromAxes(const Vector xAxis, const Vector yAxis, const Vector zAxis);

// Rotation about an arbitrary axis
Vector QuaternionRotationAxis(const Vector v, SFLOAT angle);

// Rotation about an arbitrary axis
Vector QuaternionRotationAxis(const Vector v, const Vector angle);

// Yaw around the Y axis, a pitch around the X axis, a roll around the Z axis
Vector QuaternionRotationYawPitchRoll(SFLOAT yaw, SFLOAT pitch, SFLOAT roll);

// Yaw around the Y axis, a pitch around the X axis, a roll around the Z axis
Vector QuaternionRotationYawPitchRoll(const Vector yaw, const Vector pitch, const Vector roll);

// Calculate the rotation quaternion between two quaternions
Vector QuaternionCalculateRotation(const Vector u, const Vector v);

// Calculate the rotation quaternion between two quaternions. Assume unit quaternions to speed up.
Vector QuaternionCalculateRotationFast(const Vector u, const Vector v);

// Quaternion multiplication (Q2 * Q1)
Vector QuaternionMultiply(const Vector q1, const Vector q2);

// Multiply a quaternion by a Vector3
Vector QuaternionMultiplyFast(const Vector q1, const Vector q2);

// Transform a vector by a quaternion
Vector QuaternionTransformVector(const Vector v, const Vector q);

//
// Normalize
Vector QuaternionNormalize(const Vector q);

// Inverse approximation (this is for unit quaternions only)
Vector QuaternionInverse(const Vector q);

// Conjugate and re-norm
Vector QuaternionInverseSafe(const Vector q);
//
//// Expects unit quaternions. If q = (cos(theta), sin(theta) * v); ln(q) = (0, theta * v)
//Vector QuaternionLn(const Vector q);
//
//// Expects pure quaternions. (w == 0) w is ignored in calculation. If q = (0, theta * v);
//// exp(q) = (cos(theta), sin(theta) * v)
//Vector QuaternionExp(const Vector q);
//
//// Spherical linear interpolation between Q1 (t == 0) and Q2 (t == 1). Expects unit quaternions
//Vector QuaternionSlerp(const Vector q1, const Vector q2, float t);
//
//// Spherical quadrangle interpolation (Slerp(Slerp(Q1, C, t), Slerp(A, B, t), 2t(1-t))
//Vector QuaternionSquad(const Vector q1, const Vector a, 
//	const Vector b, const Vector c, float t);
//
//// Setup control points for spherical quadrangle interpolation from Q1 to Q2.  The control points 
//// are chosen in such a way to ensure the continuity of tangents with adjacent segments.
//void QuaternionSquadSetup(Vector aOut, Vector bOut, Vector cOut, 
//	const Vector q0, const Vector q1, const Vector q2, const Vector q3);
//
//// Barycentric interpolation. Slerp(Slerp(Q1, Q2, f+g), Slerp(Q1, Q3, f+g), g/(f+g))
//Vector QuaternionBarycentric(Vector out, const Vector q1, const Vector q2, const Vector q3, float f, float g);
}

#include "SumQuaternion.inl"

#endif