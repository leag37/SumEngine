//*************************************************************************************************
// Title: SumVector2.inl
// Author: Gael Huber
// Description: 2D vector implementation
//*************************************************************************************************

#ifdef SUMSIMD

//*************************************************************************************************
// Equality
//*************************************************************************************************
SUMINLINE SBOOL Vec2Equal(const Vector v1, const Vector v2)
{
	Vector vTemp = _mm_cmpeq_ps(v1, v2);
	return ((_mm_movemask_ps(vTemp) == 3) != 0);
}

//*************************************************************************************************
// Non-Equality
//*************************************************************************************************
SUMINLINE SBOOL Vec2NonEqual(const Vector v1, const Vector v2)
{
	Vector vTemp = _mm_cmpeq_ps(v1, v2);
	return ((_mm_movemask_ps(vTemp) != 3) != 0);
}

//*************************************************************************************************
// Length
//*************************************************************************************************
SUMINLINE Vector Vec2Length(const Vector v)
{
	// Get squared length
	Vector vSqrLen = _mm_mul_ps(v, v);

	// Get y value
	Vector vY = _mm_shuffle_ps(vSqrLen, vSqrLen, _MM_SHUFFLE(1, 1, 1, 1));

	// Assign sqr length to a vector
	vSqrLen = _mm_add_ps(vSqrLen, vY);

	// Get x value
	vSqrLen = _mm_shuffle_ps(vSqrLen, vSqrLen, _MM_SHUFFLE(0, 0, 0, 0));

	// Square root
	vSqrLen = _mm_sqrt_ps(vSqrLen);

	// Return 
	return vSqrLen;
}

//*************************************************************************************************
// Squared length
//*************************************************************************************************
SUMINLINE Vector Vec2LengthSqr(const Vector v)
{
		// Get squared length
	Vector vSqrLen = _mm_mul_ps(v, v);

	// Get y value
	Vector vY = _mm_shuffle_ps(vSqrLen, vSqrLen, _MM_SHUFFLE(1, 1, 1, 1));

	// Assign sqr length to a vector
	vSqrLen = _mm_add_ps(vSqrLen, vY);

	// Get x value
	vSqrLen = _mm_shuffle_ps(vSqrLen, vSqrLen, _MM_SHUFFLE(0, 0, 0, 0));

	// Return 
	return vSqrLen;
}

//*************************************************************************************************
// Dot product
//*************************************************************************************************
SUMINLINE Vector Vec2Dot(const Vector v1, const Vector v2)
{
	// Get values for v1.x*v2.x + v1.y*v2.y
	Vector v3 = _mm_mul_ps(v1, v2);

	// Grab y value
	Vector v4 = _mm_shuffle_ps(v3, v3, _MM_SHUFFLE(1, 1, 1, 1));

	// Get x + y
	v3 = _mm_add_ps(v3, v4);

	// Grab sum
	v3 = _mm_shuffle_ps(v3, v3, _MM_SHUFFLE(0, 0, 0, 0));

	return v3;
}

//*************************************************************************************************
// Z component of cross product
// v1.x*v2.y - v1.y*v2.x
//*************************************************************************************************
SUMINLINE Vector Vec2CCW(const Vector v1, const Vector v2)
{
	// Splat v2.y
	Vector vTemp = _mm_shuffle_ps(v2, v2, _MM_SHUFFLE(1, 1, 1, 1));

	// v1.x * v2.y
	Vector v3 = _mm_mul_ps(v1, vTemp);

	// Splat value
	v3 = _mm_shuffle_ps(v3, v3, _MM_SHUFFLE(0, 0, 0, 0));

	// Splat v2.x
	vTemp = _mm_shuffle_ps(v2, v2, _MM_SHUFFLE(0, 0, 0, 0));

	// v1.y * v2.x
	Vector v4 = _mm_mul_ps(v1, vTemp);

	// Splat value
	v4 = _mm_shuffle_ps(v4, v4, _MM_SHUFFLE(1, 1, 1, 1));

	// Subtract
	v3 = _mm_sub_ps(v3, v4);

	// Splat value
	v3 = _mm_shuffle_ps(v3, v3, _MM_SHUFFLE(0, 0, 0, 0));

	return v3;
}

//*************************************************************************************************
// Addition
//*************************************************************************************************
SUMINLINE Vector Vec2Add(const Vector v1, const Vector v2)
{
	return _mm_add_ps(v1, v2);
}

//*************************************************************************************************
// Subtraction
//*************************************************************************************************
SUMINLINE Vector Vec2Sub(const Vector v1, const Vector v2)
{
	return _mm_sub_ps(v1, v2);
}

//*************************************************************************************************
// Minimize each component
//*************************************************************************************************
SUMINLINE Vector Vec2Minimize(const Vector v1, const Vector v2)
{
	return _mm_min_ps(v1, v2);
}

//*************************************************************************************************
// Maximize each component
//*************************************************************************************************
SUMINLINE Vector Vec2Maximize(const Vector v1, const Vector v2)
{
	return _mm_max_ps(v1, v2);
}

