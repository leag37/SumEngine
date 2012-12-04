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
