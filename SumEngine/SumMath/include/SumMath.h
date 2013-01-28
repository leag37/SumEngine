//*************************************************************************************************
// Title: SumMath.h
// Author: Gael Huber
// Description: General purpose file for defining various mathematical features to be used in the
//	program.
//*************************************************************************************************
#ifndef __SUMMATH_H__
#define __SUMMATH_H__

#include <SumInclude.h>
//#include "SumAlign.h"
//#include <immintrin.h>
#include <math.h>
//
//*************************************************************************************************
// GENERAL PURPOSE
//*************************************************************************************************
namespace Math
{
#define S_PI 3.141592654f
#define S_PId 3.141592654
#define S_2PI 6.283185307f
#define S_2PId 6.283185307

#define ToRadian(degree) ((degree) * (S_PI / 180.0f))
#define ToDegree(radian) ((radian) * (180.0f / S_PI))
#define ToRadian_d(degree) ((degree) * (S_PId / 180.0))
#define ToDegree_d(radian) ((radian * (180.0 / S_PId))
}

//*************************************************************************************************
// DEFINITIONS
//*************************************************************************************************

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
typedef SUM_DECLSPEC_ALIGN_16 struct _VectorF32 
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
} VectorF32;

// 4x 32-bit integers
typedef SUM_DECLSPEC_ALIGN_16 struct _VectorI32
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
} VectorI32;	

// 16x 8-bit unsigned chars
typedef SUM_DECLSPEC_ALIGN_16 struct _VectorU8
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
} VectorU8;

// 4x 32-bit unsigned integers
typedef SUM_DECLSPEC_ALIGN_16 struct _VectorU32
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
} VectorU32;

