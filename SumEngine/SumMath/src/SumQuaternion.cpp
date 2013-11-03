//*************************************************************************************************
// Title: SumQuaternion.h
// Author: Gael Huber
// Description: Quaternion mathematics
//*************************************************************************************************
#include "SumQuaternion.h"

//// Compute a quaternion's axis and angle of rotation (expects unit quaternions)
//void QuaternionToAxisAngle(const Vector pQ, Vector3* pAxis, float* pAngle);
//
//*************************************************************************************************
// Build a quaternion from a rotation matrix
//*************************************************************************************************
Vector QuaternionRotationMatrix(const Matrix& m)
{
	// Trace of a matrix
	Vector m00 = VectorSplatX(m.r[0]);
	Vector m11 = VectorSplatY(m.r[1]);
	Vector m22 = VectorSplatZ(m.r[2]);
	Vector trace = VectorAdd(m00, m11);
	trace = VectorAdd(trace, m22);

	Vector result = VectorZero();
	
	// There are 2 cases
	// 1) The trace is greater than 0. We can proceed normally as there is no risk of division by 0
	// 2) The trace is <= 0. Here we must pick the largest trace element and use that as our pivot point
	if(VectorCompareGreaterThan(trace, gVZero))
	{
		// x (m21 - m12) / s
		// y (m02 - m20) / s
		// z (m10 - m01) / s
		// w 0.25 * s
		// where s = sqrt(trace + 1) * 2

		// S = 4*qx
		Vector s = VectorAdd(trace, gVOne);
		s = VectorSqrt(s);
		s = VectorMul(s, gVTwo);

		// Create our w component
		Vector w = VectorSet(0.0f, 0.0f, 0.0f, 0.25f);
		w = VectorMul(w, s);

		// Finish morphing s into final form
		s = VectorAnd(s, gVMask3);
		s = VectorOr(s, gVIdentityR3);
		
		// Shuffle around vectors until we can reach our desired structure
		Vector v1 = VectorSwizzle(m.r[0], m.r[1], SUM_SWIZZLE(1, 2, 0, 2));	// 01 02 10 12
		Vector v2 = VectorSwizzle(m.r[0], m.r[2], SUM_SWIZZLE(1, 2, 0, 1));	// 01 02 20 21
		Vector v3 = VectorSwizzle(m.r[1], m.r[2], SUM_SWIZZLE(0, 2, 0, 1));	// 10 12 20 21

		Vector v4 = VectorSwizzle(v2, v1, SUM_SWIZZLE(3, 1, 2, 0));	// 21 02 10 01
		Vector v5 = VectorSwizzle(v3, v2, SUM_SWIZZLE(1, 2, 0, 0));	// 12 20 01 01

		v4 = VectorAnd(v4, gVMask3);	// 21 02 10 0.0f
		v5 = VectorAnd(v5, gVMask3);	// 12 20 01 0.0f

		v4 = VectorOr(v4, w);	// 21 02 10 0.25*s
		v5 = VectorNegate(v5);
		
		v4 = VectorSub(v4, v5);	// m21 - m12 ...

		result = VectorDiv(v4, s);
	}
	else if(VectorCompareGreaterThan(m00, m11) && VectorCompareGreaterThan(m00, m22))
	{
		// s = sqrt(1 + m00 - m11 - m22) * 2
		// x = 0.25 * s
		// y = (m01 + m10) / s
		// z = (m02 + m20) / s
		// w = (m21 - m12) / s

		// Calculate s
		Vector s = VectorAdd(gVOne, m00);
		s = VectorSub(s, m11);
		s = VectorSub(s, m22);
		s = VectorSqrt(s);
		s = VectorMul(s, gVTwo);

		// Set x field
		Vector x = VectorSet(0.25f, 0.0f, 0.0f, 0.0f);
		x = VectorMul(x, s);

		// Finish morphing s into final form
		s = VectorAnd(s, gVMask0);
		s = VectorOr(s, gVIdentityR0);

		// Shuffle around vectors until we reach our desired configuration
		Vector v1 = VectorSwizzle(m.r[0], m.r[2], SUM_SWIZZLE(1, 2, 0, 1));	// 01 02 20 21
		Vector v2 = VectorSwizzle(m.r[1], m.r[2], SUM_SWIZZLE(0, 2, 0, 1));	// 10 12 20 21
		
		Vector v3 = VectorSwizzle(v1, v1, SUM_SWIZZLE(0, 0, 1, 3));	// 01 01 02 21
		Vector v4 = VectorSwizzle(v2, v2, SUM_SWIZZLE(0, 0, 2, 1));	// 10 10 20 12

		v3 = VectorAnd(v3, gVMask0);	// 0.0 01 02 21
		v4 = VectorAnd(v4, gVMask0);	// 0.0 10 20 12

		v3 = VectorOr(v3, x);	// 0.25*s 01 02 21
		v4 = VectorMul(v4, gVNegateW);

		v3 = VectorAdd(v3, v4);	// m01 + m10 ...

		result = VectorDiv(v3, s);
	}
	else if(VectorCompareGreaterThan(m11, m22))
	{
		// s = sqrt(1 + m11 - m00 - m22) * 2
		// x = (m01 + m10) / s
		// y = 0.25 * s
		// z = (m12 + m21) / s
		// w = (m02 - m20) / s

		// Calculate s
		Vector s = VectorAdd(gVOne, m11);
		s = VectorSub(s, m00);
		s = VectorSub(s, m22);
		s = VectorSqrt(s);
		s = VectorMul(s, gVTwo);

		// Calculate y
		Vector y = VectorSet(0.0f, 0.25f, 0.0f, 0.0f);
		y = VectorMul(y, s);

		// Finish morphing s into final form
		s = VectorAnd(s, gVMask1);
		s = VectorOr(s, gVIdentityR1);

		// Shuffle around vectors until we reach our desired configuration
		Vector v1 = VectorSwizzle(m.r[0], m.r[1], SUM_SWIZZLE(1, 2, 0, 2));	// 01 02 10 12
		Vector v2 = VectorSwizzle(m.r[1], m.r[2], SUM_SWIZZLE(0, 2, 0, 1));	// 10 12 20 21

		Vector v3 = VectorSwizzle(v1, v1, SUM_SWIZZLE(0, 0, 3, 1));	// 01 01 12 02
		Vector v4 = VectorSwizzle(v2, v2, SUM_SWIZZLE(0, 0, 3, 2));	// 10 10 21 20

		v3 = VectorAnd(v3, gVMask1);
		v4 = VectorAnd(v4, gVMask1);

		v3 = VectorOr(v3, y);
		v4 = VectorMul(v4, gVNegateW);

		v3 = VectorAdd(v3, v4);

		result = VectorDiv(v3, s);
	}
	else
	{
		// s = sqrt(1 + m22 - m00 - m11) * 2
		// x = (m02 + m20) / s
		// y = (m12 + m21) / s
		// z = 0.25 * s
		// w = (m10 - m01) / s

		// Calculate s
		Vector s = VectorAdd(gVOne, m22);
		s = VectorSub(s, m00);
		s = VectorSub(s, m11);
		s = VectorSqrt(s);
		s = VectorMul(s, gVTwo);

		// Calculate z
		Vector z = VectorSet(0.0f, 0.0f, 0.25f, 0.0f);
		z = VectorMul(z, s);

		// Finish morphing s into final form
		s = VectorAnd(s, gVMask2);
		s = VectorOr(s, gVIdentityR2);

		// Shuffle around vectors until we reach our desired configuration
		Vector v1 = VectorSwizzle(m.r[0], m.r[1], SUM_SWIZZLE(1, 2, 0, 2));	// 01 02 10 12
		Vector v2 = VectorSwizzle(m.r[0], m.r[2], SUM_SWIZZLE(1, 2, 0, 1));	// 01 02 20 21

		Vector v3 = VectorSwizzle(v1, v1, SUM_SWIZZLE(1, 3, 0, 2));	// 02 12 01 10
		Vector v4 = VectorSwizzle(v2, v2, SUM_SWIZZLE(2, 3, 0, 0));	// 20 21 01 01

		v3 = VectorAnd(v3, gVMask2);
		v4 = VectorAnd(v4, gVMask2);

		v3 = VectorOr(v3, z);
		v4 = VectorMul(v4, gVNegateW);

		v3 = VectorAdd(v3, v4);

		result = VectorDiv(v3, s);
	}
	
	return result;	
}

