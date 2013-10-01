//*************************************************************************************************
// Title: SumVector.inl
// Author: Gael Huber
// Description: Basic vector used as the base type for any SIMD operations
//*************************************************************************************************

//*************************************************************************************************
// Cast to positive version of the vector
//*************************************************************************************************
SUMINLINE Vector operator+ (const Vector v)
{
	return v;
}

//*************************************************************************************************
// Cast to negated version of the vector
//*************************************************************************************************
SUMINLINE Vector operator- (const Vector v)
{
	return VectorNegate(v);
}

//*************************************************************************************************
// Addition of two vectors
//*************************************************************************************************
SUMINLINE Vector& operator+= (Vector& v1, const Vector v2)
{
	v1 = VectorAdd(v1, v2);
	return v1;
}

//*************************************************************************************************
// Subtraction of two vectors
//*************************************************************************************************
SUMINLINE Vector& operator-= (Vector& v1, const Vector v2)
{
	v1 = VectorSub(v1, v2);
	return v1;
}

//*************************************************************************************************
// Product of two vectors
//*************************************************************************************************
SUMINLINE Vector& operator*= (Vector& v1, const Vector v2)
{
	v1 = VectorMul(v1, v2);
	return v1;
}

//*************************************************************************************************
// Division of two vectors
//*************************************************************************************************
SUMINLINE Vector& operator/= (Vector& v1, const Vector v2)
{
	v1 = VectorDiv(v1, v2);
	return v1;
}

//*************************************************************************************************
// Multiply a vector by a scalar
//*************************************************************************************************
SUMINLINE Vector& operator*= (Vector& v, SFLOAT s)
{
	v = VectorScale(v, s);
	return v;
}

//*************************************************************************************************
// Divide by a scalar
//*************************************************************************************************
SUMINLINE Vector& operator/= (Vector& v, SFLOAT s)
{
	v = VectorScale(v, 1.0f / s);
	return v;
}

//*************************************************************************************************
// Addition of two vectors
//*************************************************************************************************
SUMINLINE Vector operator+ (const Vector v1, const Vector v2)
{
	return VectorAdd(v1, v2);
}

//*************************************************************************************************
// Difference between two vectors
//*************************************************************************************************
SUMINLINE Vector operator- (const Vector v1, const Vector v2)
{
	return VectorSub(v1, v2);
}

//*************************************************************************************************
// Product of two vectors
//*************************************************************************************************
SUMINLINE Vector operator* (const Vector v1, const Vector v2)
{
	return VectorMul(v1, v2);
}

//*************************************************************************************************
// Division of two vectors
//*************************************************************************************************
SUMINLINE Vector operator/ (const Vector v1, const Vector v2)
{
	return VectorDiv(v1, v2);
}

//*************************************************************************************************
// Scale a vector by a scalar
//*************************************************************************************************
SUMINLINE Vector operator* (const Vector v, const SFLOAT s)
{
	return VectorScale(v, s);
}

//*************************************************************************************************
// Scale a vector by a scalar
//*************************************************************************************************
SUMINLINE Vector operator* (const SFLOAT s, const Vector v)
{
	return VectorScale(v, s);
}

//*************************************************************************************************
// Scale a vector by a scalar
//*************************************************************************************************
SUMINLINE Vector operator/ (const Vector v, const SFLOAT s)
{
	return VectorScale(v, 1.0f / s);
}

//*************************************************************************************************
// Return a zeroed vector
//*************************************************************************************************
SUMINLINE Vector VectorZero()
{
#ifdef SUMSIMD
	return _mm_setzero_ps();
#else
	return {0.0f, 0.0f, 0.0f, 0.0f};
#endif
}

//*************************************************************************************************
// Vector setting operations
//*************************************************************************************************
SUMINLINE Vector VectorSet(SFLOAT x, SFLOAT y, SFLOAT z, SFLOAT w)
{
#ifdef SUMSIMD
	return _mm_set_ps(w, z, y, x);
#else
	return {x, y, z, w};
#endif
}

//*************************************************************************************************
// Negate a vector
//*************************************************************************************************
SUMINLINE Vector VectorNegate(Vector v)
{
#ifdef SUMSIMD
	Vector z = _mm_setzero_ps();
	return _mm_sub_ps(z, v);
#else
	Vector result;
	result.vector_f32[0] = -v.vector_f32[0];
	result.vector_f32[1] = -v.vector_f32[1];
	result.vector_f32[2] = -v.vector_f32[2];
	result.vector_f32[3] = -v.vector_f32[3];
#endif
}

