//*************************************************************************************************
// Title: SumFloat.h
// Author: Gael Huber
// Description: Non-vectorized representations of vector quantities. Primarily constructor for
//	passing data to GPU. 
// 
// TODO: Implement Float2, Float3, Float4, Float3x3, Float4x3, Float4x4
//*************************************************************************************************
#ifndef __SUMFLOAT_H__
#define __SUMFLOAT_H__

#include "SumMath.h"

// 2D Vector
typedef struct _Float2
{
	SFLOAT x;
	SFLOAT y;

	_Float2();
	_Float2(SFLOAT _x, SFLOAT _y);
	_Float2(const SFLOAT* p);

	_Float2& operator=(const _Float2& rhs);
} Float2;

// 3D Vector
typedef struct _Float3
{
	SFLOAT x;
	SFLOAT y;
	SFLOAT z;

	_Float3();
	_Float3(SFLOAT _x, SFLOAT _y, SFLOAT _z);
	_Float3(const SFLOAT* p);

	_Float3& operator=(const _Float3& rhs);
} Float3;

// 4D Vector
typedef struct _Float4
{
	SFLOAT x;
	SFLOAT y;
	SFLOAT z;
	SFLOAT w;

	_Float4();
	_Float4(SFLOAT _x, SFLOAT _y, SFLOAT _z, SFLOAT _w);
	_Float4(const SFLOAT* p);

	_Float4& operator=(const _Float4& rhs);
} Float4;

// 3x3 matrix
typedef struct _Float3x3
{
	union
	{
		struct
		{
			SFLOAT _11, _12, _13;
			SFLOAT _21, _22, _23;
			SFLOAT _31, _32, _33;
		};
		SFLOAT m[3][3];
	};

	// Constructors
	_Float3x3();
	_Float3x3(	SFLOAT m11, SFLOAT m12, SFLOAT m13,
				SFLOAT m21, SFLOAT m22, SFLOAT m23,
				SFLOAT m31, SFLOAT m32, SFLOAT m33);
	_Float3x3(const SFLOAT* m);

	// Accessors
	SFLOAT operator() (SUINT row, SUINT column) const;
	SFLOAT& operator() (SUINT row, SUINT column);

	// Assignment
	_Float3x3& operator=(const _Float3x3& rhs);

} Float3x3;

// 4x3 matrix
typedef struct _Float4x3
{
	union
	{
		struct
		{
			SFLOAT _11, _12, _13;
			SFLOAT _21, _22, _23;
			SFLOAT _31, _32, _33;
			SFLOAT _41, _42, _43;
		};
		SFLOAT m[4][3];
	};

	// Constructors
	_Float4x3();
	_Float4x3(	SFLOAT m11, SFLOAT m12, SFLOAT m13,
				SFLOAT m21, SFLOAT m22, SFLOAT m23,
				SFLOAT m31, SFLOAT m32, SFLOAT m33,
				SFLOAT m41, SFLOAT m42, SFLOAT m43);
	_Float4x3(const SFLOAT* m);

	// Accessors
	SFLOAT operator() (SUINT row, SUINT column) const;
	SFLOAT& operator() (SUINT row, SUINT column);

	// Assignment
	_Float4x3& operator=(const _Float4x3& rhs);

} Float4x3;

// 4x4 matrix
typedef struct _Float4x4
{
	union
	{
		struct
		{
			SFLOAT _11, _12, _13, _14;
			SFLOAT _21, _22, _23, _24;
			SFLOAT _31, _32, _33, _34;
			SFLOAT _41, _42, _43, _44;
		};
		SFLOAT m[4][4];
	};

	// Constructors
	_Float4x4();
	_Float4x4(	SFLOAT m11, SFLOAT m12, SFLOAT m13, SFLOAT m14,
				SFLOAT m21, SFLOAT m22, SFLOAT m23, SFLOAT m24,
				SFLOAT m31, SFLOAT m32, SFLOAT m33, SFLOAT m34,
				SFLOAT m41, SFLOAT m42, SFLOAT m43, SFLOAT m44);
	_Float4x4(const SFLOAT* m);

	// Accessors
	SFLOAT operator() (SUINT row, SUINT column) const;
	SFLOAT& operator() (SUINT row, SUINT column);

	// Assignment
	_Float4x4& operator=(const _Float4x4& rhs);

} Float4x4;


// Load operations
Vector LoadFloat2(const Float2* source);
Vector LoadFloat3(const Float3* source);
Vector LoadFloat4(const Float4* source);
Matrix LoadFloat3x3(const Float3x3* source);
Matrix LoadFloat4x3(const Float4x3* source);
Matrix LoadFloat4x4(const Float4x4* source);

// Store operations
void StoreFloat2(Float2* destination, const Vector v);
void StoreFloat3(Float3* destination, const Vector v);
void StoreFloat4(Float4* destination, const Vector v);
void StoreFloat3x3(Float3x3* destination, const Matrix& m);
void StoreFloat4x3(Float4x3* destination, const Matrix& m);
void StoreFloat4x4(Float4x4* destination, const Matrix& m);

#include "SumFloat.inl"

#endif // SUMFLOATS