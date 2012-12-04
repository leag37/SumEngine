//*************************************************************************************************
// Title: SumMatrix.cpp
// Author: Gael Huber
// Description: Matrix math functions.
//*************************************************************************************************
#include "SumMatrix.h"

//*************************************************************************************************
// Determinant
//
//11 12 13 14
//21 22 23 24
//31 32 33 34
//41 42 43 44
//
//11 |22 23 24| - 12 |21 23 24| + 13 |21 22 24| - 14 |21 22 23|
//   |32 33 34|	   |31 33 34|	   |31 32 34|      |31 32 33|
//   |42 43 44|      |41 43 44|      |41 42 44|      |41 42 43|
//
//+11 ( 22 |33 34| - 23 |32 34| + 24 |32 33|)
//		 |43 44|	  |42 44|      |42 43|
//-12 ( 21 |33 34| - 23 |31 34| + 24 |31 33|)
//		 |43 44|      |41 44|      |41 43|
//+13 ( 21 |32 34| - 22 |31 34| + 24 |31 32|)
//	     |42 44|      |41 44|      |41 42|
//-14 ( 21 |32 33| - 22 |31 33| + 23 |31 32|)
//		 |42 43|      |41 43|      |41 42|
//
//+11 ( 22 (33.44 - 34.43) - 23 (32.44 - 34.42) + 24 (32.43 - 33.42))
//-12 ( 21 (33.44 - 34.43) - 23 (31.44 - 34.41) + 24 (31.43 - 33.41))
//+13 ( 21 (32.44 - 34.42) - 22 (31.44 - 34.41) + 24 (31.42 - 32.41))
//-14 ( 21 (32.43 - 33.42) - 22 (31.43 - 33.41) + 23 (31.42 - 32.41))
//
// Phase 1 - primary inner products
//v1 = zzyy -> 3
//v2 = wwwz -> 4
//v3 = yxxx -> 3
//v4 = wwwz -> 4
//v5 = yxxx -> 3
//v6 = zzyy -> 4
//
//p0 = v1.v2
//p1 = v3.v4
//p2 = v5.v6
//
//v1 = wwwz -> 3
//v2 = zzyy -> 4
//v3 = wwwz -> 3
//v4 = yxxx -> 4
//v5 = zzyy -> 3
//v6 = yxxx -> 4
//
//v1 = v1.v2
//v3 = v3.v4
//v5 = v5.v6
//
// Phase 2 - difference of inner products
//p0 = p0 - v1
//p1 = p1 - v3
//p2 = p2 - v5
//
// Phase 3 - secondary inner products
//v1 = yxxx -> 2
//v2 = zzyy -> 2
//v3 = wwwz -> 2
//
//p0 = p0.v1
//p1 = p1.v1
//p2 = p2.v2
//
// Phase 4 - aggregate sum
//p0 = p0 - p1
//p0 = p0 + p2
//
//// Final product
//p1 = r1 * +-+-
//result = dot(p0, p1)
//*************************************************************************************************
Vector MatrixDeterminant(const Matrix& m)
{
	// Phase 1
	return VectorZero();
}

//*************************************************************************************************
// 
//*************************************************************************************************
// Decompose
SBOOL MatrixDecompose(Vector* pOutScale, Vector* pOutRotation, Vector* pOutTranslation, const Matrix& m);

//*************************************************************************************************
// 
//*************************************************************************************************
// Transpose
Matrix MatrixTranspose(const Matrix& m);

