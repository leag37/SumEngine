//*************************************************************************************************
// Title: SumVector.h
// Author: Gael Huber
// Description: Basic vector used as the base type for any SIMD operations
//*************************************************************************************************
#ifndef __SUMVECTOR_H__
#define __SUMVECTOR_H__

#include "SumMath.h"

// Swizzle macro
#define SUM_SWIZZLE(x, y, z, w) ((w << 6) | (z << 4) | (y << 2) | x)

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
Vector VectorMax(const Vector v1, const Vector v2);
Vector VectorScale(const Vector v, const SFLOAT s);
Vector VectorAdd(const Vector v1, const Vector v2);
Vector VectorSub(const Vector v1, const Vector v2);
Vector VectorMul(const Vector v1, const Vector v2);
Vector VectorDiv(const Vector v1, const Vector v2);
Vector VectorSqrt(const Vector v);
SBOOL VectorCompareEqual(const Vector v1, const Vector v2);
SBOOL VectorCompareNotEqual(const Vector v1, const Vector v2);
SBOOL VectorCompareGreaterThan(const Vector v1, const Vector v2);
Vector VectorEqual(const Vector v1, const Vector v2);
Vector VectorNotEqual(const Vector v1, const Vector v2);
Vector VectorReciprocal(const Vector v);
Vector VectorReplicate(SFLOAT v);
Vector VectorSplatX(const Vector v);
Vector VectorSplatY(const Vector v);
Vector VectorSplatZ(const Vector v);
Vector VectorSplatW(const Vector v);
Vector VectorSetX(const Vector v, SFLOAT x);
Vector VectorSetY(const Vector v, SFLOAT y);
Vector VectorSetZ(const Vector v, SFLOAT z);
Vector VectorSetW(const Vector v, SFLOAT w);
SFLOAT VectorGetX(const Vector v);
SFLOAT VectorGetY(const Vector v);
SFLOAT VectorGetZ(const Vector v);
SFLOAT VectorGetW(const Vector v);
Vector VectorAnd(const Vector v1, const Vector v2);
Vector VectorOr(const Vector v1, const Vector v2);

// Swizzle operations (defined differently on SIMD vs. non-SIMD
#ifdef SUMSIMD

#ifndef VectorSwizzle
#define VectorSwizzle(v1, v2, mask) _mm_shuffle_ps(v1, v2, mask);
#endif // VectorSwizzle

//typedef Vector (*VectorSwizzle)(Vector a, Vector b, SUINT mask);
//typedef *_mm_shuffle_ps *VectorSwizzle;
//typedef _mm_shuffle_ps VectorSwizzle;

//SUMGLOBALCONST VecSwizzle VectorSwizzle = _mm_shuffle_ps;
#else
Vector VectorSwizzle(const Vector v1, const Vector v2, const SUINT mask);
#endif

#include "SumVector.inl"

#endif // SUMVECTOR