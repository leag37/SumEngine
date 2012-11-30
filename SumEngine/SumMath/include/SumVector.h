//*************************************************************************************************
// Title: SumVector.h
// Author: Gael Huber
// Description: Basic vector used as the base type for any SIMD operations
//*************************************************************************************************
#ifndef __SUMVECTOR_H__
#define __SUMVECTOR_H__

#include "SumMath.h"

// Define a basic vector type
#ifdef SUMSIMD
typedef __m128 Vector;
#else
typedef struct Vector
{
	union
	{
		SFLOAT vector_f32[4];
		SUINT vector_u32[4];
		struct
		{
			SFLOAT x;
			SFLOAT y;
			SFLOAT z;
			SFLOAT w;
		};
		SFLOAT v[4];
		SUINT u[4];
	};
};
#endif // SUMSIMD

// Define conversions for vector types
//***********************************************

// 4x 32-bit floating point values
typedef SUM_DECLSPEC_ALIGN_16 struct VectorF32 
{
	union
	{
		float f[4];
		Vector v;
	};

	// Casting operators
	SUMINLINE_F operator Vector() const { return v; }
	SUMINLINE_F operator __m128i() const { return reinterpret_cast<const __m128i*>(&v)[0]; }
	SUMINLINE_F operator __m128d() const { return reinterpret_cast<const __m128d*>(&v)[0]; }
};

// 4x 32-bit integers
typedef SUM_DECLSPEC_ALIGN_16 struct VectorI32
{
	union
	{
		SINT i[4];
		Vector v;
	};

	// Casting operators
	SUMINLINE_F operator Vector() const { return v; }
	SUMINLINE_F operator __m128i() const { return reinterpret_cast<const __m128i*>(&v)[0]; }
	SUMINLINE_F operator __m128d() const { return reinterpret_cast<const __m128d*>(&v)[0]; }
};	

// 16x 8-bit unsigned chars
typedef SUM_DECLSPEC_ALIGN_16 struct VectorU8
{
	union
	{
		SUCHAR u[16];
		Vector v;
	};

	// Casting operators
	SUMINLINE_F operator Vector() const { return v; }
	SUMINLINE_F operator __m128i() const { return reinterpret_cast<const __m128i*>(&v)[0]; }
	SUMINLINE_F operator __m128d() const { return reinterpret_cast<const __m128d*>(&v)[0]; }
};

// 4x 32-bit unsigned integers
typedef SUM_DECLSPEC_ALIGN_16 struct VectorU32
{
	union
	{
		SUINT u[4];
		Vector v;
	};

	// Casting operators
	SUMINLINE_F operator Vector() const { return v; }
	SUMINLINE_F operator __m128i() const { return reinterpret_cast<const __m128i*>(&v)[0]; }
	SUMINLINE_F operator __m128d() const { return reinterpret_cast<const __m128d*>(&v)[0]; }
};

// Standard vector operations
Vector operator+ (const	Vector v);
Vector operator- (const Vector v);

Vector& operator+= (Vector& v1, const Vector v2);
Vector& operator-= (Vector& v1, const Vector v2);
Vector& operator*= (Vector& v1, const Vector v2);
Vector& operator/= (Vector& v1, const Vector v2);
Vector& operator*= (Vector& v, const SFLOAT s);
Vector& operator/= (Vector& v, const SFLOAT s);

Vector operator+ (const Vector v1, const Vector v2);
Vector operator- (const Vector v1, const Vector v2);
Vector operator* (const Vector v1, const Vector v2);
Vector operator/ (const Vector v1, const Vector v2);
Vector operator* (const Vector v, const SFLOAT s);
Vector operator* (const SFLOAT s, const Vector v);
Vector operator/ (const Vector v, const SFLOAT s);

Vector VectorZero();
Vector VectorSet(SFLOAT x, SFLOAT y, SFLOAT z, SFLOAT w);
Vector VectorNegate(Vector v);
Vector VectorScale(const Vector v, const SFLOAT s);
Vector VectorAdd(const Vector v1, const Vector v2);
Vector VectorSub(const Vector v1, const Vector v2);
Vector VectorMul(const Vector v1, const Vector v2);
Vector VectorDiv(const Vector v1, const Vector v2);
Vector VectorEqual(const Vector v1, const Vector v2);
Vector VectorNotEqual(const Vector v1, const Vector v2);

#include "SumVector.inl"

#endif // SUMVECTOR