//*************************************************************************************************
// Multiply
//
//[a b c d]
//[e f g h]
//[i j k l]
//[m n o p]
//
//[q r s t] -> shuffle
//[u v w x]
//[y z 0 1]
//[2 3 4 5]
//
//A*B = 
//[aq+bu+cy+d2 ar+bv+cz+d3 as+bw+c0+d4 at+bx+c1+d5]
//[eq+fu+gy+h2 er+fv+gz+h3 es+fw+g0+h4 et+fx+g1+h5]
//...
//
// Process
//---------
//
//Desired matrix:
//[aq ar as at]
//[bu bv bw bx]
//[cy cz c0 c1]
//[d2 d3 d4 d5]
//
//to yield:
//[a a a a]  -> splat a, b, c, d
//[b b b b]
//[c c c c]
//[d d d d]
//
//[q r s t]
//[u v w x]
//[y z 0 1]
//[2 3 4 5]
//
//// For one row of matrix MResult
//1. Splat a, b, c, d into vTemp1-4
//2. Multiply vTemp1-4 . m2
//3. m.r[index] = vTemp1 + vTemp2 + vTemp3 + vTemp4
//*************************************************************************************************
Matrix MatrixMultiply(const Matrix& m1, const Matrix& m2)
{
	Matrix m;
	
	// Row 1
	Vector vTemp1 = _mm_load1_ps(&m1._11);
	Vector vTemp2 = _mm_load1_ps(&m1._12);
	Vector vTemp3 = _mm_load1_ps(&m1._13);
	Vector vTemp4 = _mm_load1_ps(&m1._14);

	vTemp1 = _mm_mul_ps(vTemp1, m2.r[0]);
	vTemp2 = _mm_mul_ps(vTemp2, m2.r[1]);
	vTemp3 = _mm_mul_ps(vTemp3, m2.r[2]);
	vTemp4 = _mm_mul_ps(vTemp4, m2.r[3]);

	vTemp1 = _mm_add_ps(vTemp1, vTemp2);
	vTemp3 = _mm_add_ps(vTemp3, vTemp4);
	m.r[0] = _mm_add_ps(vTemp1, vTemp3);

	// Row 2
	vTemp1 = _mm_load1_ps(&m1._21);
	vTemp2 = _mm_load1_ps(&m1._22);
	vTemp3 = _mm_load1_ps(&m1._23);
	vTemp4 = _mm_load1_ps(&m1._24);

	vTemp1 = _mm_mul_ps(vTemp1, m2.r[0]);
	vTemp2 = _mm_mul_ps(vTemp2, m2.r[1]);
	vTemp3 = _mm_mul_ps(vTemp3, m2.r[2]);
	vTemp4 = _mm_mul_ps(vTemp4, m2.r[3]);

	vTemp1 = _mm_add_ps(vTemp1, vTemp2);
	vTemp3 = _mm_add_ps(vTemp3, vTemp4);
	m.r[1] = _mm_add_ps(vTemp1, vTemp3);

	// Row 3
	vTemp1 = _mm_load1_ps(&m1._31);
	vTemp2 = _mm_load1_ps(&m1._32);
	vTemp3 = _mm_load1_ps(&m1._33);
	vTemp4 = _mm_load1_ps(&m1._34);

	vTemp1 = _mm_mul_ps(vTemp1, m2.r[0]);
	vTemp2 = _mm_mul_ps(vTemp2, m2.r[1]);
	vTemp3 = _mm_mul_ps(vTemp3, m2.r[2]);
	vTemp4 = _mm_mul_ps(vTemp4, m2.r[3]);

	vTemp1 = _mm_add_ps(vTemp1, vTemp2);
	vTemp3 = _mm_add_ps(vTemp3, vTemp4);
	m.r[2] = _mm_add_ps(vTemp1, vTemp3);

	// Row 4
	vTemp1 = _mm_load1_ps(&m1._41);
	vTemp2 = _mm_load1_ps(&m1._42);
	vTemp3 = _mm_load1_ps(&m1._43);
	vTemp4 = _mm_load1_ps(&m1._44);

	vTemp1 = _mm_mul_ps(vTemp1, m2.r[0]);
	vTemp2 = _mm_mul_ps(vTemp2, m2.r[1]);
	vTemp3 = _mm_mul_ps(vTemp3, m2.r[2]);
	vTemp4 = _mm_mul_ps(vTemp4, m2.r[3]);

	vTemp1 = _mm_add_ps(vTemp1, vTemp2);
	vTemp3 = _mm_add_ps(vTemp3, vTemp4);
	m.r[3] = _mm_add_ps(vTemp1, vTemp3);

	return m;
}

//*************************************************************************************************
// 
//*************************************************************************************************
// Multiply, followed by a transpose T(M1 * M2)
Matrix MatrixMultiplyTranspose(const Matrix& m1, const Matrix& m2);

