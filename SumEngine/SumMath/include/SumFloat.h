
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

// 2x2 matrix
typedef struct _Float2x2
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
	_Float2x2();
	_Float2x2(	SFLOAT m11, SFLOAT m12, SFLOAT m13,
				SFLOAT m21, SFLOAT m22, SFLOAT m23,
				SFLOAT m31, SFLOAT m32, SFLOAT m33);
	_Float2x2(const SFLOAT* m);

	// Accessors
	
	// Assignment
} Float2x2;


// Load operations
Vector LoadFloat2(const Float2* source);

// Store operations
void StoreFloat2(Float2* destination, const Vector v);

//#include "SumFloat.inl"

#endif // SUMFLOATS