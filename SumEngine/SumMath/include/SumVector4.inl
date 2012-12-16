//*************************************************************************************************
// Title: SumVector4.inl
// Author: Gael Huber
// Description: Vector 4 mathematics.
//*************************************************************************************************

//*************************************************************************************************
// Equality
//*************************************************************************************************
SUMINLINE SBOOL Vec4Equal(const Vector v1, const Vector v2)
{
	Vector vTemp = _mm_cmpeq_ps(v1, v2);
	return ((_mm_movemask_ps(vTemp) == 15) != 0);
}

//*************************************************************************************************
// Non-Equality
//*************************************************************************************************
SUMINLINE SBOOL Vec4NonEqual(const Vector v1, const Vector v2)
{
	Vector vTemp = _mm_cmpeq_ps(v1, v2);
	return ((_mm_movemask_ps(vTemp) != 15) != 0);
}

//*************************************************************************************************
// Length 
//*************************************************************************************************
SUMINLINE Vector Vec4Length(const Vector v)
{
	// Multiply by self
	Vector vSqrLen = _mm_mul_ps(v, v);

	// Splat y and w
	Vector vTemp = _mm_shuffle_ps(vSqrLen, vSqrLen, _MM_SHUFFLE(3, 3, 1, 1));

	// Add to get (x+y, y+y, z+w, w+w)
	vSqrLen = _mm_add_ps(vSqrLen, vTemp);

	// Splat z
	vTemp = _mm_shuffle_ps(vSqrLen, vSqrLen, _MM_SHUFFLE(2, 2, 2, 2));

	// Add to get (x+y+z+w, y+y+z+w, z+w+z+w, w+w+z+w)
	vSqrLen = _mm_add_ps(vSqrLen, vTemp);

	// Splat x
	vSqrLen = _mm_shuffle_ps(vSqrLen, vSqrLen, _MM_SHUFFLE(0, 0, 0, 0));

	// Take the square root and return the result
	return _mm_sqrt_ps(vSqrLen);
}

//*************************************************************************************************
// Squared length
//*************************************************************************************************
SUMINLINE Vector Vec4LengthSqr(const Vector v)
{
	// Multiply by self
	Vector vSqrLen = _mm_mul_ps(v, v);

	// Splat y and w
	Vector vTemp = _mm_shuffle_ps(vSqrLen, vSqrLen, _MM_SHUFFLE(3, 3, 1, 1));

	// Add to get (x+y, y+y, z+w, w+w)
	vSqrLen = _mm_add_ps(vSqrLen, vTemp);

	// Splat z
	vTemp = _mm_shuffle_ps(vSqrLen, vSqrLen, _MM_SHUFFLE(2, 2, 2, 2));

	// Add to get (x+y+z+w, y+y+z+w, z+w+z+w, w+w+z+w)
	vSqrLen = _mm_add_ps(vSqrLen, vTemp);

	// Splat x
	return _mm_shuffle_ps(vSqrLen, vSqrLen, _MM_SHUFFLE(0, 0, 0, 0));
}

//*************************************************************************************************
// Dot product
//*************************************************************************************************
SUMINLINE Vector Vec4Dot(const Vector v1, const Vector v2)
{
	// Multiply by self
	Vector vSqrLen = _mm_mul_ps(v1, v2);

	// Splat y and w
	Vector vTemp = _mm_shuffle_ps(vSqrLen, vSqrLen, _MM_SHUFFLE(3, 3, 1, 1));

	// Add to get (x+y, y+y, z+w, w+w)
	vSqrLen = _mm_add_ps(vSqrLen, vTemp);

	// Splat z
	return _mm_shuffle_ps(vSqrLen, vSqrLen, _MM_SHUFFLE(2, 2, 2, 2));
}

//*************************************************************************************************
// Add
//*************************************************************************************************
SUMINLINE Vector Vec4Add(const Vector v1, const Vector v2)
{
	return _mm_add_ps(v1, v2);
}

//*************************************************************************************************
// Subtract
//*************************************************************************************************
SUMINLINE Vector Vec4Sub(const Vector v1, const Vector v2)
{
	return _mm_sub_ps(v1, v2);
}

//*************************************************************************************************
// Minimize
//*************************************************************************************************
SUMINLINE Vector Vec4Minimize(const Vector v1, const Vector v2)
{
	return _mm_min_ps(v1, v2);
}

//*************************************************************************************************
//  Maximize
//*************************************************************************************************
SUMINLINE Vector Vec4Maximize(const Vector v1, const Vector v2)
{
	return _mm_max_ps(v1, v2);
}

//*************************************************************************************************
// Scale
//*************************************************************************************************
SUMINLINE Vector Vec4Scale(const Vector v, float s)
{
	Vector vS = _mm_set1_ps(s);
	return Vec4Scale(v, vS);
}

//*************************************************************************************************
// Scale
//*************************************************************************************************
SUMINLINE Vector Vec4Scale(const Vector v, Vector s)
{
	return _mm_mul_ps(v, s);
}

//*************************************************************************************************
// Lerp
//*************************************************************************************************
SUMINLINE Vector Vec4Lerp(const Vector v1, const Vector v2, float s)
{
	Vector vS = _mm_set1_ps(s);
	return Vec4Lerp(v1, v2, vS);
}

//*************************************************************************************************
// Lerp v3 = v1 + s(v2 - v1)
//*************************************************************************************************
SUMINLINE Vector Vec4Lerp(const Vector v1, const Vector v2, Vector s)
{
	Vector vTemp = _mm_sub_ps(v2, v1);
	vTemp = _mm_mul_ps(vTemp, s);
	return _mm_add_ps(v1, vTemp);
}