//*************************************************************************************************
// 
//*************************************************************************************************
// Inverse
Matrix MatrixInverse(Vector* pDeterminant, const Matrix& m);

//*************************************************************************************************
// 
//*************************************************************************************************
// Build a matrix which scales by (sx, sy, sz)
Matrix MatrixScaling(float sx, float sy, float sz);

//*************************************************************************************************
// 
//*************************************************************************************************
// Build a matrix which scales by (sx, sy, sz)
Matrix MatrixScaling(Vector sx, Vector sy, Vector sz);

//*************************************************************************************************
// 
//*************************************************************************************************
// Build a matrix which tranlates by (x, y, z)
Matrix MatrixTranslation(float x, float y, float z);

//*************************************************************************************************
// 
//*************************************************************************************************
// Build a matrix which tranlates by (x, y, z)
Matrix MatrixTranslation(Vector x, Vector y, Vector z);

//*************************************************************************************************
// 
//*************************************************************************************************
// Build a matrix which rotates around the X axis
Matrix MatrixRotationX(float angle);

//*************************************************************************************************
// 
//*************************************************************************************************
// Build a matrix which rotates around the X axis
Matrix MatrixRotationX(Vector angle);

//*************************************************************************************************
// 
//*************************************************************************************************
// Build a matrix which rotates around the Y axis
Matrix MatrixRotationY(float angle);

//*************************************************************************************************
// 
//*************************************************************************************************
// Build a matrix which rotates around the Y axis
Matrix MatrixRotationY(Vector angle);

//*************************************************************************************************
// 
//*************************************************************************************************
// Build a matrix which rotates around the Z axis
Matrix MatrixRotationZ(float angle);

//*************************************************************************************************
// 
//*************************************************************************************************
// Build a matrix which rotates around the Z axis
Matrix MatrixRotationZ(Vector angle);

//*************************************************************************************************
// 
//*************************************************************************************************
// Build a matrix which rotates around an arbitrary axis
Matrix MatrixRotationAxis(const Vector v, float angle);

//*************************************************************************************************
// 
//*************************************************************************************************
// Build a matrix which rotates around an arbitrary axis
Matrix MatrixRotationAxis(const Vector v, Vector angle);

//*************************************************************************************************
// 
//*************************************************************************************************
// Build a matrix from a quaternion
Matrix MatrixRotationQuaternion(const Vector q);

//*************************************************************************************************
// 
//*************************************************************************************************
// Yaw around the Y axis, a pitch around the X axis, and a roll around the Z axis
Matrix MatrixRotationYawPitchRoll(float yaw, float pitch, float roll);

//*************************************************************************************************
// 
//*************************************************************************************************
// Yaw around the Y axis, a pitch around the X axis, and a roll around the Z axis
Matrix MatrixRotationYawPitchRoll(Vector yaw, Vector pitch, Vector roll);

//*************************************************************************************************
// 
//*************************************************************************************************
// Build transformation matrix with null arguments being treated as identity. 
// Mout = Msc-1 * Msr-1 * Ms * Msr * Msc * Mrc-1 * Mr * Mrc * Mt
Matrix MatrixTransformation(const Vector scalingCenter, const Vector scalingRotation, 
	const Vector scaling, const Vector& rotationCenter, const Vector& rotation, const Vector& translation);

//*************************************************************************************************
// 
//*************************************************************************************************
// Build 2D transformation matrix in XY plane. Null arguments treated as identity. Mout = Msc-1 * Msr-1 * Ms * Msr * Msc * Mrc-1 * Mr * Mrc * Mt
Matrix MatrixTransformation2D(const Vector scalingCenter, float scalingRotation, const Vector scaling,
	const Vector rotationCenter, float rotation, const Vector& translation);

//*************************************************************************************************
// 
//*************************************************************************************************
// Build 2D transformation matrix in XY plane. Null arguments treated as identity. Mout = Msc-1 * Msr-1 * Ms * Msr * Msc * Mrc-1 * Mr * Mrc * Mt
Matrix MatrixTransformation2D(const Vector scalingCenter, const Vector scalingRotation, const Vector scaling,
	const Vector& rotationCenter, const Vector& rotation, const Vector& translation);