//*************************************************************************************************
// Max values of a vector
//*************************************************************************************************
SUMINLINE Vector VectorMax(const Vector v1, const Vector v2)
{
#ifdef SUMSIMD
	return _mm_max_ps(v1, v2);
#else	// SUMSIMD
	Vector result = 
	{
		v1.x > v2.x ? v1.x : v2.x,
		v1.y > v2.y ? v1.y : v2.y,
		v1.z > v2.z ? v1.z : v2.z,
		v1.w > v2.w ? v1.w : v2.w
	};
	return result;
#endif	// SUMSIMD
}

//*************************************************************************************************
// Scale a vector by a scalar
//*************************************************************************************************
SUMINLINE Vector VectorScale(const Vector v, const SFLOAT s)
{
#ifdef SUMSIMD
	Vector scale = _mm_set1_ps(s);
	return _mm_mul_ps(v, scale);
#else
	Vector result;
	result.vector_f32[0] = v.vector_f32[0] * s;
	result.vector_f32[1] = v.vector_f32[1] * s;
	result.vector_f32[2] = v.vector_f32[2] * s;
	result.vector_f32[3] = v.vector_f32[3] * s;
#endif
}

//*************************************************************************************************
// Sum of two vectors
//*************************************************************************************************
SUMINLINE Vector VectorAdd(const Vector v1, const Vector v2)
{
#ifdef SUMSIMD
	return _mm_add_ps(v1, v2);
#else
	Vector result;
	result.vector_f32[0] = v1.vector_f32[0] + v2.vector_f32[0];
	result.vector_f32[1] = v1.vector_f32[1] + v2.vector_f32[1];
	result.vector_f32[2] = v1.vector_f32[2] + v2.vector_f32[2];
	result.vector_f32[3] = v1.vector_f32[3] + v2.vector_f32[3];
	return result;
#endif
}

//*************************************************************************************************
// Difference between two vectors
//*************************************************************************************************
SUMINLINE Vector VectorSub(const Vector v1, const Vector v2)
{
#ifdef SUMSIMD
	return _mm_sub_ps(v1, v2);
#else
	Vector result;
	result.vector_f32[0] = v1.vector_f32[0] - v2.vector_f32[0];
	result.vector_f32[1] = v1.vector_f32[1] - v2.vector_f32[1];
	result.vector_f32[2] = v1.vector_f32[2] - v2.vector_f32[2];
	result.vector_f32[3] = v1.vector_f32[3] - v2.vector_f32[3];
	return result;
#endif
}

//*************************************************************************************************
// Product of two vectors
//*************************************************************************************************
SUMINLINE Vector VectorMul(const Vector v1, const Vector v2)
{
#ifdef SUMSIMD
	return _mm_mul_ps(v1, v2);
#else
	Vector result;
	result.vector_f32[0] = v1.vector_f32[0] * v2.vector_f32[0];
	result.vector_f32[1] = v1.vector_f32[1] * v2.vector_f32[1];
	result.vector_f32[2] = v1.vector_f32[2] * v2.vector_f32[2];
	result.vector_f32[3] = v1.vector_f32[3] * v2.vector_f32[3];
	return result;
#endif
}

//*************************************************************************************************
// Division of two vectors
//*************************************************************************************************
SUMINLINE Vector VectorDiv(const Vector v1, const Vector v2)
{
#ifdef SUMSIMD
	return _mm_div_ps(v1, v2);
#else
	Vector result;
	result.vector_f32[0] = v1.vector_f32[0] / v2.vector_f32[0];
	result.vector_f32[1] = v1.vector_f32[1] / v2.vector_f32[1];
	result.vector_f32[2] = v1.vector_f32[2] / v2.vector_f32[2];
	result.vector_f32[3] = v1.vector_f32[3] / v2.vector_f32[3];
	return result;
#endif
}

//*************************************************************************************************
// Square root of a vector
//*************************************************************************************************
SUMINLINE Vector VectorSqrt(const Vector v)
{
#ifdef SUMSIMD
	return _mm_sqrt_ps(v);
#else
#endif
}