//*************************************************************************************************
// Build a quaternion from axes
//*************************************************************************************************
Vector QuaternionFromAxes(const Vector xAxis, const Vector yAxis, const Vector zAxis)
{
	// Build a matrix from the axes of the form:
	// x1 x2 x3 0
	// y1 y2 y3 0
	// z1 z2 z3 0
	// 0  0  0  1

	// First two rows
	// x1 x2 y1 y2 -> unpacklo
	// x3 0  y3 0 -> unpacklo
	// x1 x2 x3 0 -> movelh
	// y1 y2 y3 0 -> movehl
	Vector vTemp0 = _mm_unpacklo_ps(xAxis, yAxis);
	Vector vTemp1 = _mm_unpackhi_ps(xAxis, yAxis);
	Vector r0 = _mm_movelh_ps(vTemp0, vTemp1);
	Vector r1 = _mm_movehl_ps(vTemp0, vTemp1);

	// Last two rows
	// z1 z2 0 0 -> unpackhi
	// z3 0  0 1 -> unpackhi
	// z1 z2 z3 0 -> movelh
	// 0 0 0 1 -> movehl
	vTemp0 = _mm_unpacklo_ps(zAxis, gVIdentityR3);
	vTemp1 = _mm_unpackhi_ps(zAxis, gVIdentityR3);
	Vector r2 = _mm_movelh_ps(vTemp0, vTemp1);
	Vector r3 = _mm_movehl_ps(vTemp0, vTemp1);

	// Build and get quaternion from matrix
	Matrix m = Matrix(r0, r1, r2, r3);
	return QuaternionRotationMatrix(m);
}