//*************************************************************************************************
// Scale the vector
//*************************************************************************************************
SUMINLINE Vector Vec2Scale(const Vector v, float s)
{
	Vector vScale = _mm_set1_ps(s);
	return _mm_mul_ps(v, vScale);
}

//*************************************************************************************************
// Scale the vector
//*************************************************************************************************
SUMINLINE Vector Vec2Scale(const Vector v, const Vector s)
{
	return _mm_mul_ps(v, s);
}

//*************************************************************************************************
// Linear interpolation V1 + s(V2 - V1)
//*************************************************************************************************
SUMINLINE Vector Vec2Lerp(const Vector v1, const Vector v2, float s)
{
	// v2 - v1
	Vector v3 = _mm_sub_ps(v2, v1);

	// s(v3)
	Vector vTemp = _mm_set1_ps(s);
	v3 = _mm_mul_ps(v3, vTemp);

	// v1 + v3
	v3 = _mm_add_ps(v1, v3);

	return v3;
}

//*************************************************************************************************
// Linear interpolation V1 + s(V2 - V1)
//*************************************************************************************************
SUMINLINE Vector Vec2Lerp(const Vector v1, const Vector v2, const Vector s)
	{
	// v2 - v1
	Vector v3 = _mm_sub_ps(v2, v1);

	// s(v3)
	v3 = _mm_mul_ps(v3, s);

	// v1 + v3
	v3 = _mm_add_ps(v1, v3);

	return v3;
}

//*************************************************************************************************
// Normalize
//*************************************************************************************************
SUMINLINE Vector Vec2Normalize(const Vector v)
{
	// Calculate dot product
	Vector vSqrLen = _mm_mul_ps(v, v);
	Vector vTemp = _mm_shuffle_ps(vSqrLen, vSqrLen, _MM_SHUFFLE(1, 1, 1, 1));
	vSqrLen = _mm_add_ps(vSqrLen, vTemp);
	vSqrLen = _mm_shuffle_ps(vSqrLen, vSqrLen, _MM_SHUFFLE(0, 0, 0, 0));
	
	// Get length
	Vector vNorm = _mm_sqrt_ps(vSqrLen);

	// Prepare for division
	Vector vZero = _mm_setzero_ps();

	// Test for division by zero
	vZero = _mm_cmpneq_ps(vZero, vNorm);

	// Compare against infinity
	vSqrLen = _mm_cmpneq_ps(vSqrLen, gVInfinity);

	// Perform actual normalization
	vNorm = _mm_div_ps(v, vNorm);

	// If any results are infinity, set to zero
	vNorm = _mm_and_ps(vNorm, vZero);

	// Assign NaN if infinity
	Vector vTemp1 = _mm_andnot_ps(vSqrLen, gVQNaN);
	Vector vTemp2 = _mm_and_ps(vNorm, vSqrLen);
	vNorm = _mm_or_ps(vTemp1, vTemp2);

	return vNorm;
}

#else

//*************************************************************************************************
// 
//*************************************************************************************************
// Length
Vector Vec2Length(const Vector v);

//*************************************************************************************************
// 
//*************************************************************************************************
// Squared length
Vector Vec2LengthSqr(const Vector v);

//*************************************************************************************************
// 
//*************************************************************************************************
// Dot product
Vector Vec2Dot(const Vector v1, const Vector v2);

//*************************************************************************************************
// 
//*************************************************************************************************
// Z component of cross product
Vector Vec2CCW(const Vector v1, const Vector v2);

//*************************************************************************************************
// 
//*************************************************************************************************
// Addition
Vector Vec2Add(const Vector v1, const Vector v2);

//*************************************************************************************************
// 
//*************************************************************************************************
// Subtraction
Vector Vec2Sub(const Vector v1, const Vector v2);

//*************************************************************************************************
// 
//*************************************************************************************************
// Minimize each component
Vector Vec2Minimize(const Vector v1, const Vector v2);

//*************************************************************************************************
// 
//*************************************************************************************************
// Maximize each component
Vector Vec2Maximize(const Vector v1, const Vector v2);

//*************************************************************************************************
// 
//*************************************************************************************************
// Scale the vector
Vector Vec2Scale(const Vector v, float s);

//*************************************************************************************************
// 
//*************************************************************************************************
// Scale the vector
Vector Vec2Scale(const Vector v, const Vector s);

//*************************************************************************************************
// 
//*************************************************************************************************
// Linear interpolation V1 + s(V2 - V1)
Vector Vec2Lerp(const Vector v1, const Vector v2, float s);

//*************************************************************************************************
// 
//*************************************************************************************************
// Linear interpolation V1 + s(V2 - V1)
Vector Vec2Lerp(const Vector v1, const Vector v2, const Vector s);

//*************************************************************************************************
// 
//*************************************************************************************************
// Normalize
Vector Vec2Normalize(const Vector v);

#endif

//*************************************************************************************************
// 
//*************************************************************************************************