//*************************************************************************************************
// Equality of two vectors
//*************************************************************************************************
SUMINLINE Vector VectorEqual(const Vector v1, const Vector v2)
{
#ifdef SUMSIMD
	return _mm_cmpeq_ps(v1, v2);
#else
#endif
}

//*************************************************************************************************
// Compare for equality and return boolean value
//*************************************************************************************************
SUMINLINE SBOOL VectorCompareEqual(const Vector v1, const Vector v2)
{
#ifdef SUMSIMD
	Vector cmp = _mm_cmpeq_ps(v1, v2);
	SINT mask = _mm_movemask_ps(cmp);
	return mask == 15;
#else
#endif
}

//*************************************************************************************************
// Compare for equality and return boolean value
//*************************************************************************************************
SUMINLINE SBOOL VectorCompareNotEqual(const Vector v1, const Vector v2)
{
#ifdef SUMSIMD
	Vector cmp = _mm_cmpneq_ps(v1, v2);
	SINT mask = _mm_movemask_ps(cmp);
	return mask > 0;
#else
#endif
}

//*************************************************************************************************
// Compare for greater than and return the boolean value
//*************************************************************************************************
SUMINLINE SBOOL VectorCompareGreaterThan(const Vector v1, const Vector v2)
{
#ifdef SUMSIMD
	Vector cmp = _mm_cmpgt_ps(v1, v2);
	SINT mask = _mm_movemask_ps(cmp);
	return mask == 15;
#else
#endif
}

//*************************************************************************************************
// Division of two vectors
//*************************************************************************************************
SUMINLINE Vector VectorNotEqual(const Vector v1, const Vector v2)
{
#ifdef SUMSIMD
	return _mm_cmpneq_ps(v1, v2);
#else
#endif
}

//*************************************************************************************************
// Return the reciprocal of a vector
//*************************************************************************************************
SUMINLINE Vector VectorReciprocal(const Vector v)
{
	return _mm_div_ps(gVOne, v);
}

//*************************************************************************************************
// Replicate a float value across a vector
//*************************************************************************************************
SUMINLINE Vector VectorReplicate(SFLOAT v)
{
#ifdef SUMSIMD
	return _mm_set1_ps(v);
#else
#endif
}

SUMINLINE Vector VectorSplatX(const Vector v)
{
	return _mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 0, 0, 0));
}

SUMINLINE Vector VectorSplatY(const Vector v)
{
	return _mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 1, 1, 1));
}

SUMINLINE Vector VectorSplatZ(const Vector v)
{
	return _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 2, 2, 2));
}

SUMINLINE Vector VectorSplatW(const Vector v)
{
	return _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 3, 3, 3));
}

//Vector VectorSetX(const Vector v, SFLOAT x);
//Vector VectorSetY(const Vector v, SFLOAT y);
//Vector VectorSetZ(const Vector v, SFLOAT z);
//Vector VectorSetW(const Vector v, SFLOAT w);

SUMINLINE SFLOAT VectorGetX(const Vector v)
{
#ifdef SUMSIMD
	return v.m128_f32[0];
#else
#endif
}

SUMINLINE SFLOAT VectorGetY(const Vector v)
{
#ifdef SUMSIMD
	return v.m128_f32[1];
#else
#endif
}

SUMINLINE SFLOAT VectorGetZ(const Vector v)
{
#ifdef SUMSIMD
	return v.m128_f32[2];
#else
#endif
}

SUMINLINE SFLOAT VectorGetW(const Vector v)
{
#ifdef SUMSIMD
	return v.m128_f32[3];
#else
#endif
}
	
//*************************************************************************************************
// And operation on vector
//*************************************************************************************************
SUMINLINE Vector VectorAnd(const Vector v1, const Vector v2)
{
#ifdef SUMSIMD
	return _mm_and_ps(v1, v2);
#else
#endif
}

//*************************************************************************************************
// Or operation on vector
//*************************************************************************************************
SUMINLINE Vector VectorOr(const Vector v1, const Vector v2)
{
#ifdef SUMSIMD
	return _mm_or_ps(v1, v2);
#else
#endif
}

//// Swizzle operation
//SUMINLINE Vector VectorSwizzle(const Vector v1, const Vector v2, 
//	SUINT x, SUINT y, SUINT z, SUINT w)
//{
//#ifdef SUMSIMD
//	return _mm_shuffle_ps(v1, v2, SUM_SWIZZLE(x, y, z, w));
//#else
//#endif
//}