//*************************************************************************************************
// Rotation about an arbitrary axis
//*************************************************************************************************
Vector QuaternionRotationAxis(const Vector v, SFLOAT angle)
{
	Vector vAngle = VectorReplicate(angle);
	return QuaternionRotationAxis(v, vAngle);
}

//*************************************************************************************************
// Rotation about an arbitrary axis
//*************************************************************************************************
Vector QuaternionRotationAxis(const Vector v, const Vector angle)
{
	// Get half angle
	Vector halfAngle = VectorMul(angle, gVOneHalf);

	// Get sin and cos of half-angle
	Vector sin, cos;
	VectorSinCos(&sin, &cos, halfAngle);

	// Get vector portion of quaternion
	sin = VectorMul(sin, v);
	
	// Combine scalar and vector values into quaternion
	sin = VectorAnd(sin, gVMask3);
	cos = VectorAnd(cos, gVWMask);
	Vector quat = VectorOr(sin, cos);
	return quat;
}

//*************************************************************************************************
// Yaw around the Y axis, a pitch around the X axis, a roll around the Z axis
//*************************************************************************************************
Vector QuaternionRotationYawPitchRoll(SFLOAT yaw, SFLOAT pitch, SFLOAT roll)
{
	Vector vYaw = VectorReplicate(yaw);
	Vector vPitch = VectorReplicate(pitch);
	Vector vRoll = VectorReplicate(roll);
	return QuaternionRotationYawPitchRoll(vYaw, vPitch, vRoll);
}

//*************************************************************************************************
// Yaw around the Y axis, a pitch around the X axis, a roll around the Z axis
//*************************************************************************************************
Vector QuaternionRotationYawPitchRoll(const Vector yaw, const Vector pitch, const Vector roll)
{
	// Create individual yaw pitch and roll quaternion representations
	Vector qYaw = QuaternionRotationAxis(gVIdentityR1, yaw);
	Vector qPitch = QuaternionRotationAxis(gVIdentityR0, pitch);
	Vector qRoll = QuaternionRotationAxis(gVIdentityR2, roll);

	// Multiply rotations together
	Vector rotation = QuaternionMultiply(qYaw, qPitch);
	rotation = QuaternionMultiply(rotation, qRoll);

	return rotation;
}

//*************************************************************************************************
// Given the two vectors, calculate the rotation quaternion between two vectors
//*************************************************************************************************
Vector QuaternionCalculateRotation(const Vector u, const Vector v)
{
	// Get cos
	Vector dot = Vec3Dot(u, v);
	
	// Get squared length of u and v to find the length of the vector between u and v
	Vector lu = Vec3LengthSqr(u);
	Vector lv = Vec3LengthSqr(v);
	Vector k = VectorMul(lu, lv);
	k = VectorSqrt(k);

	if(VectorCompareEqual(VectorDiv(dot, k), gVNegOne))
	{
		// Return 180 degree rotation about any axis (choose x)
		return gVIdentityR0;
	}

	// Construct a resultant quaternion
	dot = VectorAdd(dot, k);
	Vector cross = Vec3Cross(u, v);
	
	dot = VectorAnd(dot, gVWMask);
	cross = VectorAnd(cross, gVMask3);
	dot = VectorOr(dot, cross);

	dot = QuaternionNormalize(dot);

	return dot;
}

