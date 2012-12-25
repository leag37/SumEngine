//*************************************************************************************************
// Title: SumFloat.inl
// Author: Gael Huber
// Description: Non-vectorized representations of vector quantities. Primarily constructor for
//	passing data to GPU. 
//*************************************************************************************************

//*************************************************************************************************
// Load a Float2 into a vector
//*************************************************************************************************
SUMINLINE Vector LoadFloat2(const Float2* source)
{
#ifdef SUMSIMD
	Vector x = _mm_load_ss(&source->x);
	Vector y = _mm_load_ss(&source->y);
	return _mm_unpacklo_ps(x, y);
#else
#endif
}

//*************************************************************************************************
// Load a Float3 into a vector
//*************************************************************************************************
SUMINLINE Vector LoadFloat3(const Float3* source)
{
#ifdef SUMSIMD
	Vector x = _mm_load_ss(&source->x);
	Vector y = _mm_load_ss(&source->y);
	Vector z = _mm_load_ss(&source->z);
	Vector xy = _mm_unpacklo_ps(x, y);
	return _mm_movelh_ps(xy, z);
#else
#endif
}

//*************************************************************************************************
// Load a Float4 into a vector
//*************************************************************************************************
SUMINLINE Vector LoadFloat4(const Float4* source)
{
#ifdef SUMSIMD
	return _mm_loadu_ps(&source->x);
#else
#endif
}

//*************************************************************************************************
// Load a Float3x3 into a matrix
//
// [a b c]
// [d e f]
// [g h i]
//
// Want:
// [a b c 0]
// [d e f 0]
// [g h i 0]
// [0 0 0 1]
//
// Load entire contents into 3 vectors
// v1 = [a b c d]
// v2 = [e f g h]
// v3 = [i 0 0 0]
//
// Save zero for proper unpacking
// z = [0 0 0 0]
//
// FORMAT NEEDED
// t1 = _mm_unpackhi_ps(v2, z) => [g h 0 0]
// t2 = _mm_unpacklo_ps(v1, z) => [a b 0 0]
// t3 = _mm_unpackhi_ps(v1, z) => [c d 0 0]
// t4 = _mm_shuffle_ps(t3, v2, _MM_SHUFFLE(0, 0, 1, 1)) => [d d e e]
// t5 = _mm_shuffle_ps(v2, v3, _MM_SHUFFLE(1, 1, 1, 1) => [f f 0 0] 
//
// m.r[0] = _mm_shuffle_ps(t2, t3, _MM_SHUFFLE(3, 0, 1, 0)) => [a b c 0]
// m.r[1] = _mm_shuffle_ps(t4, t5, _MM_SHUFFLE(3, 1, 3, 1)) => [d e f 0]
// m.r[2] = _mm_unpacklo_ps(t1, v3) => [g h i 0]
// m.r[3] = gVIdentityR3
//*************************************************************************************************
SUMINLINE Matrix LoadFloat3x3(const Float3x3* source)
{
#ifdef SUMSIMD
	// Load the entire contents of the matrix into 3 vectors
	Vector v1 = _mm_loadu_ps(&source->m[0][0]);
	Vector v2 = _mm_loadu_ps(&source->m[1][1]);
	Vector v3 = _mm_load_ss(&source->m[2][2]);

	// Grab a zero vector to ensure data can be unpacked properly
	Vector z = _mm_setzero_ps();

	// Unpack into a set of temporary vectors used to create matrix
	Vector t1 = _mm_unpackhi_ps(v2, z);
	Vector t2 = _mm_unpacklo_ps(v1, z);
	Vector t3 = _mm_unpackhi_ps(v1, z);
	Vector t4 = _mm_shuffle_ps(t3, v2, _MM_SHUFFLE(0, 0, 1, 1));
	Vector t5 = _mm_shuffle_ps(v2, v3, _MM_SHUFFLE(1, 1, 1, 1));

	// Create matrix
	Matrix m;
	m.r[0] = _mm_shuffle_ps(t2, t3, _MM_SHUFFLE(3, 0, 1, 0));
	m.r[1] = _mm_shuffle_ps(t4, t5, _MM_SHUFFLE(3, 1, 3, 1));
	m.r[2] = _mm_unpacklo_ps(t1, v3);
	m.r[3] = gVIdentityR3;
	return m;
#else
#endif
}

//*************************************************************************************************
//
//*************************************************************************************************
Matrix LoadFloat4x3(const Float4x3* source);

//*************************************************************************************************
// Load a Float4x4 into a destination matrix
//*************************************************************************************************
SUMINLINE Matrix LoadFloat4x4(const Float4x4* source)
{
	Matrix m;
	m.r[0] = _mm_loadu_ps(source->m[0]);
	m.r[1] = _mm_loadu_ps(source->m[1]);
	m.r[2] = _mm_loadu_ps(source->m[2]);
	m.r[3] = _mm_loadu_ps(source->m[3]);
	return m;
}

//*************************************************************************************************
// Store a Vector into a Float2
//*************************************************************************************************
SUMINLINE void StoreFloat2(Float2* destination, const Vector v)
{
	Vector vTemp = _mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 1, 1, 1));
	_mm_store_ss(&destination->x, v);
	_mm_store_ss(&destination->y, vTemp);
}

//*************************************************************************************************
// Store a vector into a Float3
//*************************************************************************************************
SUMINLINE void StoreFloat3(Float3* destination, const Vector v)
{
	Vector vTemp1 = _mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 1, 1, 1));
	Vector vTemp2 = _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 2, 2, 2));
	_mm_store_ss(&destination->x, v);
	_mm_store_ss(&destination->y, vTemp1);
	_mm_store_ss(&destination->z, vTemp2);
}

//*************************************************************************************************
// Store a vector into a Float4
//*************************************************************************************************
SUMINLINE void StoreFloat4(Float4* destination, const Vector v)
{
	_mm_storeu_ps(&destination->x, v);
}

//*************************************************************************************************
//
//*************************************************************************************************
void StoreFloat3x3(Float3x3* destination, const Matrix& m);

//*************************************************************************************************
//
//*************************************************************************************************
void StoreFloat4x3(Float4x3* destination, const Matrix& m);

//*************************************************************************************************
// Store a Matrix into a Float4x4
//*************************************************************************************************
SUMINLINE void StoreFloat4x4(Float4x4* destination, const Matrix& m)
{
	_mm_storeu_ps(destination->m[0], m.r[0]);
	_mm_storeu_ps(destination->m[1], m.r[1]);
	_mm_storeu_ps(destination->m[2], m.r[2]);
	_mm_storeu_ps(destination->m[3], m.r[3]);
}
