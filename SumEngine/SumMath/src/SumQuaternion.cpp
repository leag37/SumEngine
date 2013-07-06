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
	Vector vTemp0 = VectorSplatX(m.r[0]);
	Vector vTemp1 = VectorSplatY(m.r[1]);
	Vector vTemp2 = VectorSplatZ(m.r[2]);
	vTemp0 = VectorAdd(vTemp0, vTemp1);
	Vector trace = VectorAdd(vTemp0, vTemp2);
	Vector root = VectorZero();
	Vector result = VectorZero();

	// Check whether trace is greater than zero
	if(VectorCompareGreaterThan(trace, gVZero))
	{
		// |w| > 0.5 so choose w > 0.5
		root = VectorAdd(trace, gVOne);
		root = VectorSqrt(root);

		Vector w = VectorMul(gVOneHalf, root);

		root = VectorDiv(gVOneHalf, root);

		// x = (21-12)*root
		// y = (02-20)*root
		// z = (10-01)*root
		// j c e
		vTemp0 = VectorSwizzle(m.r[2], m.r[0], SUM_SWIZZLE(1, 2, 1, 2));
		vTemp1 = VectorSwizzle(m.r[1], m.r[1], SUM_SWIZZLE(0, 0, 0, 0));
		vTemp0 = _mm_movelh_ps(vTemp0, vTemp1);

		vTemp1 = VectorSwizzle(m.r[1], m.r[2], SUM_SWIZZLE(2, 0, 2, 0));
		vTemp2 = VectorSwizzle(m.r[0], m.r[0], SUM_SWIZZLE(1, 1, 1, 1));
		vTemp1 = _mm_movelh_ps(vTemp1, vTemp2);

		vTemp0 = VectorSub(vTemp0, vTemp1);
		vTemp0 = VectorMul(vTemp0, root);

		// Move into result
		w = VectorAnd(w, gVWMask);
		vTemp0 = VectorAnd(vTemp0, gVMask3);
		result = VectorOr(w, vTemp0);
	}
	else
	{
		// |w| <= 0.5
		static size_t iNext[3] = {1, 2, 0};
		size_t i = 0;
		if(VectorCompareGreaterThan(vTemp1, vTemp0))
		{
			i = 1;
		}
		Vector vTemp3 = VectorSwizzle(m.r[i], m.r[i], SUM_SWIZZLE(1, 1, 1, 1));//i, i, i, i));
		if(VectorCompareGreaterThan(vTemp2, vTemp3))
		{
			i = 2;
		}

		size_t j = iNext[i];
		size_t k = iNext[j];

		// Grab ii, jj, and kk
		//vTemp1 = VectorSwizzle(m.r[j], m.r[j], SUM_SWIZZLE(j, j, j, j));
		//vTemp2 = VectorSwizzle(m.r[k], m.r[k], SUM_SWIZZLE(k, k, k, k));
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