//*************************************************************************************************
// Calculate the rotation quaternion between two quaternions. Assume unit quaternions to speed up.
//*************************************************************************************************
Vector QuaternionCalculateRotationFast(const Vector u, const Vector v)
{
	// Get cos
	Vector dot = Vec3Dot(u, v);
	
	if(VectorCompareEqual(dot, gVNegOne))
	{
		// Return 180 degree rotation about any axis (choose x)
		return gVIdentityR0;
	}

	// Construct a resultant quaternion
	dot = VectorAdd(dot, gVOne);
	Vector cross = Vec3Cross(u, v);
	
	dot = VectorAnd(dot, gVWMask);
	cross = VectorAnd(cross, gVMask3);
	dot = VectorOr(dot, cross);

	dot = QuaternionNormalize(dot);

	return dot;
}


//*************************************************************************************************
// Quaternion multiplication (Q1 * Q2)
// Quaternion multiplication is in the form of:
// Q1 = [ w1 v1 ]		Q2 = [ w2 v2 ]
// Q' = [ w1w2 - v1.v2		w1v2 + w2v1 + v1xv2 ]
//*************************************************************************************************
Vector QuaternionMultiply(const Vector q1, const Vector q2)
{
	// Find the dot
	Vector dot = Vec3Dot(q1, q2);
	
	// Find the cross product
	Vector cross = Vec3Cross(q1, q2);

	// Splat w1 and w2
	Vector w1 = VectorSplatW(q1);
	Vector w2 = VectorSplatW(q2);

	// Multiply w1 and w2
	Vector vTemp = VectorMul(w1, w2);
	dot = VectorSub(vTemp, dot);

	// w1v2
	vTemp = VectorMul(w1, q2);
	Vector vTemp2 = VectorMul(w2, q1);
	cross = VectorAdd(cross, vTemp);
	cross = VectorAdd(cross, vTemp2);

	// Move scalar and vector values into single quaternion
	dot = VectorAnd(dot, gVWMask);
	cross = VectorAnd(cross, gVMask3);
	dot = VectorOr(dot, cross);
	return dot;
}

//*************************************************************************************************
// Multiply a unit quaternion by a Vector3. This acts as a transformation of the form v' = q*vq
// For multiplying a vector, the math is slightly simplified as Vector v is projected into
// a quaternion. As such:
// Q = [ w1 v1 ]
// Qv = [ 0 v2 ]
// QQv = [ -v1.v2		w1v2 + v1xv2 ]
//*************************************************************************************************
Vector QuaternionMultiplyFast(const Vector q, const Vector v)
{
	// Find the 3d dot product
	Vector dot = Vec3Dot(q, v);
	dot = VectorNegate(dot);

	// Find the scaled vector
	Vector scale = VectorSplatW(q);
	scale = VectorMul(scale, v);

	// Find the cross product
	Vector cross = Vec3Cross(q, v);
	
	// Add scale and cross together
	scale = VectorAdd(scale, cross);

	// Apply masks to get dot and scale into a quaternion
	dot = VectorAnd(dot, gVWMask);
	scale = VectorAnd(scale, gVMask3);
	dot = VectorOr(dot, scale);

	return dot;
}

//*************************************************************************************************
// Transform a vector by a quaternion
// v' = q*vq
//*************************************************************************************************
Vector QuaternionTransformVector(const Vector v, const Vector q)
{
	// Grab the conjugate, this transform should only happen with unit quaternions, so the conjugate
	// should be sufficient
	Vector qConj = QuaternionConjugate(q);

	// We may now use the fast multiplication for q' = q*v operation as vector v has 0 for its real
	// component.
	qConj = QuaternionMultiply(qConj, v);// QuaternionMultiplyFast(qConj, v);

	// Since v has now been transformed into imaginary space, we must now transform it back out.
	// This operation cannot use fast multiply as q' might have a non-zero real component. 
	qConj = QuaternionMultiply(qConj, q);

	// Ensure we properly convert q' into v' by zero-ing out the real component
	qConj = VectorAnd(qConj, gVMask3);
	return qConj;
}

//*************************************************************************************************
// Normalize
//*************************************************************************************************
Vector QuaternionNormalize(const Vector q)
{
	Vector vTemp = QuaternionLength(q);
	return VectorDiv(q, vTemp);
}

//*************************************************************************************************
// Quaternion inverse for a unit quaternion is only the conjugate
//*************************************************************************************************
Vector QuaternionInverseSafe(const Vector q)
{
	return QuaternionConjugate(q);
}

//*************************************************************************************************
// Conjugate and re-norm
//*************************************************************************************************
Vector QuaternionInverse(const Vector q)
{
	Vector vTemp = QuaternionConjugate(q);
	return QuaternionNormalize(vTemp);
}

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