//*************************************************************************************************
// 
//*************************************************************************************************
// Build affine transformation matrix. Null arguments treated as identity. Mout = Ms * Mrc-1 * Mr * Mrc * Mt
Matrix MatrixAffineTransformation(float scaling, const Vector rotationCenter, const Vector rotation, 
	const Vector translation);

//*************************************************************************************************
// 
//*************************************************************************************************
// Build affine transformation matrix. Null arguments treated as identity. Mout = Ms * Mrc-1 * Mr * Mrc * Mt
Matrix MatrixAffineTransformation(const Vector scaling, const Vector rotationCenter, const Vector rotation, 
	const Vector& translation);

//*************************************************************************************************
// 
//*************************************************************************************************
// Build 2D affine transformation matrix in XY plane. Null arguments treated as identity. Mout = Ms * Mrc-1 * Mr * Mrc * Mt
Matrix MatrixAffineTransformation2D(float scaling, const Vector rotationCenter, float rotation, const Vector translation);

//*************************************************************************************************
// 
//*************************************************************************************************
// Build 2D affine transformation matrix in XY plane. Null arguments treated as identity. Mout = Ms * Mrc-1 * Mr * Mrc * Mt
Matrix MatrixAffineTransformation2D(const Vector scaling, const Vector rotationCenter, 
	const Vector rotation, const Vector& translation);

//*************************************************************************************************
// 
//*************************************************************************************************
// Build a lookat matrix (right-handed)
Matrix MatrixLookAtRH(const Vector eye, const Vector at, const Vector up);

//*************************************************************************************************
// 
//*************************************************************************************************
// Build a lookat matrix (left-handed)
Matrix MatrixLookAtLH(const Vector eye, const Vector at, const Vector up);

//*************************************************************************************************
// 
//*************************************************************************************************
// Build a perspective projection matrix (right-handed)
Matrix MatrixPerspectiveRH(float w, float h, float zn, float zf);

//*************************************************************************************************
// 
//*************************************************************************************************
// Build a perspective projection matrix (right-handed)
Matrix MatrixPerspectiveRH(const Vector w, const Vector h, const Vector zn, const Vector& zf);

//*************************************************************************************************
// 
//*************************************************************************************************
// Build a perspective projection matrix (left-handed)
Matrix MatrixPerspectiveLH(float w, float h, float zn, float zf);

//*************************************************************************************************
// 
//*************************************************************************************************
// Build a perspective projection matrix (left-handed)
Matrix MatrixPerspectiveLH(const Vector w, const Vector h, const Vector zn, const Vector& zf);

//*************************************************************************************************
// 
//*************************************************************************************************
// Build a perspective projection matrix (right-handed)
Matrix MatrixPerspectiveFovRH(float fovy, float aspect, float zn, float zf);

//*************************************************************************************************
// 
//*************************************************************************************************
// Build a perspective projection matrix (right-handed)
Matrix MatrixPerspectiveFovRH(const Vector fovy, const Vector aspect, const Vector zn, const Vector& zf);

//*************************************************************************************************
// 
//*************************************************************************************************
// Build a perspective projection matrix (left-handed)
Matrix MatrixPerspectiveFovLH(float fovy, float aspect, float zn, float zf);

//*************************************************************************************************
// 
//*************************************************************************************************
// Build a perspective projection matrix (left-handed)
Matrix MatrixPerspectiveFovLH(const Vector fovy, const Vector aspect, const Vector zn, const Vector& zf);

//*************************************************************************************************
// 
//*************************************************************************************************
// Build a matrix which flattens geometry into a plane, as if casting a shadow from a light
Matrix MatrixShadow(const Vector light, const Vector plane);

//*************************************************************************************************
// 
//*************************************************************************************************
// Build a matrix which reflects the coordinate system about a plane
Matrix MatrixReflect(const Vector plane);

//*************************************************************************************************
// 
//*************************************************************************************************
// Creates a tensor product of given two 3D vectors
Matrix MatrixTensorProduct(const Vector v1, const Vector v2);