// MATRIX
typedef SUM_DECLSPEC_ALIGN_16 struct _Matrix
{
	// Primary data structure
	union
	{
		Vector r[4];
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
	_Matrix();
	_Matrix(const Vector r0, const Vector r1, const Vector r2, const Vector& r3);
	_Matrix(SFLOAT m11, SFLOAT m12, SFLOAT m13, SFLOAT m14,
			SFLOAT m21, SFLOAT m22, SFLOAT m23, SFLOAT m24,
			SFLOAT m31, SFLOAT m32, SFLOAT m33, SFLOAT m34,
			SFLOAT m41, SFLOAT m42, SFLOAT m43, SFLOAT m44);
	_Matrix(const SFLOAT* m);

	// Accessors
	SFLOAT operator() (SUINT row, SUINT column) const;
	SFLOAT& operator() (SUINT row, SUINT column);

	// Assignment operator
	_Matrix& operator=(const _Matrix& m);

	// Matrix multiplication
	_Matrix& operator*=(const _Matrix& m);
	_Matrix operator*(const _Matrix& m) const;
} Matrix;


//*************************************************************************************************
// GLOBALS
//*************************************************************************************************

// Vector
//***********************************************
SUMGLOBALCONST VectorF32 gVEpsilon = {1.192092896e-7f, 1.192092896e-7f, 1.192092896e-7f, 1.192092896e-7f};
SUMGLOBALCONST VectorI32 gVInfinity = {0x7F800000, 0x7F800000, 0x7F800000, 0x7F800000};
SUMGLOBALCONST VectorI32 gVQNaN = {0x7FC00000, 0x7FC00000, 0x7FC00000, 0x7FC00000};
SUMGLOBALCONST VectorI32 gVXMask = {0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000};
SUMGLOBALCONST VectorI32 gVYMask = {0x00000000, 0xFFFFFFFF, 0x00000000, 0x00000000};
SUMGLOBALCONST VectorI32 gVZMask = {0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000000};
SUMGLOBALCONST VectorI32 gVWMask = {0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF};

SUMGLOBALCONST VectorF32 gVOne = {1.0f, 1.0f, 1.0f, 1.0f};
SUMGLOBALCONST VectorF32 gVZero = {0.0f, 0.0f, 0.0f, 0.0f};
SUMGLOBALCONST VectorF32 gVOneHalf = {0.5f, 0.5f, 0.5f, 0.5f};
SUMGLOBALCONST VectorF32 gVNegOne = {-1.0f, -1.0f, -1.0f, -1.0f};
SUMGLOBALCONST VectorF32 gVSinCoefficient0 = {1.0f, -0.166666667f, 8.33333333e-3f, -1.984126984e-4f};
SUMGLOBALCONST VectorF32 gVSinCoefficient1 = {2.755731922e-6f, -2.505210839e-8f, 1.605904383e-10f, -7.647163732e-13f};
SUMGLOBALCONST VectorF32 gVSinCoefficient2 = {2.811457254e-15f, -8.220635247e-18f, 1.957294106e-20f, -3.868170171e-23f};
SUMGLOBALCONST VectorF32 gVCosCoefficient0 = {1.0f, -0.5f, 4.166666667e-2f, -1.388888889e-3f};
SUMGLOBALCONST VectorF32 gVCosCoefficient1 = {2.480158730e-5f, -2.755731922e-7f, 2.087675699e-9f, -1.147074560e-11f};
SUMGLOBALCONST VectorF32 gVCosCoefficient2 = {4.779477332e-14f, -1.561920697e-16f, 4.110317623e-19f, -8.896791392e-22f};
SUMGLOBALCONST VectorF32 gVNegateX = {-1.0f, 1.0f, 1.0f, 1.0f};
SUMGLOBALCONST VectorF32 gVNegateY = {1.0f, -1.0f, 1.0f, 1.0f};
SUMGLOBALCONST VectorF32 gVNegateZ = {1.0f, 1.0f, -1.0f, 1.0f};
SUMGLOBALCONST VectorF32 gVNegateW = {1.0f, 1.0f, 1.0f, -1.0f};

// Matrix
//***********************************************
SUMGLOBALCONST VectorF32 gVIdentityR0 = {1.0f, 0.0f, 0.0f, 0.0f};
SUMGLOBALCONST VectorF32 gVIdentityR1 = {0.0f, 1.0f, 0.0f, 0.0f};
SUMGLOBALCONST VectorF32 gVIdentityR2 = {0.0f, 0.0f, 1.0f, 0.0f};
SUMGLOBALCONST VectorF32 gVIdentityR3 = {0.0f, 0.0f, 0.0f, 1.0f};
SUMGLOBALCONST VectorF32 gVDeterminantNegate = {1.0f, -1.0f, 1.0f, -1.0f};

SUMGLOBALCONST VectorF32 gV3Negate = {-1.0f, -1.0f, -1.0f, 1.0f};

// Colors
//***********************************************
namespace Color
{
	SUMGLOBALCONST VectorF32 White     = {1.0f, 1.0f, 1.0f, 1.0f};
	SUMGLOBALCONST VectorF32 Black     = {0.0f, 0.0f, 0.0f, 1.0f};
	SUMGLOBALCONST VectorF32 Red       = {1.0f, 0.0f, 0.0f, 1.0f};
	SUMGLOBALCONST VectorF32 Green     = {0.0f, 1.0f, 0.0f, 1.0f};
	SUMGLOBALCONST VectorF32 Blue      = {0.0f, 0.0f, 1.0f, 1.0f};
	SUMGLOBALCONST VectorF32 Yellow    = {1.0f, 1.0f, 0.0f, 1.0f};
	SUMGLOBALCONST VectorF32 Cyan      = {0.0f, 1.0f, 1.0f, 1.0f};
	SUMGLOBALCONST VectorF32 Magenta   = {1.0f, 0.0f, 1.0f, 1.0f};
	SUMGLOBALCONST VectorF32 Silver    = {0.75f, 0.75f, 0.75f, 1.0f};
	SUMGLOBALCONST VectorF32 LightSteelBlue = {0.69f, 0.77f, 0.87f, 1.0f};
}

//*************************************************************************************************
// DIMENSIONAL VECTOR
//*************************************************************************************************
#include "SumVector.h"
#include "SumVector2.h"
#include "SumVector3.h"
#include "SumVector4.h"

//*************************************************************************************************
// MATRICES
//*************************************************************************************************
#include "SumMatrix.h"

//*************************************************************************************************
// QUATERNIONS
//*************************************************************************************************
#include "SumQuaternion.h"

//*************************************************************************************************
// MISCELLANEOUS
//*************************************************************************************************
#include "SumMiscMath.h"

//*************************************************************************************************
// FLOATS
//*************************************************************************************************
#include "SumFloat.h"


#ifndef SUMSIMD
// 2D Vector
//struct Vector2 {
//	// Constructors and destructors
//	Vector2(void);
//	Vector2(const float* f);
//	Vector2(float x, float y);
//	Vector2(const Vector2& rhs);
//	~Vector2(void);
//
//	// Casting operators
//	operator float*(void);		// Cast to non-const
//	operator const float*(void) const;	// Cast to const
//
//	// Assignment operators
//	Vector2& operator=(const Vector2& rhs);		
//	Vector2& operator+=(const Vector2& rhs);
//	Vector2& operator-=(const Vector2& rhs);
//	Vector2& operator*=(float rhs);
//	Vector2& operator/=(float rhs);
//
//	// Unary operators
//	Vector2 operator+(void) const;
//	Vector2 operator-(void) const;
//
//	// Binary operators
//	Vector2 operator+(const Vector2& rhs) const;
//	Vector2 operator-(const Vector2& rhs) const;
//	Vector2 operator*(float rhs) const;
//	Vector2 operator/(float rhs) const;
//	friend Vector2 operator*(float lhs, const Vector2& rhs);
//
//	// Equivalence operators
//	bool operator==(const Vector2& rhs) const;
//	bool operator!=(const Vector2& rhs) const;
//	
//	float x, y;		// Vector data
//};

#else
//// 2D Vector (aligned 16 bit)
//struct Vector2_16f {
//	// Ensure proper alignment on dynamic allocation
//	DYNAMIC_ALIGNMENT(Vector2_16f);
//
//	// Constructors and destructors
//	Vector2_16f(void);
//	Vector2_16f(__m128 f);
//	Vector2_16f(const float* f);
//	Vector2_16f(float x, float y);
//	Vector2_16f(const Vector2_16f& rhs);
//	~Vector2_16f(void);
//
//	// Casting operators
//	operator float*(void);		// Cast to non-const
//	operator const float*(void) const;	// Cast to const
//
//	// Assignment operators
//	Vector2_16f& operator=(const Vector2_16f& rhs);		
//	Vector2_16f& operator+=(const Vector2_16f& rhs);
//	Vector2_16f& operator-=(const Vector2_16f& rhs);
//	Vector2_16f& operator*=(float rhs);
//	Vector2_16f& operator/=(float rhs);
//
//	// Unary operators
//	Vector2_16f operator+(void) const;
//	Vector2_16f operator-(void) const;
//
//	// Binary operators
//	Vector2_16f operator+(const Vector2_16f& rhs) const;
//	Vector2_16f operator-(const Vector2_16f& rhs) const;
//	Vector2_16f operator*(float rhs) const;
//	Vector2_16f operator/(float rhs) const;
//	friend Vector2_16f operator*(float lhs, const Vector2_16f& rhs);
//
//	// Equivalence operators
//	bool operator==(const Vector2_16f& rhs) const;
//	bool operator!=(const Vector2_16f& rhs) const;
//	
//
//	// Vector data
//	union {
//		__m128 v;
//		struct {
//			float x;
//			float y;
//		};
//	};
//};

#endif

//// 3D Vector
//struct Vector3 {
//	// Constructors and destructors
//	Vector3(void);
//	Vector3(const float* f);
//	Vector3(const Vector3& rhs);
//	Vector3(float x, float y, float z);
//	~Vector3(void);
//
//	// Casting
//	operator float*(void);
//	operator const float*(void);
//
//	// Assignment operators
//	Vector3& operator=(const Vector3& rhs);
//	Vector3& operator+=(const Vector3& rhs);
//	Vector3& operator-=(const Vector3& rhs);
//	Vector3& operator*=(float rhs);
//	Vector3& operator/=(float rhs);
//
//	// Unary operators
//	Vector3 operator+(void) const;
//	Vector3 operator-(void) const;
//
//	// Binary operators
//	Vector3 operator+(const Vector3& rhs) const;
//	Vector3 operator-(const Vector3& rhs) const;
//	Vector3 operator*(float rhs) const;
//	Vector3 operator/(float rhs) const;
//	friend Vector3 operator*(float lhs, const Vector3& rhs);
//
//	// Equivalence operators
//	bool operator==(const Vector3& rhs) const;
//	bool operator!=(const Vector3& rhs) const;
//
//	float x, y, z;	// Vector data
//};
//
//// 3D Vector (aligned 16 bit)
//struct Vector3_16f {
//	// Ensure proper alignment on dynamic allocation
//	DYNAMIC_ALIGNMENT(Vector3_16f);
//
//	// Constructors and destructors
//	Vector3_16f(void);
//	Vector3_16f(__m128 f);
//	Vector3_16f(const float* f);
//	Vector3_16f(const Vector3_16f& rhs);
//	Vector3_16f(float x, float y, float z);
//	~Vector3_16f(void);
//
//	// Casting
//	operator float*(void);
//	operator const float*(void) const;
//
//	// Assignment operators
//	Vector3_16f& operator=(const Vector3_16f& rhs);
//	Vector3_16f& operator+=(const Vector3_16f& rhs);
//	Vector3_16f& operator-=(const Vector3_16f& rhs);
//	Vector3_16f& operator*=(float rhs);
//	Vector3_16f& operator*=(const __m128& rhs);
//	Vector3_16f& operator/=(float rhs);
//	Vector3_16f& operator/=(const __m128& rhs);
//
//	// Unary operators
//	Vector3_16f operator+(void) const;
//	Vector3_16f operator-(void) const;
//
//	// Binary operators
//	Vector3_16f operator+(const Vector3_16f& rhs) const;
//	Vector3_16f operator-(const Vector3_16f& rhs) const;
//	Vector3_16f operator*(float rhs) const;
//	Vector3_16f operator*(const __m128& rhs) const;
//	Vector3_16f operator/(float rhs) const;
//	Vector3_16f operator/(const __m128& rhs) const;
//	friend Vector3_16f operator*(float lhs, const Vector3_16f& rhs);
//	friend Vector3_16f operator*(const __m128& lhs, const Vector3_16f& rhs);
//
//	// Equivalence operators
//	bool operator==(const Vector3_16f& rhs) const;
//	bool operator!=(const Vector3_16f& rhs) const;
//
//	// Vector data
//	union {
//		__m128 v;
//		struct {
//			float x, y, z;
//		};
//	};
//};
//
//// 4D Vector
//struct Vector4 {
//	// Constructors and destructors
//	Vector4(void);
//	Vector4(const float* f);
//	Vector4(const Vector4& rhs);
//	Vector4(float x, float y, float z, float w);
//	~Vector4(void);
//
//	// Casting
//	operator float*(void);
//	operator const float*(void);
//
//	// Assignment operators
//	Vector4& operator=(const Vector4& rhs);
//	Vector4& operator+=(const Vector4& rhs);
//	Vector4& operator-=(const Vector4& rhs);
//	Vector4& operator*=(float rhs);
//	Vector4& operator/=(float rhs);
//
//	// Unary operators
//	Vector4 operator+(void) const;
//	Vector4 operator-(void) const;
//
//	// Binary operators
//	Vector4 operator+(const Vector4& rhs) const;
//	Vector4 operator-(const Vector4& rhs) const;
//	Vector4 operator*(float rhs) const;
//	Vector4 operator/(float rhs) const;
//	friend Vector4 operator*(float lhs, const Vector4& rhs);
//
//	// Equivalence operators
//	bool operator==(const Vector4& rhs) const;
//	bool operator!=(const Vector4& rhs) const;
//
//	float x, y, z, w;	// Vector data
//};
//
//// 4D Vector (aligned 16 bit)
//struct Vector4_16f {
//	// Ensure proper alignment on dynamic allocation
//	DYNAMIC_ALIGNMENT(Vector4_16f);
//
//	// Constructors and destructors
//	Vector4_16f(void);
//	Vector4_16f(__m128 f);
//	Vector4_16f(const float* f);
//	Vector4_16f(const Vector4_16f& rhs);
//	Vector4_16f(float x, float y, float z, float w);
//	~Vector4_16f(void);
//
//	// Casting
//	operator float*(void);
//	operator const float*(void) const;
//
//	// Assignment operators
//	Vector4_16f& operator=(const Vector4_16f& rhs);
//	Vector4_16f& operator+=(const Vector4_16f& rhs);
//	Vector4_16f& operator-=(const Vector4_16f& rhs);
//	Vector4_16f& operator*=(float rhs);
//	Vector4_16f& operator/=(float rhs);
//
//	// Unary operators
//	Vector4_16f operator+(void) const;
//	Vector4_16f operator-(void) const;
//
//	// Binary operators
//	Vector4_16f operator+(const Vector4_16f& rhs) const;
//	Vector4_16f operator-(const Vector4_16f& rhs) const;
//	Vector4_16f operator*(float rhs) const;
//	Vector4_16f operator/(float rhs) const;
//	friend Vector4_16f operator*(float lhs, const Vector4_16f& rhs);
//
//	// Equivalence operators
//	bool operator==(const Vector4_16f& rhs) const;
//	bool operator!=(const Vector4_16f& rhs) const;
//
//	// Vector data
//	union {
//		__m128 v;
//		struct {
//			float x, y, z, w;
//		};
//	};
//};
//
///**************************************************************************************************
//* MATRICES
//**************************************************************************************************/
//
//// Matrix
//struct Matrix {
//	// Constructors and destructors
//	Matrix(void);
//	Matrix(const float* f);
//	Matrix(const Matrix& rhs);
//	Matrix(	float _11, float _12, float _13, float _14,
//			float _21, float _22, float _23, float _24,
//			float _31, float _32, float _33, float _34,
//			float _41, float _42, float _43, float _44 );
//
//	// Accessors
//	float& operator() (unsigned int row, unsigned int col);
//	float operator() (unsigned int row, unsigned int col) const;
//
//	// Casting operators
//	operator float* (void);
//	operator const float* (void) const;
//
//	// Assignment operators
//	Matrix& operator=(const Matrix& rhs);
//	Matrix& operator*=(const Matrix& rhs);
//	Matrix& operator+=(const Matrix& rhs);
//	Matrix& operator-=(const Matrix& rhs);
//	Matrix& operator*=(float rhs);
//	Matrix& operator/=(float rhs);
//
//	// Unary operators
//	Matrix operator+(void) const;
//	Matrix operator-(void) const;
//
//	// Binary operators
//	Matrix operator*(const Matrix& rhs) const;
//	Matrix operator+(const Matrix& rhs) const;
//	Matrix operator-(const Matrix& rhs) const;
//	Matrix operator*(float rhs) const;
//	Matrix operator/(float rhs) const;
//	friend Matrix operator*(float lhs, const Matrix& rhs);
//
//	// Equivalence operators
//	bool operator==(const Matrix& rhs) const;
//	bool operator!=(const Matrix& rhs) const;
//
//	// Matrix data
//	union {
//		struct {
//			float _11, _12, _13, _14;
//			float _21, _22, _23, _24;
//			float _31, _32, _33, _34;
//			float _41, _42, _43, _44;
//		};
//		float m[4][4];
//	};
//};
//
//// Matrix (aligned 16 bit)
//struct Matrix_16f {
//	// Ensure proper alignment on dynamic allocation
//	DYNAMIC_ALIGNMENT(Matrix_16f);
//
//	// Constructors and destructors
//	Matrix_16f(void);
//	Matrix_16f(const __m128* f);
//	Matrix_16f(const float* f);
//	Matrix_16f(const __m128& r0, const __m128& r1, const __m128& r2, const __m128& r3);
//	Matrix_16f(const Matrix_16f& rhs);
//	Matrix_16f(	float _11, float _12, float _13, float _14,
//			float _21, float _22, float _23, float _24,
//			float _31, float _32, float _33, float _34,
//			float _41, float _42, float _43, float _44 );
//	~Matrix_16f(void);
//
//	// Accessors
//	float& operator() (unsigned int row, unsigned int col);
//	float operator() (unsigned int row, unsigned int col) const;
//
//	// Casting operators
//	operator float* (void);
//	operator const float* (void) const;
//
//	// Assignment operators
//	Matrix_16f& operator=(const Matrix_16f& rhs);
//	Matrix_16f& operator+=(const Matrix_16f& rhs);
//	Matrix_16f& operator-=(const Matrix_16f& rhs);
//	Matrix_16f& operator*=(const Matrix_16f& rhs);
//	Matrix_16f& operator*=(float rhs);
//	Matrix_16f& operator*=(const __m128& rhs);
//	Matrix_16f& operator/=(float rhs);
//	Matrix_16f& operator/=(const __m128& rhs);
//
//	// Unary operators
//	Matrix_16f operator+(void) const;
//	Matrix_16f operator-(void) const;
//
//	// Binary operators
//	Matrix_16f operator+(const Matrix_16f& rhs) const;
//	Matrix_16f operator-(const Matrix_16f& rhs) const;
//	Matrix_16f operator*(const Matrix_16f& rhs) const;
//	Matrix_16f operator*(float rhs) const;
//	Matrix_16f operator*(const __m128& rhs) const;
//	Matrix_16f operator/(float rhs) const;
//	Matrix_16f operator/(const __m128& rhs) const;
//	friend Matrix_16f operator*(float lhs, const Matrix_16f& rhs);
//	friend Matrix_16f operator*(const __m128& lhs, const Matrix_16f& rhs);
//
//	// Equivalence operators
//	bool operator==(const Matrix_16f& rhs) const;
//	bool operator!=(const Matrix_16f& rhs) const;
//
//	// Matrix data
//	union {
//		__m128 v[4];
//		struct {
//			float _11, _12, _13, _14;
//			float _21, _22, _23, _24;
//			float _31, _32, _33, _34;
//			float _41, _42, _43, _44;
//		};
//		float m[4][4];
//	};
//};
//
///**************************************************************************************************
//* QUATERNIONS
//**************************************************************************************************/
//
//// Quaternion
//struct Quaternion {
//	// Constructors and destructors
//	Quaternion(void);
//	Quaternion(const float* f);
//	Quaternion(const Quaternion& rhs);
//	Quaternion(float x, float y, float z, float w);
//	~Quaternion(void);
//
//	// Casting
//	operator float*(void);
//	operator const float*(void) const;
//
//	// Assignment operators
//	Quaternion& operator=(const Quaternion& rhs);
//	Quaternion& operator+=(const Quaternion& rhs);
//	Quaternion& operator-=(const Quaternion& rhs);
//	Quaternion& operator*=(const Quaternion& rhs);
//	Quaternion& operator*=(float rhs);
//	Quaternion& operator/=(float rhs);
//
//	// Unary operators
//	Quaternion operator+(void) const;
//	Quaternion operator-(void) const;
//
//	// Binary operators
//	Quaternion operator+(const Quaternion& rhs) const;
//	Quaternion operator-(const Quaternion& rhs) const;
//	Quaternion operator*(const Quaternion& rhs) const;
//	Quaternion operator*(float rhs) const;
//	Vector3 operator*(const Vector3& rhs) const;
//	Quaternion operator/(float rhs) const;
//	friend Quaternion operator*(float lhs, const Quaternion& rhs);
//
//	// Equivalence operators
//	bool operator==(const Quaternion& rhs) const;
//	bool operator!=(const Quaternion& rhs) const;
//
//	float x, y, z, w;	// Quaternion data
//};
//
//// Quaternion (aligned 16 bit)
//struct Quaternion_16f {
//	// Ensure proper alignment on dynamic allocation
//	DYNAMIC_ALIGNMENT(Quaternion_16f);
//
//	// Constructors and destructors
//	Quaternion_16f(void);
//	Quaternion_16f(const __m128& f);
//	Quaternion_16f(const float* f);
//	Quaternion_16f(const Quaternion_16f& rhs);
//	Quaternion_16f(float x, float y, float z, float w);
//	~Quaternion_16f(void);
//
//	// Casting
//	operator float*(void);
//	operator const float*(void) const;
//
//	// Assignment operators
//	Quaternion_16f& operator=(const Quaternion_16f& rhs);
//	Quaternion_16f& operator+=(const Quaternion_16f& rhs);
//	Quaternion_16f& operator-=(const Quaternion_16f& rhs);
//	Quaternion_16f& operator*=(const Quaternion_16f& rhs);
//	Quaternion_16f& operator*=(const __m128& rhs);
//	Quaternion_16f& operator*=(float rhs);
//	Quaternion_16f& operator/=(const __m128& rhs);
//	Quaternion_16f& operator/=(float rhs);
//
//	// Unary operators
//	Quaternion_16f operator+(void) const;
//	Quaternion_16f operator-(void) const;
//
//	// Binary operators
//	Quaternion_16f operator+(const Quaternion_16f& rhs) const;
//	Quaternion_16f operator-(const Quaternion_16f& rhs) const;
//	Quaternion_16f operator*(const Quaternion_16f& rhs) const;
//	Quaternion_16f operator*(const __m128& rhs) const;
//	Quaternion_16f operator*(float rhs) const;
//	Vector3_16f operator*(const Vector3_16f& rhs) const;
//	Quaternion_16f operator/(const __m128& rhs) const;
//	Quaternion_16f operator/(float rhs) const;
//	friend Quaternion_16f operator*(float lhs, const Quaternion_16f& rhs);
//	friend Quaternion_16f operator*(const __m128& lhs, const Quaternion_16f& rhs);
//
//	// Equivalence operators
//	bool operator==(const Quaternion_16f& rhs) const;
//	bool operator!=(const Quaternion_16f& rhs) const;
//
//	// Quaternion data
//	union {
//		__m128 v;
//		struct {
//			float x, y, z, w;
//		};
//	};
//};
//
///**************************************************************************************************
//* PLANES
//**************************************************************************************************/
//
//// Plane
//struct Plane {
//	// Constructors and destructors
//	Plane(void);
//	Plane(const float* f);
//	Plane(const Plane& rhs);
//	Plane(float a, float b, float c, float d);
//	~Plane(void);
//
//	// Casting
//	operator float*(void);
//	operator const float*(void) const;
//
//	// Assignment operators
//	Plane& operator=(const Plane& rhs);
//	Plane& operator*=(float rhs);
//	Plane& operator/=(float rhs);
//
//	// Unary operators
//	Plane operator+(void) const;
//	Plane operator-(void) const;
//
//	// Binary operators
//	Plane operator*(float rhs) const;
//	Plane operator/(float rhs) const;
//	friend Plane operator*(float lhs, const Plane& rhs);
//
//	// Equivalence operators
//	bool operator==(const Plane& rhs) const;
//	bool operator!=(const Plane& rhs) const;
//
//	float a, b, c, d;	// Plane data
//};
//
// // Plane (aligned 16 bit)
//struct Plane_16f {
//	// Ensure proper alignment on dynamic allocation
//	DYNAMIC_ALIGNMENT(Plane_16f);
//
//	// Constructors and destructors
//	Plane_16f(void);
//	Plane_16f(const __m128& f);
//	Plane_16f(const float* f);
//	Plane_16f(const Plane_16f& rhs);
//	Plane_16f(float a, float b, float c, float d);
//	~Plane_16f(void);
//
//	// Casting
//	operator float*(void);
//	operator const float*(void) const;
//
//	// Assignment operators
//	Plane_16f& operator=(const Plane_16f& rhs);
//	Plane_16f& operator*=(float rhs);
//	Plane_16f& operator*=(const __m128& rhs);
//	Plane_16f& operator/=(float rhs);
//	Plane_16f& operator/=(const __m128& rhs);
//
//	// Unary operators
//	Plane_16f operator+(void) const;
//	Plane_16f operator-(void) const;
//
//	// Binary operators
//	Plane_16f operator*(float rhs) const;
//	Plane_16f operator*(const __m128& rhs) const;
//	Plane_16f operator/(float rhs) const;
//	Plane_16f operator/(const __m128& rhs) const;
//	friend Plane_16f operator*(float lhs, const Plane_16f& rhs);
//	friend Plane_16f operator*(const __m128& lhs, const Plane_16f& rhs);
//
//	// Equivalence operators
//	bool operator==(const Plane_16f& rhs) const;
//	bool operator!=(const Plane_16f& rhs) const;
//
//	// Plane data
//	union {
//		__m128 v;
//		struct {
//			float a, b, c, d;
//		};
//	};
//};
//
///**************************************************************************************************
//* COLOR
//**************************************************************************************************/
//
//// Color
//struct Color {
//	// Constructors and destructors
//	Color(void);
//	Color(unsigned int argb);
//	Color(const float* f);
//	Color(const Color& rhs);
//	Color(float r, float g, float b, float a);
//	~Color(void);
//
//	// Casting
//	operator unsigned int(void) const;
//	operator float*(void);
//	operator const float*(void) const;
//	
//	// Assignment operators
//	Color& operator=(const Color& rhs);
//	Color& operator+=(const Color& rhs);
//	Color& operator-=(const Color& rhs);
//	Color& operator*=(float rhs);
//	Color& operator/=(float rhs);
//
//	// Unary operator
//	Color operator+(void) const;
//	Color operator-(void) const;
//
//	// Binary operators
//	Color operator+(const Color& rhs) const;
//	Color operator-(const Color& rhs) const;
//	Color operator*(float rhs) const;
//	Color operator/(float rhs) const;
//	friend Color operator*(float lhs, const Color& rhs);
//
//	// Equivalence
//	bool operator==(const Color& rhs) const;
//	bool operator!=(const Color& rhs) const;
//
//	float r, g, b, a;	// Color data
//};
//
//// Color  (aligned 16 bit)
//struct Color_16f {
//	// Ensure proper alignment on dynamic allocation
//	DYNAMIC_ALIGNMENT(Color_16f);
//
//	// Constructors and destructors
//	Color_16f(void);
//	Color_16f(const __m128& f);
//	Color_16f(unsigned int argb);
//	Color_16f(const float* f);
//	Color_16f(const Color_16f& rhs);
//	Color_16f(float r, float g, float b, float a);
//	~Color_16f(void);
//
//	// Casting
//	operator unsigned int(void) const;
//	operator float*(void);
//	operator const float*(void) const;
//	
//	// Assignment operators
//	Color_16f& operator=(const Color_16f& rhs);
//	Color_16f& operator+=(const Color_16f& rhs);
//	Color_16f& operator-=(const Color_16f& rhs);
//	Color_16f& operator*=(float rhs);
//	Color_16f& operator*=(const __m128& rhs);
//	Color_16f& operator/=(float rhs);
//	Color_16f& operator/=(const __m128& rhs);
//
//	// Unary operator
//	Color_16f operator+(void) const;
//	Color_16f operator-(void) const;
//
//	// Binary operators
//	Color_16f operator+(const Color_16f& rhs) const;
//	Color_16f operator-(const Color_16f& rhs) const;
//	Color_16f operator*(float rhs) const;
//	Color_16f operator*(const __m128& rhs) const;
//	Color_16f operator/(float rhs) const;
//	Color_16f operator/(const __m128& rhs) const;
//	friend Color_16f operator*(float lhs, const Color_16f& rhs);
//	friend Color_16f operator*(const __m128& lhs, const Color_16f& rhs);
//
//	// Equivalence
//	bool operator==(const Color_16f& rhs) const;
//	bool operator!=(const Color_16f& rhs) const;
//
//	// Color data
//	union {
//		__m128 v;
//		struct {
//			float r, g, b, a;
//		};
//	};
//};
//
///**************************************************************************************************
//* VIEWPORT
//**************************************************************************************************/
//
//// Viewport
//struct Viewport {
//	unsigned int x;				// Top-left x
//	unsigned int y;				// Top-left y
//	unsigned int width;			// Width
//	unsigned int height;		// Height
//	float minZ;					// Near clipping plane
//	float maxZ;					// Far clipping plane
//};
//
///**************************************************************************************************
//* Math functions
//**************************************************************************************************/
//
////-----------------------------------------------
//// 2D Vector
////-----------------------------------------------
//// Length
//float Vec2Length(const Vector2* pV);
//
//// Squared length
//float Vec2LengthSqr(const Vector2* pV);
//
//// Dot product
//float Vec2Dot(const Vector2* pV1, const Vector2* pV2);
//
//// Z component of cross product
//float Vec2CCW(const Vector2* pV1, const Vector2* pV2);
//
//// Addition
//Vector2* Vec2Add(Vector2* pOut, const Vector2* pV1, const Vector2* pV2);
//
//// Subtraction
//Vector2* Vec2Sub(Vector2* pOut, const Vector2* pV1, const Vector2* pV2);
//
//// Minimize each component
//Vector2* Vec2Minimize(Vector2* pOut, const Vector2* pV1, const Vector2* pV2);
//
//// Maximize each component
//Vector2* Vec2Maximize(Vector2* pOut, const Vector2* pV1, const Vector2* pV2);
//
//// Scale the vector
//Vector2* Vec2Scale(Vector2* pOut, const Vector2* pV, float s);
//
//// Linear interpolation V1 + s(V2 - V1)
//Vector2* Vec2Lerp(Vector2* pOut, const Vector2* pV1, const Vector2* pV2, float s);
//
//// Normalize
//Vector2* Vec2Normalize(Vector2* pOut, const Vector2* pV);
//
//extern "C"
//{
//// Hermite interpolation between position V1, tangent T1 (when s == 0)
//// and position V2, tangent T2 (when s == 1).
//Vector2* Vec2Hermite(Vector2* pOut, const Vector2* pV1, const Vector2* pT1, 
//	const Vector2* pV2, const Vector2* pT2, float s);
//
//// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
//Vector2* Vec2CatmullRom(Vector2* pOut, const Vector2* pV0, const Vector2* pV1,
//	const Vector2* pV2, const Vector2* pV3, float s);
//
//// Barycentric coordinates V1 + f(V2 - V1) + g(V3 - V1)
//Vector2* Vec2Barycentric(Vector2* pOut, const Vector2* pV1, const Vector2* pV2, const Vector2* pV3,
//	float f, float g);
//
//// Transform by matrix (x, y, 0, 1)
//Vector4* Vec2Transform(Vector4* pOut, const Vector2* pV, const Matrix* pM);
//
//// Transform coords by matrix (x, y, 0, 1)
//Vector2* Vec2TransformCoord(Vector2* pOut, const Vector2* pV, const Matrix* pM);
//
//// Transform normal by matrix (x, y, 0, 0)
//Vector2* Vec2TransformNormal(Vector2* pOut, const Vector2* pV, const Matrix* pM);
//}
//
////-----------------------------------------------
//// 2D Vector 16-byte aligned
////-----------------------------------------------
//// Length
//float Vec2Length_16f(const Vector2_16f* pV);
//
//// Squared length
//float Vec2LengthSqr_16f(const Vector2_16f* pV);
//
//// Dot product
//float Vec2Dot_16f(const Vector2_16f* pV1, const Vector2_16f* pV2);
//
//// Z component of cross product
//float Vec2CCW_16f(const Vector2_16f* pV1, const Vector2_16f* pV2);
//
//// Addition
//Vector2_16f* Vec2Add_16f(Vector2_16f* pOut, const Vector2_16f* pV1, const Vector2_16f* pV2);
//
//// Subtraction
//Vector2_16f* Vec2Sub_16f(Vector2_16f* pOut, const Vector2_16f* pV1, const Vector2_16f* pV2);
//
//// Minimize each component
//Vector2_16f* Vec2Minimize_16f(Vector2_16f* pOut, const Vector2_16f* pV1, const Vector2_16f* pV2);
//
//// Maximize each component
//Vector2_16f* Vec2Maximize_16f(Vector2_16f* pOut, const Vector2_16f* pV1, const Vector2_16f* pV2);
//
//// Scale the vector
//Vector2_16f* Vec2Scale_16f(Vector2_16f* pOut, const Vector2_16f* pV, float s);
//
//// Linear interpolation V1 + s(V2 - V1)
//Vector2_16f* Vec2Lerp_16f(Vector2_16f* pOut, const Vector2_16f* pV1, const Vector2_16f* pV2, float s);
//
//// Normalize
//Vector2_16f* Vec2Normalize_16f(Vector2_16f* pOut, const Vector2_16f* pV);
//
//extern "C"
//{
//// Hermite interpolation between position V1, tangent T1 (when s == 0)
//// and position V2, tangent T2 (when s == 1).
//Vector2_16f* Vec2Hermite_16f(Vector2_16f* pOut, const Vector2_16f* pV1, const Vector2_16f* pT1, 
//	const Vector2_16f* pV2, const Vector2_16f* pT2, float s);
//
//// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
//Vector2_16f* Vec2CatmullRom_16f(Vector2_16f* pOut, const Vector2_16f* pV0, const Vector2_16f* pV1,
//	const Vector2_16f* pV2, const Vector2_16f* pV3, float s);
//
//// Barycentric coordinates V1 + f(V2 - V1) + g(V3 - V1)
//Vector2_16f* Vec2Barycentric_16f(Vector2_16f* pOut, const Vector2_16f* pV1, const Vector2_16f* pV2, const Vector2_16f* pV3,
//	float f, float g);
//
//// Transform by matrix (x, y, 0, 1)
//Vector4_16f* Vec2Transform_16f(Vector2_16f* pOut, const Vector2_16f* pV, const Matrix_16f* pM);
//
//// Transform coords by matrix (x, y, 0, 1)
//Vector2_16f* Vec2TransformCoord_16f(Vector2_16f* pOut, const Vector2_16f* pV, const Matrix_16f* pM);
//
//// Transform normal by matrix (x, y, 0, 0)
//Vector2_16f* Vec2TransformNormal_16f(Vector2_16f* pOut, const Vector2_16f* pV, const Matrix_16f* pM);
//}
//
////-----------------------------------------------
//// 3D Vector
////-----------------------------------------------
//// Length
//float Vec3Length(const Vector3* pV);
//
//// Squared length
//float Vec3LengthSqr(const Vector3* pV);
//
//// Dot
//float Vec3Dot(const Vector3* pV1, const Vector3* pV2);
//
//// Cross
//Vector3* Vec3Cross(Vector3* pOut, const Vector3* pV1, const Vector3* pV2);
//
//// Add
//Vector3* Vec3Add(Vector3* pOut, const Vector3* pV1, const Vector3* pV2);
//
//// Subtract
//Vector3* Vec3Sub(Vector3* pOut, const Vector3* pV1, const Vector3* pV2);
//
//// Minimize
//Vector3* Vec3Minimize(Vector3* pOut, const Vector3* pV1, const Vector3* pV2);
//
//// Maximize
//Vector3* Vec3Maximize(Vector3* pOut, const Vector3* pV1, const Vector3* pV2);
//
//// Scale
//Vector3* Vec3Scale(Vector3* pOut, const Vector3* pV, float s);
//
//// Lerp
//Vector3* Vec3Lerp(Vector3* pOut, const Vector3* pV1, const Vector3* pV2, float s);
//
//// Normalize
//Vector3* Vec3Normalize(Vector3* pOut, const Vector3* pV);
//
//extern "C"
//{
//// Hermite interpolation between position V1, tangent T1 (when s == 0)
//// and position V2, tangent T2 (when s == 1).
//Vector3* Vec3Hermite(Vector3* pOut, const Vector3* pV1, const Vector3* pT1, 
//	const Vector3* pV2, const Vector3* pT2, float s);
//
//// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
//Vector3* Vec3CatmullRom(Vector3* pOut, const Vector3* pV0, const Vector3* pV1,
//	const Vector3* pV2, const Vector3* pV3, float s);
//
//// Barycentric
//Vector3* Vec3Barycentric(Vector3* pOut, const Vector3* pV1, const Vector3* pV2, const Vector3* pV3,
//	float f, float g);
//
//// Transform by matrix (x, y, z, 1)
//Vector4* Vec3Transform(Vector4* pOut, const Vector3* pV, const Matrix* pM);
//
//// Transform coord by matrix (x, y, z, 1)
//Vector3* Vec3TransformCoord(Vector3* pOut, const Vector3* pV, const Matrix* pM);
//
//// Transform normal by matix (x, y, z, 0)
//Vector3* Vec3TransformNormal(Vector3* pOut, const Vector3* pV, const Matrix* pM);
//
//// Project from object space into screen space
//Vector3* Vec3Project(Vector3* pOut, const Vector3* pV, const Viewport* pViewport, 
//	const Matrix* pProjection, const Matrix* pView, const Matrix* pWorld);
//
//// Project from screen space into object space
//Vector3* Vec3Unproject(Vector3* pOut, const Vector3* pV, const Viewport* pViewport, 
//	const Matrix* pProjection, const Matrix* pView, const Matrix* pWorld);
//}
//
////-----------------------------------------------
//// 3D Vector 16-byte aligned
////-----------------------------------------------
//// Length
//float Vec3Length_16f(const Vector3_16f* pV);
//
//// Squared length
//float Vec3LengthSqr_16f(const Vector3_16f* pV);
//
//// Dot
//float Vec3Dot_16f(const Vector3_16f* pV1, const Vector3_16f* pV2);
//
//// Cross
//Vector3_16f* Vec3Cross_16f(Vector3_16f* pOut, const Vector3_16f* pV1, const Vector3_16f* pV2);
//
//// Add
//Vector3_16f* Vec3Add_16f(Vector3_16f* pOut, const Vector3_16f* pV1, const Vector3_16f* pV2);
//
//// Subtract
//Vector3_16f* Vec3Sub_16f(Vector3_16f* pOut, const Vector3_16f* pV1, const Vector3_16f* pV2);
//
//// Minimize
//Vector3_16f* Vec3Minimize_16f(Vector3_16f* pOut, const Vector3_16f* pV1, const Vector3_16f* pV2);
//
//// Maximize
//Vector3_16f* Vec3Maximize_16f(Vector3_16f* pOut, const Vector3_16f* pV1, const Vector3_16f* pV2);
//
//// Scale
//Vector3_16f* Vec3Scale_16f(Vector3_16f* pOut, const Vector3_16f* pV, float s);
//
//// Scale the vector
//Vector3_16f* Vec3Scale_16f(Vector3_16f* pOut, const Vector3_16f* pV, const __m128& s);
//
//// Lerp
//Vector3_16f* Vec3Lerp_16f(Vector3_16f* pOut, const Vector3_16f* pV1, const Vector3_16f* pV2, float s);
//
//// Lerp
//Vector3_16f* Vec3Lerp_16f(Vector3_16f* pOut, const Vector3_16f* pV1, const Vector3_16f* pV2, const __m128& s);
//
//// Normalize
//Vector3_16f* Vec3Normalize_16f(Vector3_16f* pOut, const Vector3_16f* pV);
//
//extern "C++"
//{
//// Hermite interpolation between position V1, tangent T1 (when s == 0)
//// and position V2, tangent T2 (when s == 1).
//Vector3_16f* Vec3Hermite_16f(Vector3_16f* pOut, const Vector3_16f* pV1, const Vector3_16f* pT1, 
//	const Vector3_16f* pV2, const Vector3_16f* pT2, float s);
//
//// Hermite interpolation between position V1, tangent T1 (when s == 0)
//// and position V2, tangent T2 (when s == 1).
//Vector3_16f* Vec3Hermite_16f(Vector3_16f* pOut, const Vector3_16f* pV1, const Vector3_16f* pT1, 
//	const Vector3_16f* pV2, const Vector3_16f* pT2, __m128 s);
//
//// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
//Vector3_16f* Vec3CatmullRom_16f(Vector3_16f* pOut, const Vector3_16f* pV0, const Vector3_16f* pV1,
//	const Vector3_16f* pV2, const Vector3_16f* pV3, float s);
//
//// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
//Vector3_16f* Vec3CatmullRom_16f(Vector3_16f* pOut, const Vector3_16f* pV0, const Vector3_16f* pV1,
//	const Vector3_16f* pV2, const Vector3_16f* pV3, const __m128& s);
//
//// Barycentric
//Vector3_16f* Vec3Barycentric_16f(Vector3_16f* pOut, const Vector3_16f* pV1, const Vector3_16f* pV2, const Vector3_16f* pV3,
//	float f, float g);
//
//// Transform by matrix (x, y, z, 1)
//Vector4_16f* Vec3Transform_16f(Vector4_16f* pOut, const Vector3_16f* pV, const Matrix_16f* pM);
//
//// Transform coord by matrix (x, y, z, 1)
//Vector3_16f* Vec3TransformCoord_16f(Vector3_16f* pOut, const Vector3_16f* pV, const Matrix_16f* pM);
//
//// Transform normal by matix (x, y, z, 0)
//Vector3_16f* Vec3TransformNormal_16f(Vector3_16f* pOut, const Vector3_16f* pV, const Matrix_16f* pM);
//
//// Project from object space into screen space
//Vector3_16f* Vec3Project_16f(Vector3_16f* pOut, const Vector3_16f* pV, const Viewport* pViewport, const Matrix_16f* pProjection, const Matrix_16f* pView, const Matrix_16f* pWorld);
//
//// Project from screen space into object space
//Vector3_16f* Vec3Unproject_16f(Vector3_16f* pOut, const Vector3_16f* pV, const Viewport* pViewport, const Matrix_16f* pProjection, const Matrix_16f* pView, const Matrix_16f* pWorld);
//}
//
////-----------------------------------------------
//// 4D Vector
////-----------------------------------------------
//// Length
//float Vec4Length(const Vector4* pV);
//
//// Squared length
//float Vec4LengthSqr(const Vector4* pV);
//
//// Dot product
//float Vec4Dot(const Vector4* pV1, const Vector4* pV2);
//
//// Add
//Vector4* Vec4Add(Vector4* pOut, const Vector4* pV1, const Vector4* pV2);
//
//// Subtract
//Vector4* Vec4Sub(Vector4* pOut, const Vector4* pV1, const Vector4* pV2);
//
//// Minimize
//Vector4* Vec4Minimize(Vector4* pOut, const Vector4* pV1, const Vector4* pV2);
//
//// Maximize
//Vector4* Vec4Maximize(Vector4* pOut, const Vector4* pV1, const Vector4* pV2);
//
//// Scale
//Vector4* Vec4Scale(Vector4* pOut, const Vector4* pV, float s);
//
//// Lerp
//Vector4* Vec4Lerp(Vector4* pOut, const Vector4* pV1, const Vector4* pV2, float s);
//
//extern "C"
//{
//// Cross
//Vector4* Vec4Cross(Vector4* pOut, const Vector4* pV1, const Vector4* pV2, const Vector4* pV3);
//
//// Normalize
//Vector4* Vec4Normalize(Vector4* pOut, const Vector4* pV);
//
//// Hermite interpolation between position V1, tangent T1 (when s == 0)
//// and position V2, tangent T2 (when s == 1).
//Vector4* Vec4Hermite(Vector4* pOut, const Vector4* pV1, const Vector4* pT1, 
//	const Vector4* pV2, const Vector4* pT2, float s);
//
//// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
//Vector4* Vec4CatmullRom(Vector4* pOut, const Vector4* pV0, const Vector4* pV1,
//	const Vector4* pV2, const Vector4* pV3, float s);
//
//// Barycentric coordinates
//Vector4* Vec4Barycentric(Vector4* pOut, const Vector4* pV1, const Vector4* pV2, const Vector4* pV3,
//	float f, float g);
//
//// Transform vector by matrix
//Vector4* Vec4Transform(Vector4* pOut, const Vector4* pV, const Matrix* pM);
//}
//
////-----------------------------------------------
//// 4D Vector 16-byte aligned
////-----------------------------------------------
//
//// Length
//float Vec4Length_16f(const Vector4_16f* pV);
//
//// Squared length
//float Vec4LengthSqr_16f(const Vector4_16f* pV);
//
//// Dot product
//float Vec4Dot_16f(const Vector4_16f* pV1, const Vector4_16f* pV2);
//
//// Add
//Vector4_16f* Vec4Add_16f(Vector4_16f* pOut, const Vector4_16f* pV1, const Vector4_16f* pV2);
//
//// Subtract
//Vector4_16f* Vec4Sub_16f(Vector4_16f* pOut, const Vector4_16f* pV1, const Vector4_16f* pV2);
//
//// Minimize
//Vector4_16f* Vec4Minimize_16f(Vector4_16f* pOut, const Vector4_16f* pV1, const Vector4_16f* pV2);
//
//// Maximize
//Vector4_16f* Vec4Maximize_16f(Vector4_16f* pOut, const Vector4_16f* pV1, const Vector4_16f* pV2);
//
//// Scale
//Vector4_16f* Vec4Scale_16f(Vector4_16f* pOut, const Vector4_16f* pV, float s);
//
//// Scale
//Vector4_16f* Vec4Scale_16f(Vector4_16f* pOut, const Vector4_16f* pV, const __m128& s);
//
//// Lerp
//Vector4_16f* Vec4Lerp_16f(Vector4_16f* pOut, const Vector4_16f* pV1, const Vector4_16f* pV2, float s);
//
//// Lerp
//Vector4_16f* Vec4Lerp_16f(Vector4_16f* pOut, const Vector4_16f* pV1, const Vector4_16f* pV2, const __m128& s);
//
//extern "C++"
//{
//// Cross product
//Vector4_16f* Vec4Cross_16f(Vector4_16f* pOut, const Vector4_16f* pV1, const Vector4_16f* pV2, const Vector4_16f* pV3);
//
//// Normalize
//Vector4_16f* Vec4Normalize_16f(Vector4_16f* pOut, const Vector4_16f* pV);
//
//// Hermite interpolation between position V1, tangent T1 (when s == 0)
//// and position V2, tangent T2 (when s == 1).
//Vector4_16f* Vec4Hermite_16f(Vector4_16f* pOut, const Vector4_16f* pV1, const Vector4_16f* pT1, 
//	const Vector4_16f* pV2, const Vector4_16f* pT2, float s);
//
//// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
//Vector4_16f* Vec4CatmullRom_16f(Vector4_16f* pOut, const Vector4_16f* pV0, const Vector4_16f* pV1,
//	const Vector4_16f* pV2, const Vector4_16f* pV3, float s);
//
//// Barycentric coordinates V1 + f(V2 - V1) + g(V3 - V1)
//Vector4_16f* Vec4Barycentric_16f(Vector4_16f* pOut, const Vector4_16f* pV1, const Vector4_16f* pV2, const Vector4_16f* pV3,
//	float f, float g);
//
//// Barycentric coordinates V1 + f(V2 - V1) + g(V3 - V1)
//Vector4_16f* Vec4Barycentric_16f(Vector4_16f* pOut, const Vector4_16f* pV1, const Vector4_16f* pV2, const Vector4_16f* pV3,
//	const __m128& f, const __m128& g);
//
//// Transform by matrix (x, y, 0, 1)
//Vector4_16f* Vec4Transform_16f(Vector4_16f* pOut, const Vector4_16f* pV, const Matrix_16f* pM);
//}
//
////-----------------------------------------------
//// 4D Matrix
////-----------------------------------------------
//
//// Identity
//Matrix* MatrixIdentity(Matrix* pOut);
//
//// Is identity
//bool MatrixIsIdentity(const Matrix* pM);
//
//// Sum of two matrices
//Matrix* MatrixAdd(Matrix* pOut, const Matrix* pM1, const Matrix* pM2);
//
//// Difference between two matrices
//Matrix* MatrixSub(Matrix* pOut, const Matrix* pM1, const Matrix* pM2);
//
//extern "C"
//{
//// Determinant
//float MatrixDeterminant(const Matrix* pM);
//
//// Decompose
//int MatrixDecompose(Vector3* pOutScale, Quaternion* pOutRotation, Vector3* pOutTranslation, const Matrix* pM);
//
//// Transpose
//Matrix* MatrixTranspose(Matrix* pOut, const Matrix* pM);
//
//// Multiply
//Matrix* MatrixMultiply(Matrix* pOut, const Matrix* pM1, const Matrix* pM2);
//
//// Multiply, followed by a transpose T(M1 * M2)
//Matrix* MatrixMultiplyTranspose(Matrix* pOut, const Matrix* pM1, const Matrix* pM2);
//
//// Inverse
//Matrix* MatrixInverse(Matrix* pOut, float* pDeterminant, const Matrix* pM);
//
//// Build a matrix which scales by (sx, sy, sz)
//Matrix* MatrixScaling(Matrix* pOut, float sx, float sy, float sz);
//
//// Build a matrix which tranlates by (x, y, z)
//Matrix* MatrixTranslation(Matrix* pOut, float x, float y, float z);
//
//// Build a matrix which rotates around the X axis
//Matrix* MatrixRotationX(Matrix* pOut, float angle);
//
//// Build a matrix which rotates around the Y axis
//Matrix* MatrixRotationY(Matrix* pOut, float angle);
//
//// Build a matrix which rotates around the Z axis
//Matrix* MatrixRotationZ(Matrix* pOut, float angle);
//
//// Build a matrix which rotates around an arbitrary axis
//Matrix* MatrixRotationAxis(Matrix* pOut, const Vector3* pV, float angle);
//
//// Build a matrix from a quaternion
//Matrix* MatrixRotationQuaternion(Matrix* pOut, const Quaternion* pQ);
//
//// Yaw around the Y axis, a pitch around the X axis, and a roll around the Z axis
//Matrix* MatrixRotationYawPitchRoll(Matrix* pOut, float yaw, float pitch, float roll);
//
//// Build transformation matrix with null arguments being treated as identity. 
//// Mout = Msc-1 * Msr-1 * Ms * Msr * Msc * Mrc-1 * Mr * Mrc * Mt
//Matrix* MatrixTransformation(Matrix* pOut, const Vector3* pScalingCenter, 
//	const Quaternion* pScalingRotation, const Vector3* pScaling, const Vector3* pRotationCenter, const Quaternion* pRotation, const Vector3* pTranslation);
//
//// Build 2D transformation matrix in XY plane. Null arguments treated as identity. Mout = Msc-1 * Msr-1 * Ms * Msr * Msc * Mrc-1 * Mr * Mrc * Mt
//Matrix* MatrixTransformation2D(Matrix* pOut, const Vector2* pScalingCenter, float scalingRotation, 
//	const Vector2* pScaling, const Vector2* pRotationCenter, float rotation, const Vector2* pTranslation);
//
//// Build affine transformation matrix. Null arguments treated as identity. Mout = Ms * Mrc-1 * Mr * Mrc * Mt
//Matrix* MatrixAffineTransformation(Matrix* pOut, float scaling, const Vector3* pRotationCenter, const Quaternion* pRotation, const Vector3* pTranslation);
//
//// Build 2D affine transformation matrix in XY plane. Null arguments treated as identity. Mout = Ms * Mrc-1 * Mr * Mrc * Mt
//Matrix* MatrixAffineTransformation2D(Matrix* pOut, float scaling, const Vector2* pRotationCenter, float rotation, const Vector2* pTranslation);
//
//// Build a lookat matrix (right-handed)
//Matrix* MatrixLookAtRH(Matrix* pOut, const Vector3* pEye, const Vector3* pAt, const Vector3* pUp);
//
//// Build a lookat matrix (left-handed)
//Matrix* MatrixLookAtLH(Matrix* pOut, const Vector3* pEye, const Vector3* pAt, const Vector3* pUp);
//
//// Build a perspective projection matrix (right-handed)
//Matrix* MatrixPerspectiveRH(Matrix* pOut, float w, float h, float zn, float zf);
//
//// Build a perspective projection matrix (left-handed)
//Matrix* MatrixPerspectiveLH(Matrix* pOut, float w, float h, float zn, float zf);
//
//// Build a perspective projection matrix (right-handed)
//Matrix* MatrixPerspectiveFovRH(Matrix* pOut, float fovy, float aspect, float zn, float zf);
//
//// Build a perspective projection matrix (left-handed)
//Matrix* MatrixPerspectiveFovLH(Matrix* pOut, float fovy, float aspect, float zn, float zf);
//
//// Build a matrix which flattens geometry into a plane, as if casting a shadow from a light
//Matrix* MatrixShadow(Matrix* pOut, const Vector4* pLight, const Plane* pPlane);
//
//// Build a matrix which reflects the coordinate system about a plane
//Matrix* MatrixReflect(Matrix* pOut, const Plane* pPlane);
//
//// Creates a tensor product of given two 3D vectors
//Matrix* MatrixTensorProduct(Matrix* pOut, const Vector3* pV1, const Vector3* pV2);
//}
//
////-----------------------------------------------
//// 4D Matrix 16-byte aligned
////-----------------------------------------------
//
//// Identity
//Matrix_16f* MatrixIdentity_16f(Matrix_16f* pOut);
//
//// Is identity
//bool MatrixIsIdentity_16f(const Matrix_16f* pM);
//
//// Sum of two matrices
//Matrix_16f* MatrixAdd_16f(Matrix_16f* pOut, const Matrix_16f* pM1, const Matrix_16f* pM2);
//
//// Difference between two matrices
//Matrix_16f* MatrixSub_16f(Matrix_16f* pOut, const Matrix_16f* pM1, const Matrix_16f* pM2);
//
//extern "C++"
//{
//// Determinant
//float MatrixDeterminant_16f(const Matrix_16f* pM);
//
//// Decompose
//int MatrixDecompose_16f(Vector3_16f* pOutScale, Quaternion_16f* pOutRotation, Vector3_16f* pOutTranslation, const Matrix_16f* pM);
//
//// Transpose
//Matrix_16f* MatrixTranspose_16f(Matrix_16f* pOut, const Matrix_16f* pM);
//
//// Multiply
//Matrix_16f* MatrixMultiply_16f(Matrix_16f* pOut, const Matrix_16f* pM1, const Matrix_16f* pM2);
//
//// Multiply, followed by a transpose T(M1 * M2)
//Matrix_16f* MatrixMultiplyTranspose_16f(Matrix_16f* pOut, const Matrix_16f* pM1, const Matrix_16f* pM2);
//
//// Inverse
//Matrix_16f* MatrixInverse_16f(Matrix_16f* pOut, float* pDeterminant, const Matrix_16f* pM);
//
//// Build a matrix which scales by (sx, sy, sz)
//Matrix_16f* MatrixScaling_16f(Matrix_16f* pOut, float sx, float sy, float sz);
//
//// Build a matrix which tranlates by (x, y, z)
//Matrix_16f* MatrixTranslation_16f(Matrix_16f* pOut, float x, float y, float z);
//
//// Build a matrix which rotates around the X axis
//Matrix_16f* MatrixRotationX_16f(Matrix_16f* pOut, float angle);
//
//// Build a matrix which rotates around the Y axis
//Matrix_16f* MatrixRotationY_16f(Matrix_16f* pOut, float angle);
//
//// Build a matrix which rotates around the Z axis
//Matrix_16f* MatrixRotationZ_16f(Matrix_16f* pOut, float angle);
//
//// Build a matrix which rotates around an arbitrary axis
//Matrix_16f* MatrixRotationAxis_16f(Matrix_16f* pOut, const Vector3_16f* pV, float angle);
//
//// Build a matrix from a quaternion
//Matrix_16f* MatrixRotationQuaternion_16f(Matrix_16f* pOut, const Quaternion_16f* pQ);
//
//// Yaw around the Y axis, a pitch around the X axis, and a roll around the Z axis
//Matrix_16f* MatrixRotationYawPitchRoll_16f(Matrix_16f* pOut, float yaw, float pitch, float roll);
//
//// Build transformation matrix with null arguments being treated as identity. 
//// Mout = Msc-1 * Msr-1 * Ms * Msr * Msc * Mrc-1 * Mr * Mrc * Mt
//Matrix_16f* MatrixTransformation_16f(Matrix_16f* pOut, const Vector3_16f* pScalingCenter, 
//	const Quaternion_16f* pScalingRotation, const Vector3_16f* pScaling, const Vector3_16f* pRotationCenter, 
//	const Quaternion_16f* pRotation, const Vector3_16f* pTranslation);
//
//// Build 2D transformation matrix in XY plane. Null arguments treated as identity. Mout = Msc-1 * Msr-1 * Ms * Msr * Msc * Mrc-1 * Mr * Mrc * Mt
//Matrix_16f* MatrixTransformation2D_16f(Matrix_16f* pOut, const Vector2_16f* pScalingCenter, float scalingRotation, 
//	const Vector2_16f* pScaling, const Vector2_16f* pRotationCenter, float rotation, const Vector2_16f* pTranslation);
//
//// Build affine transformation matrix. Null arguments treated as identity. Mout = Ms * Mrc-1 * Mr * Mrc * Mt
//Matrix_16f* MatrixAffineTransformation_16f(Matrix_16f* pOut, float scaling, const Vector3_16f* pRotationCenter, 
//	const Quaternion_16f* pRotation, const Vector3_16f* pTranslation);
//
//// Build 2D affine transformation matrix in XY plane. Null arguments treated as identity. Mout = Ms * Mrc-1 * Mr * Mrc * Mt
//Matrix_16f* MatrixAffineTransformation2D_16f(Matrix_16f* pOut, float scaling, const Vector2_16f* pRotationCenter, 
//	float rotation, const Vector2_16f* pTranslation);
//
//// Build a lookat matrix (right-handed)
//Matrix_16f* MatrixLookAtRH_16f(Matrix_16f* pOut, const Vector3_16f* pEye, const Vector3_16f* pAt, const Vector3_16f* pUp);
//
//// Build a lookat matrix (left-handed)
//Matrix_16f* MatrixLookAtLH_16f(Matrix_16f* pOut, const Vector3_16f* pEye, const Vector3_16f* pAt, const Vector3_16f* pUp);
//
//// Build a perspective projection matrix (right-handed)
//Matrix_16f* MatrixPerspectiveRH_16f(Matrix_16f* pOut, float w, float h, float zn, float zf);
//
//// Build a perspective projection matrix (left-handed)
//Matrix_16f* MatrixPerspectiveLH_16f(Matrix_16f* pOut, float w, float h, float zn, float zf);
//
//// Build a perspective projection matrix (right-handed)
//Matrix_16f* MatrixPerspectiveFovRH_16f(Matrix_16f* pOut, float fovy, float aspect, float zn, float zf);
//
//// Build a perspective projection matrix (left-handed)
//Matrix_16f* MatrixPerspectiveFovLH_16f(Matrix_16f* pOut, float fovy, float aspect, float zn, float zf);
//
//// Build a matrix which flattens geometry into a plane, as if casting a shadow from a light
//Matrix_16f* MatrixShadow_16f(Matrix_16f* pOut, const Vector4_16f* pLight, const Plane_16f* pPlane);
//
//// Build a matrix which reflects the coordinate system about a plane
//Matrix_16f* MatrixReflect_16f(Matrix_16f* pOut, const Plane_16f* pPlane);
//}
//
////-----------------------------------------------
//// Quaternion
////-----------------------------------------------
//// Add
//Quaternion* QuaternionAdd(Quaternion* pOut, const Quaternion* pQ1, const Quaternion* pQ2);
//
//// Subtract
//Quaternion* QuaternionSub(Quaternion* pOut, const Quaternion* pQ1, const Quaternion* pQ2);
//
//// Scale
//Quaternion* QuaternionScale(Quaternion* pOut, const Quaternion* pQ, float s);
//
//// Length
//float QuaternionLength(const Quaternion* pQ);
//
//// Length squared, or "norm"
//float QuaternionLengthSqr(const Quaternion* pQ);
//
//// Dot
//float QuaternionDot(const Quaternion* pQ1, const Quaternion* pQ2);
//
//// Identity (0, 0, 0, 1)
//Quaternion* QuaternionIdentity(Quaternion* pOut);
//
//// Is identity
//bool QuaternionIsIdentity(const Quaternion* pQ);
//
//// Conjugate (-x, -y, -z, -w)
//Quaternion* QuaternionConjugate(Quaternion* pOut, const Quaternion* pQ);
//
//extern "C++"
//{
//
//// Compute a quaternion's axis and angle of rotation (expects unit quaternions)
//void QuaternionToAxisAngle(const Quaternion* pQ, Vector3* pAxis, float* pAngle);
//
//// Build a quaternion from a rotation matrix
//Quaternion* QuaternionRotationMatrix(Quaternion* pOut, const Matrix* pM);
//
//// Rotation about an arbitrary axis
//Quaternion* QuaternionRotationAxis(Quaternion* pOut, const Vector3* pV, float angle);
//
//// Yaw around the Y axis, a pitch around the X axis, a roll around the Z axis
//Quaternion* QuaternionRotationYawPitchRoll(Quaternion* pOut, float yaw, float pitch, float roll);
//
//// Quaternion multiplication (Q2 * Q1)
//Quaternion* QuaternionMultiply(Quaternion* pOut, const Quaternion* pQ1, const Quaternion* pQ2);
//
//// Multiply a quaternion by a Vector3
//Vector3* QuaternionMultiply(Vector3* pOut, const Quaternion* pQ, const Vector3* pV);
//
//// Normalize
//Quaternion* QuaternionNormalize(Quaternion* pOut, const Quaternion* pQ);
//
//// Conjugate and re-norm
//Quaternion* QuaternionInverse(Quaternion* pOut, const Quaternion* pQ);
//
//// Expects unit quaternions. If q = (cos(theta), sin(theta) * v); ln(q) = (0, theta * v)
//Quaternion* QuaternionLn(Quaternion* pOut,  const Quaternion* pQ);
//
//// Expects pure quaternions. (w == 0) w is ignored in calculation. If q = (0, theta * v);
//// exp(q) = (cos(theta), sin(theta) * v)
//Quaternion* QuaternionExp(Quaternion* pOut, const Quaternion* pQ);
//
//// Spherical linear interpolation between Q1 (t == 0) and Q2 (t == 1). Expects unit quaternions
//Quaternion* QuaternionSlerp(Quaternion* pOut, const Quaternion* pQ1, const Quaternion* pQ2, float t);
//
//// Spherical quadrangle interpolation (Slerp(Slerp(Q1, C, t), Slerp(A, B, t), 2t(1-t))
//Quaternion* QuaternionSquad(Quaternion* pOut, const Quaternion* pQ1, const Quaternion* pA, 
//	const Quaternion* pB, const Quaternion* pC, float t);
//
//// Setup control points for spherical quadrangle interpolation from Q1 to Q2.  The control points 
//// are chosen in such a way to ensure the continuity of tangents with adjacent segments.
//void QuaternionSquadSetup(Quaternion* pAOut, Quaternion* pBOut, Quaternion* pCOut, 
//	const Quaternion* pQ0, const Quaternion* pQ1, const Quaternion* pQ2, const Quaternion* pQ3);
//
//// Barycentric interpolation. Slerp(Slerp(Q1, Q2, f+g), Slerp(Q1, Q3, f+g), g/(f+g))
//Quaternion* QuaternionBarycentric(Quaternion* pOut, const Quaternion* pQ1, const Quaternion* pQ2, const Quaternion* pQ3, float f, float g);
//}
//
////-----------------------------------------------
//// Quaternion 16-byte aligned
////-----------------------------------------------
//// Add
//Quaternion_16f* QuaternionAdd_16f(Quaternion_16f* pOut, const Quaternion_16f* pQ1, const Quaternion_16f* pQ2);
//
//// Subtract
//Quaternion_16f* QuaternionSub_16f(Quaternion_16f* pOut, const Quaternion_16f* pQ1, const Quaternion_16f* pQ2);
//
//// Scale
//Quaternion_16f* QuaternionScale_16f(Quaternion_16f* pOut, const Quaternion_16f* pQ, const __m128& s);
//
//// Scale
//Quaternion_16f* QuaternionScale_16f(Quaternion_16f* pOut, const Quaternion_16f* pQ, float s);
//
//// Length
//float QuaternionLength_16f(const Quaternion_16f* pQ);
//
//// Length squared, or "norm"
//float QuaternionLengthSqr_16f(const Quaternion_16f* pQ);
//
//// Dot
//float QuaternionDot_16f(const Quaternion_16f* pQ1, const Quaternion_16f* pQ2);
//
//// Identity (0, 0, 0, 1)
//Quaternion_16f* QuaternionIdentity_16f(Quaternion_16f* pOut);
//
//// Is identity
//bool QuaternionIsIdentity_16f(const Quaternion_16f* pQ);
//
//// Conjugate (-x, -y, -z, -w)
//Quaternion_16f* QuaternionConjugate_16f(Quaternion_16f* pOut, const Quaternion_16f* pQ);
//
//extern "C++"
//{
//
//// Compute a quaternion's axis and angle of rotation (expects unit quaternions)
//void QuaternionToAxisAngle_16f(const Quaternion_16f* pQ, Vector3_16f* pAxis, float* pAngle);
//
//// Build a quaternion from a rotation matrix
//Quaternion_16f* QuaternionRotationMatrix_16f(Quaternion_16f* pOut, const Matrix_16f* pM);
//
//// Rotation about an arbitrary axis
//Quaternion_16f* QuaternionRotationAxis_16f(Quaternion_16f* pOut, const Vector3_16f* pV, float angle);
//
//// Yaw around the Y axis, a pitch around the X axis, a roll around the Z axis
//Quaternion_16f* QuaternionRotationYawPitchRoll_16f(Quaternion_16f* pOut, float yaw, float pitch, float roll);
//
//// Quaternion multiplication (Q2 * Q1)
//Quaternion_16f* QuaternionMultiply_16f(Quaternion_16f* pOut, const Quaternion_16f* pQ1, const Quaternion_16f* pQ2);
//
//// Multiply a quaternion by a Vector3
//Vector3_16f* QuaternionMultiply_16f(Vector3_16f* pOut, const Quaternion_16f* pQ, const Vector3_16f* pV);
//
//// Normalize
//Quaternion_16f* QuaternionNormalize_16f(Quaternion_16f* pOut, const Quaternion_16f* pQ);
//
//// Conjugate and re-norm
//Quaternion_16f* QuaternionInverse_16f(Quaternion_16f* pOut, const Quaternion_16f* pQ);
//
//// Expects unit quaternions. If q = (cos(theta), sin(theta) * v); ln(q) = (0, theta * v)
//Quaternion_16f* QuaternionLn_16f(Quaternion_16f* pOut,  const Quaternion_16f* pQ);
//
//// Expects pure quaternions. (w == 0) w is ignored in calculation. If q = (0, theta * v);
//// exp(q) = (cos(theta), sin(theta) * v)
//Quaternion_16f* QuaternionExp_16f(Quaternion_16f* pOut, const Quaternion_16f* pQ);
//
//// Spherical linear interpolation between Q1 (t == 0) and Q2 (t == 1). Expects unit quaternions
//Quaternion_16f* QuaternionSlerp_16f(Quaternion_16f* pOut, const Quaternion_16f* pQ1, const Quaternion_16f* pQ2, float t);
//
//// Spherical quadrangle interpolation (Slerp(Slerp(Q1, C, t), Slerp(A, B, t), 2t(1-t))
//Quaternion_16f* QuaternionSquad_16f(Quaternion_16f* pOut, const Quaternion_16f* pQ1, const Quaternion_16f* pA, 
//	const Quaternion_16f* pB, const Quaternion_16f* pC, float t);
//
//// Setup control points for spherical quadrangle interpolation from Q1 to Q2.  The control points 
//// are chosen in such a way to ensure the continuity of tangents with adjacent segments.
//void QuaternionSquadSetup_16f(Quaternion_16f* pAOut, Quaternion_16f* pBOut, Quaternion_16f* pCOut, 
//	const Quaternion_16f* pQ0, const Quaternion_16f* pQ1, const Quaternion_16f* pQ2, const Quaternion_16f* pQ3);
//
//// Barycentric interpolation. Slerp(Slerp(Q1, Q2, f+g), Slerp(Q1, Q3, f+g), g/(f+g))
//Quaternion_16f* QuaternionBarycentric_16f(Quaternion_16f* pOut, const Quaternion_16f* pQ1, const Quaternion_16f* pQ2, 
//	const Quaternion_16f* pQ3, float f, float g);
//}
//
////-----------------------------------------------
//// Plane
////-----------------------------------------------
//
//// ax + by + cz + dw
//float PlaneDot(const Plane* pP, const Vector4* pV);
//
//// ax + by + cz + d
//float PlaneDotCoord(const Plane* pP, const Vector3* pV);
//
//// ax + by + cz
//float PlaneDotNormal(const Plane* pP, const Vector3* pV);
//
//// Scale
//Plane* PlaneScale(Plane* pOut, const Plane* pP, float s);
//
//extern "C"
//{
//// Normalize plane (so that |a,b,c| == 1
//Plane* PlaneNormalize(Plane* pOut, const Plane* pP);
//
//// Find intersection point between a plane and a line. If the line is parallel to the plane, null is returned.
//Vector3* PlaneIntersectLine(Vector3* pOut, const Plane* pP, const Vector3* pV1, const Vector3* pV2);
//
//// Construct a plane from a point and a normal
//Plane* PlaneFromPointNormal(Plane* pOut, const Vector3* pPoint, const Vector3* pNormal);
//
//// Construct a plane from 3 points
//Plane* PlaneFromPoints(Plane* pOut, const Vector3* pV1, const Vector3* pV2, const Vector3* pV3);
//
//// Transform a plane by a matrix. The vector (a,b,c) must be normal. M should be the inverse transpose of the transformation desired.
//Plane* PlaneTransform(Plane* pOut, const Plane* pP, const Matrix* pM);
//}
//
////-----------------------------------------------
//// Plane 16-byte aligned
////-----------------------------------------------
//// ax + by + cz + dw
//float PlaneDot_16f(const Plane_16f* pP, const Vector4_16f* pV);
//
//// ax + by + cz + d
//float PlaneDotCoord_16f(const Plane_16f* pP, const Vector3_16f* pV);
//
//// ax + by + cz
//float PlaneDotNormal(const Plane_16f* pP, const Vector3_16f* pV);
//
//// Scale
//Plane_16f* PlaneScale_16f(Plane_16f* pOut, const Plane_16f* pP, float s);
//
//// Scale
//Plane_16f* PlaneScale_16f(Plane_16f* pOut, const Plane_16f* pP, const __m128& s);
//
//extern "C"
//{
//// Normalize plane (so that |a,b,c| == 1
//Plane_16f* PlaneNormalize_16f(Plane_16f* pOut, const Plane_16f* pP);
//
//// Find intersection point between a plane and a line. If the line is parallel to the plane, null is returned.
//Vector3_16f* PlaneIntersectLine_16f(Vector3_16f* pOut, const Plane_16f* pP, const Vector3_16f* pV1, const Vector3_16f* pV2);
//
//// Construct a plane from a point and a normal
//Plane_16f* PlaneFromPointNormal_16f(Plane_16f* pOut, const Vector3_16f* pPoint, const Vector3_16f* pNormal);
//
//// Construct a plane from 3 points
//Plane_16f* PlaneFromPoints_16f(Plane_16f* pOut, const Vector3_16f* pV1, const Vector3_16f* pV2, const Vector3_16f* pV3);
//
//// Transform a plane by a matrix. The vector (a,b,c) must be normal. M should be the inverse transpose of the transformation desired.
//Plane_16f* PlaneTransform_16f(Plane_16f* pOut, const Plane_16f* pP, const Matrix_16f* pM);
//}
//
////-----------------------------------------------
//// Color
////-----------------------------------------------
//
//// (1-r, 1-g, 1-b, a);
//Color* ColorNegative(Color* pOut, const Color* pC);
//
//// Add
//Color* ColorAdd(Color* pOut, const Color* pC1, const Color* pC2);
//
//// Subtract
//Color* ColorSub(Color* pOut, const Color* pC1, const Color* pC2);
//
//// Scale
//Color* ColorScale(Color* pOut, const Color* pC, float s);
//
//// Modulate (r1*r2, g1*g2, b1*b2, a1*a2)
//Color* ColorModulate(Color* pOut, const Color* pC1, const Color* pC2);
//
//// LERP of r,g,b, and a. C1 + s(C2-C1)
//Color* ColorLerp(Color* pOut, const Color* pC1, const Color* pC2, float s);
//
//extern "C"
//{
//// Interpolate r,g,b between desaturated color and color. DesaturatedColor + s(Color - DesaturatedColor)
//Color* ColorAdjustSaturation(Color* pOut, const Color* pC, float s);
//
//// Interpolate r,g,b, between 50% grey and color. Grey + s(Color - Grey)
//Color* ColorAdjustContrast(Color* pOut, const Color* pC, float c);
//}
//
////-----------------------------------------------
//// Color 16-byte aligned
////-----------------------------------------------
//// (1-r, 1-g, 1-b, a);
//Color_16f* ColorNegative_16f(Color_16f* pOut, const Color_16f* pC);
//
//// Add
//Color_16f* ColorAdd_16f(Color_16f* pOut, const Color_16f* pC1, const Color_16f* pC2);
//
//// Subtract
//Color_16f* ColorSub_16f(Color_16f* pOut, const Color_16f* pC1, const Color_16f* pC2);
//
//// Scale
//Color_16f* ColorScale_16f(Color_16f* pOut, const Color_16f* pC, float s);
//
//// Scale
//Color_16f* ColorScale_16f(Color_16f* pOut, const Color_16f* pC, const __m128& s);
//
//// Modulate (r1*r2, g1*g2, b1*b2, a1*a2)
//Color_16f* ColorModulate_16f(Color_16f* pOut, const Color_16f* pC1, const Color_16f* pC2);
//
//// LERP of r,g,b, and a. C1 + s(C2-C1)
//Color_16f* ColorLerp_16f(Color_16f* pOut, const Color_16f* pC1, const Color_16f* pC2, float s);
//
//// LERP of r,g,b, and a. C1 + s(C2-C1)
//Color_16f* ColorLerp_16f(Color_16f* pOut, const Color_16f* pC1, const Color_16f* pC2, const __m128& s);
//extern "C++"
//{
//// Interpolate r,g,b between desaturated color and color. DesaturatedColor + s(Color - DesaturatedColor)
//Color_16f* ColorAdjustSaturation_16f(Color_16f* pOut, const Color_16f* pC, float s);
//
//// Interpolate r,g,b between desaturated color and color. DesaturatedColor + s(Color - DesaturatedColor)
//Color_16f* ColorAdjustSaturation_16f(Color_16f* pOut, const Color_16f* pC, const __m128& s);
//
//// Interpolate r,g,b, between 50% grey and color. Grey + c(Color - Grey)
//Color_16f* ColorAdjustContrast_16f(Color_16f* pOut, const Color_16f* pC, float c);
//
//// Interpolate r,g,b, between 50% grey and color. Grey + c(Color - Grey)
//Color_16f* ColorAdjustContrast_16f(Color_16f* pOut, const Color_16f* pC, const __m128& c);
//}

/**************************************************************************************************
* FILE INCLUDES
**************************************************************************************************/
//#include "SumVector2.inl"
//#include "SumVector2_16f.inl"
//#include "SumVector3.inl"
//#include "SumVector3_16f.inl"
//#include "SumVector4.inl"
//#include "SumVector4_16f.inl"
//#include "SumMatrix.inl"
//#include "SumMatrix_16f.inl"
//#include "SumQuaternion.inl"
//#include "SumQuaternion_16f.inl"
//#include "SumPlane.inl"
//#include "SumPlane_16f.inl"
//#include "SumColor.inl"
//#include "SumColor_16f.inl"

#endif