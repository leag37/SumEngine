//*************************************************************************************************
// Title: SumQuaternion.inl
// Author: Gael Huber
// Description: Quaternion mathematics
//*************************************************************************************************

//*************************************************************************************************
// Add
//*************************************************************************************************
SUMINLINE Vector QuaternionAdd(const Vector q1, const Vector q2)
{
	return _mm_add_ps(q1, q2);
}

//*************************************************************************************************
// Subtract
//*************************************************************************************************
SUMINLINE Vector QuaternionSub(const Vector q1, const Vector q2)
{
	return _mm_sub_ps(q1, q2);
}

//*************************************************************************************************
// Scale
//*************************************************************************************************
SUMINLINE Vector QuaternionScale(const Vector q, float s)
{
	Vector vS = _mm_set1_ps(s);
	return QuaternionScale(q, vS);
}

//*************************************************************************************************
// Scale
//*************************************************************************************************
SUMINLINE Vector QuaternionScale(const Vector q, const Vector s)
{
	return _mm_mul_ps(q, s);
}

//*************************************************************************************************
// Length
//*************************************************************************************************
SUMINLINE Vector QuaternionLength(const Vector q)
{
	Vector vSqrLen = _mm_mul_ps(q, q);

	// Splat y and w
	Vector vTemp = _mm_shuffle_ps(vSqrLen, vSqrLen, _MM_SHUFFLE(3, 3, 1, 1));
	
	// Find x+y and z+w
	vSqrLen = _mm_add_ps(vSqrLen, vTemp);

	// Splat z+w
	vTemp = _mm_shuffle_ps(vSqrLen, vSqrLen, _MM_SHUFFLE(2, 2, 2, 2));
	
	// Find x+y+z+w
	vSqrLen = _mm_add_ps(vSqrLen, vTemp);

	// Splat result
	vSqrLen = _mm_shuffle_ps(vSqrLen, vSqrLen, _MM_SHUFFLE(0, 0, 0, 0));

	// Return square root
	return _mm_sqrt_ps(vSqrLen);
}

//*************************************************************************************************
// Length squared, or "norm"
//*************************************************************************************************
SUMINLINE Vector QuaternionLengthSqr(const Vector q)
{
	Vector vSqrLen = _mm_mul_ps(q, q);

	// Splat y and w
	Vector vTemp = _mm_shuffle_ps(vSqrLen, vSqrLen, _MM_SHUFFLE(3, 3, 1, 1));
	
	// Find x+y and z+w
	vSqrLen = _mm_add_ps(vSqrLen, vTemp);

	// Splat z+w
	vTemp = _mm_shuffle_ps(vSqrLen, vSqrLen, _MM_SHUFFLE(2, 2, 2, 2));
	
	// Find x+y+z+w
	vSqrLen = _mm_add_ps(vSqrLen, vTemp);

	// Splat result
	return _mm_shuffle_ps(vSqrLen, vSqrLen, _MM_SHUFFLE(0, 0, 0, 0));
}

//*************************************************************************************************
// Dot
//*************************************************************************************************
SUMINLINE Vector QuaternionDot(const Vector q1, const Vector q2)
{
	// Multiply together
	Vector vDot = _mm_mul_ps(q1, q2);

	// Splat y and w
	Vector vTemp = _mm_shuffle_ps(vDot, vDot, _MM_SHUFFLE(3, 3, 1, 1));

	// Find x+y and z+w
	vDot = _mm_add_ps(vDot, vTemp);

	// Splat z+w
	vTemp = _mm_shuffle_ps(vDot, vDot, _MM_SHUFFLE(2, 2, 2, 2));

	// Find x+y+z+w
	vDot = _mm_add_ps(vDot, vTemp);

	// Splat result and return
	return _mm_shuffle_ps(vDot, vDot, _MM_SHUFFLE(0, 0, 0, 0));
}

//*************************************************************************************************
// Identity (0, 0, 0, 1)
//*************************************************************************************************
SUMINLINE Vector QuaternionIdentity()
{
	return _mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f);
}

//*************************************************************************************************
// Is identity
//*************************************************************************************************
SUMINLINE SBOOL QuaternionIsIdentity(const Vector q)
{
	Vector vTemp = _mm_cmpeq_ps(q, gVIdentityR3);
	return (_mm_movemask_ps(vTemp) == 15) != 0;
}

//*************************************************************************************************
// Conjugate (-x, -y, -z, -w)
//*************************************************************************************************
SUMINLINE Vector QuaternionConjugate(const Vector q)
{
	return _mm_mul_ps(q, gVNegOne);
}


//*************************************************************************************************
//
//*************************************************************************************************

