//*************************************************************************************************
// Title: SumVector.h
// Author: Gael Huber
// Description: Basic vector used as the base type for any SIMD operations
//*************************************************************************************************
#ifndef __SUMVECTOR_H__
#define __SUMVECTOR_H__

#include "SumMath.h"

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