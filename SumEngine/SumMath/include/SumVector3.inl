//*************************************************************************************************
// Title: SumVector3.inl
// Author: Gael Huber
// Description: Vector3 mathematics
//*************************************************************************************************

//*************************************************************************************************
// Equality
//*************************************************************************************************
SUMINLINE SBOOL Vec3Equal(const Vector v1, const Vector v2)
{
	Vector vTemp = _mm_cmpeq_ps(v1, v2);
	return ((_mm_movemask_ps(vTemp) == 7) != 0);
}

//*************************************************************************************************
// Non-Equality
//*************************************************************************************************
SUMINLINE SBOOL Vec3NotEqual(const Vector v1, const Vector v2)
{
	Vector vTemp = _mm_cmpeq_ps(v1, v2);
	return ((_mm_movemask_ps(vTemp) != 7) != 0);
}

//*************************************************************************************************
// Length
//*************************************************************************************************
SUMINLINE Vector Vec3Length(const Vector v)
{
#ifdef SUMSIMD

	// Get squared length
	Vector vSqrLen = _mm_mul_ps(v, v);

	// Splat y, z
	Vector vYZ = _mm_shuffle_ps(vSqrLen, vSqrLen, _MM_SHUFFLE(1, 2, 1, 2));
	
	// Add values
	vSqrLen = _mm_add_ss(vSqrLen, vYZ);
	vYZ = _mm_shuffle_ps(vYZ, vYZ, _MM_SHUFFLE(1, 1, 1, 1));
	vSqrLen = _mm_add_ss(vSqrLen, vYZ);

	// Splat x to yield final result
	vSqrLen = _mm_shuffle_ps(vSqrLen, vSqrLen, _MM_SHUFFLE(0, 0, 0, 0));

	// Square length
	vSqrLen = _mm_sqrt_ps(vSqrLen);

	return vSqrLen;

#else

#endif
}

//*************************************************************************************************
// Squared length
//*************************************************************************************************
SUMINLINE Vector Vec3LengthSqr(const Vector v)
{
#ifdef SUMSIMD

	// Get squared length
	Vector vSqrLen = _mm_mul_ps(v, v);

	// Splat y, z
	Vector vYZ = _mm_shuffle_ps(vSqrLen, vSqrLen, _MM_SHUFFLE(1, 2, 1, 2));
	
	// Add values
	vSqrLen = _mm_add_ss(vSqrLen, vYZ);
	vYZ = _mm_shuffle_ps(vYZ, vYZ, _MM_SHUFFLE(1, 1, 1, 1));
	vSqrLen = _mm_add_ss(vSqrLen, vYZ);

	// Splat x to yield final result
	vSqrLen = _mm_shuffle_ps(vSqrLen, vSqrLen, _MM_SHUFFLE(0, 0, 0, 0));

	return vSqrLen;

#else

#endif
}

//*************************************************************************************************
// Dot
//*************************************************************************************************
SUMINLINE Vector Vec3Dot(const Vector v1, const Vector v2)
{
#ifdef SUMSIMD

	// Multiply two vectors together
	Vector vTemp = _mm_mul_ps(v1, v2);

	// Grab y and z values
	Vector vYZ = _mm_shuffle_ps(vTemp, vTemp, _MM_SHUFFLE(2, 1, 2, 1));

	// Find result of x+y
	vTemp = _mm_add_ss(vTemp, vYZ);

	// Shuffle to get z value
	vYZ = _mm_shuffle_ps(vYZ, vYZ, _MM_SHUFFLE(1, 1, 1, 1));

	// Find x+y+z
	vTemp = _mm_add_ss(vTemp, vYZ);

	// Splat results
	vTemp = _mm_shuffle_ps(vTemp, vTemp, _MM_SHUFFLE(0, 0, 0, 0));

	return vTemp;

#else
#endif
}

//*************************************************************************************************
// Cross
// v1 x v2 = (y1.z2 - z1.y2, z1.x2 - x1.z2, x1.y2 - y1.x2)
//*************************************************************************************************
SUMINLINE Vector Vec3Cross(const Vector v1, const Vector v2)
{
	// Perform left side of the operation
	Vector vTemp1 = _mm_shuffle_ps(v1, v1, _MM_SHUFFLE(3, 0, 2, 1));
	Vector vTemp2 = _mm_shuffle_ps(v2, v2, _MM_SHUFFLE(3, 1, 0, 2));
	Vector vResult = _mm_mul_ps(vTemp1, vTemp2);

	// Perform right side of the operation
	vTemp1 = _mm_shuffle_ps(vTemp1, vTemp1, _MM_SHUFFLE(3, 0, 2, 1));
	vTemp2 = _mm_shuffle_ps(vTemp2, vTemp2, _MM_SHUFFLE(3, 1, 0, 2));
	vTemp1 = _mm_mul_ps(vTemp1, vTemp2);

	// Subtraction
	vResult = _mm_sub_ps(vResult, vTemp1);

	// Set w to 0
	vResult = _mm_and_ps(vResult, gVMask3);

	return vResult;
}

//*************************************************************************************************
// Add
//*************************************************************************************************
SUMINLINE Vector Vec3Add(const Vector v1, const Vector v2)
{
#ifdef SUMSIMD

	return _mm_add_ps(v1, v2);

#else
#endif
}

//*************************************************************************************************
// Subtract
//*************************************************************************************************
SUMINLINE Vector Vec3Sub(const Vector v1, const Vector v2)
{
#ifdef SUMSIMD

	return _mm_sub_ps(v1, v2);

#else
#endif
}

//*************************************************************************************************
// Minimize
//*************************************************************************************************
SUMINLINE Vector Vec3Minimize(const Vector v1, const Vector v2)
{
#ifdef SUMSIMD

	return _mm_min_ps(v1, v2);

#else
#endif
}

//*************************************************************************************************
// Maximize
//*************************************************************************************************
SUMINLINE Vector Vec3Maximize(const Vector v1, const Vector v2)
{
#ifdef SUMSIMD

	return _mm_max_ps(v1, v2);
#else
#endif
}

//*************************************************************************************************
// Scale
//*************************************************************************************************
SUMINLINE Vector Vec3Scale(const Vector v, float s)
{
#ifdef SUMSIMD

	Vector vS = _mm_set1_ps(s);
	return Vec3Scale(v, vS);

#else
#endif
}

//*************************************************************************************************
// Scale
//*************************************************************************************************
SUMINLINE Vector Vec3Scale(const Vector v, Vector s)
{
#ifdef SUMSIMD

	return _mm_mul_ps(v, s);

#else
#endif
}

//*************************************************************************************************
// Lerp
//*************************************************************************************************
SUMINLINE Vector Vec3Lerp(const Vector v1, const Vector v2, float s)
{
#ifdef SUMSIMD
	
	Vector vS = _mm_set1_ps(s);
	return Vec3Lerp(v1, v2, vS);

#else
#endif
}

//*************************************************************************************************
// Lerp
// V3 = V1 + s(V2 - V1);
//*************************************************************************************************
SUMINLINE Vector Vec3Lerp(const Vector v1, const Vector v2, Vector s)
{
	Vector v3 = Vec3Sub(v2, v1);
	v3 = Vec3Scale(v3, s);
	return Vec3Add(v1, v3);
}

//*************************************************************************************************
// Normalize 
//*************************************************************************************************
SUMINLINE Vector Vec3Normalize(const Vector v)
{
	// Multiply by self
	Vector vLen = Vec3Length(v);

	// Divide v
	return _mm_div_ps(v, vLen);
}