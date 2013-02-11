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
// v1 = zzyy -> 3
// v2 = wwwz -> 4
// v3 = yxxx -> 3
// v4 = wwwz -> 4
// v5 = yxxx -> 3
// v6 = zzyy -> 4
//
// p0 = v1.v2
// p1 = v3.v4
// p2 = v5.v6
//
// v1 = wwwz -> 3
// v2 = zzyy -> 4
// v3 = wwwz -> 3
// v4 = yxxx -> 4
// v5 = zzyy -> 3
// v6 = yxxx -> 4
//
// v1 = v1.v2
// v3 = v3.v4
// v5 = v5.v6
//
// Phase 2 - difference of inner products
// p0 = p0 - v1
// p1 = p1 - v3
// p2 = p2 - v5
//
// Phase 3 - secondary inner products
// v1 = yxxx -> 2
// v2 = zzyy -> 2
// v3 = wwwz -> 2
//
// p0 = p0.v1
// p1 = p1.v1
// p2 = p2.v2
//
// Phase 4 - aggregate sum
// p0 = p0 - p1
// p0 = p0 + p2
//
// Final product
// p1 = r1 * +-+-
// result = dot(p0, p1)
//*************************************************************************************************
Vector MatrixDeterminant(const Matrix& m)
{
	// Phase 1 - primary inner products
	// v1 = zzyy -> 3
	// v2 = wwwz -> 4
	// v3 = yxxx -> 3
	// v4 = wwwz -> 4
	// v5 = yxxx -> 3
	// v6 = zzyy -> 4
	//
	// p0 = v1.v2
	// p1 = v3.v4
	// p2 = v5.v6
	
	Vector v1 = _mm_shuffle_ps(m.r[2], m.r[2], _MM_SHUFFLE(1, 1, 2, 2));
	Vector v2 = _mm_shuffle_ps(m.r[3], m.r[3], _MM_SHUFFLE(2, 3, 3, 3));
	Vector v3 = _mm_shuffle_ps(m.r[2], m.r[2], _MM_SHUFFLE(0, 0, 0, 1));
	Vector v4 = _mm_shuffle_ps(m.r[3], m.r[3], _MM_SHUFFLE(2, 3, 3, 3));
	Vector v5 = _mm_shuffle_ps(m.r[2], m.r[2], _MM_SHUFFLE(0, 0, 0, 1));
	Vector v6 = _mm_shuffle_ps(m.r[3], m.r[3], _MM_SHUFFLE(1, 1, 2, 2));

	Vector p0 = _mm_mul_ps(v1, v2);
	Vector p1 = _mm_mul_ps(v3, v4);
	Vector p2 = _mm_mul_ps(v5, v6);
	
	// Phase 2 - difference of inner products
	// p0 = p0 - v1
	// p1 = p1 - v3
	// p2 = p2 - v5
	
	p0 = _mm_sub_ps(p0, v1);
	p1 = _mm_sub_ps(p1, v3);
	p2 = _mm_sub_ps(p2, v5);

	// Phase 3 - secondary inner products
	// v1 = yxxx -> 2
	// v2 = zzyy -> 2
	// v3 = wwwz -> 2
	//
	// p0 = p0.v1
	// p1 = p1.v2
	// p2 = p2.v3
	
	v1 = _mm_shuffle_ps(m.r[1], m.r[1], _MM_SHUFFLE(0, 0, 0, 1));
	v2 = _mm_shuffle_ps(m.r[1], m.r[1], _MM_SHUFFLE(1, 1, 2, 2));
	v3 = _mm_shuffle_ps(m.r[1], m.r[1], _MM_SHUFFLE(2, 3, 3, 3));

	p0 = _mm_mul_ps(p0, v1);
	p1 = _mm_mul_ps(p1, v2);
	p2 = _mm_mul_ps(p2, v3);

	// Phase 4 - aggregate sum
	// p0 = p0 - p1
	// p0 = p0 + p2
	
	p0 = _mm_sub_ps(p0, p1);
	p0 = _mm_add_ps(p0, p2);

	// Final product
	// p1 = r1 * +-+-
	// result = dot(p0, p1)
	p1 = _mm_mul_ps(m.r[0], gVDeterminantNegate);
	return Vec4Dot(p0, p1);
}

//*************************************************************************************************
// Decompose 
//*************************************************************************************************
//SBOOL MatrixDecompose(Vector* pOutScale, Vector* pOutRotation, Vector* pOutTranslation, const Matrix& m)
//{
//	// Create row vector u, v, and w
//	Vector u = _mm_load_ps(&m._11);
//	Vector v = _mm_load_ps(&m._21);
//	Vector w = _mm_load_ps(&m._31);
//
//	// Create orthonormal vectors 
//	Vector s1 = Vec3Length(u);
//	if(Vec3Equal(s1, gVZero))
//		return false;
//
//	Vector u0 = VectorReciprocal(s1);
//	u0 = _mm_mul_ps(u, u0);
//
//	Vector temp = Vec3Dot(v, u0);
//	temp = _mm_mul_ps(temp, u0);
//	temp = _mm_sub_ps(v, temp);
//	Vector s2 = Vec3Length(temp);
//	if(Vec3Equal(s2, gVZero))
//		return false;
//
//	Vector v0 = VectorReciprocal(s2);
//	v0 = _mm_mul_ps(v0, temp);
//	
//	temp = Vec3Dot(w, u0);
//	temp = _mm_mul_ps(temp, u0);
//	temp = _mm_sub_ps(w, temp);
//	Vector temp1 = Vec3Dot(w, v0);
//	temp1 = _mm_mul_ps(temp1, v0);
//	temp = _mm_sub_ps(temp, temp1);
//	Vector s3 = Vec3Length(temp);
//	if(Vec3Equal(s3, gVZero))
//		return false;
//
//	Vector w0 = VectorReciprocal(s3);
//	w0 = _mm_mul_ps(temp, w0);
//
//	// Populate reciprocal matrix
//	Matrix r = Matrix(u0, v0, w0, gVIdentityR3);
//	Vector det = MatrixDeterminant(r);
//	if(Vec4Equal(det, gVNegOne))
//	{
//		r.r[2] = _mm_mul_ps(r.r[2], gV3Negate);
//		s3 = _mm_mul_ps(s3, gVNegOne);
//	}
//
//	// Populate scale
//	temp = _mm_unpacklo_ps(s1, s2);
//	temp = _mm_shuffle_ps(temp, s3, _MM_SHUFFLE(0, 0, 1, 0));
//	*pOutScale = temp;
//
//	// Populate quaternion
//	*pOutRotation = QuaternionRotationMatrix(r);
//
//	// Populate translation
//	*pOutTranslation = _mm_load_ps(r.m[3]);
//
//	return true;
//}

//*************************************************************************************************
// Transpose
//
// [11 12 13 14]
// [21 22 23 24]
// [31 32 33 34]
// [41 42 43 44]
//
// [11 21 31 41]
// [12 22 32 42]
// [13 23 33 43]
// [14 24 34 44]
//
// v1 = _mm_unpacklo_ps(r1, r2)
// v1 = [11 21 12 22]
// v2 = _mm_unpacklo_ps(r3, r4)
// v2 = [31 41 32 42]
// m1 = _mm_shuffle_ps(v1, v2, _MM_SHUFFLE(1, 0, 1, 0))
// m2 = _mm_shuffle_ps(v1, v2, _MM_SHUFFLE(3, 2, 3, 2))
//
// v1 = _mm_unpackhi_ps(r1, r2)
// v1 = [13 23 14 24]
// v2 = _mm_unpackhi_ps(r3, r4)
// v2 = [33 43 34 44]
// m3 = _mm_shuffle_ps(v1, v2, _MM_SHUFFLE(1, 0, 1, 0))
// m4 = _mm_shuffle_ps(v1, v2, _MM_SHUFFLE(3, 2, 3, 2))
//*************************************************************************************************
Matrix MatrixTranspose(const Matrix& m)
{
	// Unpack lo and solve for first two rows
	Vector vTemp1 = _mm_unpacklo_ps(m.r[0], m.r[1]);
	Vector vTemp2 = _mm_unpacklo_ps(m.r[2], m.r[3]);

	Matrix result;
	result.r[0] = _mm_shuffle_ps(vTemp1, vTemp2, _MM_SHUFFLE(1, 0, 1, 0));
	result.r[1] = _mm_shuffle_ps(vTemp1, vTemp2, _MM_SHUFFLE(3, 2, 3, 2));

	// Unpack hi and solve for last two rows
	vTemp1 = _mm_unpackhi_ps(m.r[0], m.r[1]);
	vTemp2 = _mm_unpackhi_ps(m.r[2], m.r[3]);

	result.r[2] = _mm_shuffle_ps(vTemp1, vTemp2, _MM_SHUFFLE(1, 0, 1, 0));
	result.r[3] = _mm_shuffle_ps(vTemp1, vTemp2, _MM_SHUFFLE(3, 2, 3, 2));

	return result;
}

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
// Multiply, followed by a transpose T(M1 * M2) 
//*************************************************************************************************
Matrix MatrixMultiplyTranspose(const Matrix& m1, const Matrix& m2)
{
	Matrix result = MatrixMultiply(m1, m2);
	return MatrixTranspose(result);
}

//*************************************************************************************************
// Inverse
//*************************************************************************************************
//Matrix MatrixInverse(Vector* pDeterminant, const Matrix& m)
//{
//	// Get the determinant
//	Vector determinant = MatrixDeterminant(m);
//
//	// If the determinant is not equal to 0
//	if(Vec4NotEqual(determinant, gVZero))
//	{
//		// Start with two base matrices - one as identity matrix, the other as the parametrized matrix
//		Matrix m1 = MatrixIdentity();
//		Matrix m2 = m;
//
//
//	}
//
//	return m;
//}

//*************************************************************************************************
// Build a matrix which scales by (sx, sy, sz)
//*************************************************************************************************
Matrix MatrixScaling(float sx, float sy, float sz)
{
	Matrix m;
	m.r[0] = _mm_set_ps(0.0f, 0.0f, 0.0f, sx);
	m.r[1] = _mm_set_ps(0.0f, 0.0f, sy, 0.0f);
	m.r[2] = _mm_set_ps(0.0f, sz, 0.0f, 0.0f);
	m.r[3] = gVIdentityR3;
	return m;
}

//*************************************************************************************************
//  Build a matrix which scales by (sx, sy, sz)
//*************************************************************************************************
Matrix MatrixScaling(Vector s)
{
	Matrix m;
	m.r[0] = _mm_and_ps(gVXMask, s);
	m.r[1] = _mm_and_ps(gVYMask, s);
	m.r[2] = _mm_and_ps(gVZMask, s);
	m.r[3] = gVIdentityR3;
	return m;
}

//*************************************************************************************************
// Build a matrix which tranlates by (x, y, z) 
//*************************************************************************************************
Matrix MatrixTranslation(float x, float y, float z)
{
	Matrix m;
	m.r[0] = gVIdentityR0;
	m.r[1] = gVIdentityR1;
	m.r[2] = gVIdentityR2;
	m.r[3] = _mm_set_ps(1.0f, z, y, x);
	return m;
}

//*************************************************************************************************
//  Build a matrix which tranlates by (x, y, z)
//*************************************************************************************************
Matrix MatrixTranslation(Vector t)
{
	Matrix m;
	m.r[0] = gVIdentityR0;
	m.r[1] = gVIdentityR1;
	m.r[2] = gVIdentityR2;
	m.r[3] = t;
	return m;
}

//*************************************************************************************************
// Build a matrix which rotates around the X axis 
//*************************************************************************************************
Matrix MatrixRotationX(float angle)
{
	// Load sin and cos values
	SFLOAT sin = sinf(angle);
	SFLOAT cos = cosf(angle);

	Vector vSin = _mm_set_ss(sin);
	Vector vCos = _mm_set_ss(cos);

	Matrix m;

	// Load first row
	m.r[0] = gVIdentityR0;

	// Load second row [0 cos sin 0]
	m.r[1] = _mm_shuffle_ps(vCos, vSin, _MM_SHUFFLE(1, 0, 0, 1));

	// Get third row [0 -sin cos 0]
	vCos = _mm_shuffle_ps(vCos, vCos, _MM_SHUFFLE(3, 1, 2, 0));
	vCos = _mm_mul_ps(vCos, gVNegateY);
	m.r[2] = vCos;

	// Load fourth row
	m.r[3] = gVIdentityR3;

	return m;
}

////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build a matrix which rotates around the X axis
//Matrix MatrixRotationX(Vector angle);
//
//*************************************************************************************************
// Build a matrix which rotates around the Y axis 
//*************************************************************************************************
Matrix MatrixRotationY(float angle)
{
	// Load sin and cos
	SFLOAT sin = sinf(angle);
	SFLOAT cos = cosf(angle);

	Vector vSin = _mm_set_ss(sin);
	Vector vCos = _mm_set_ss(cos);

	// Load first and third rows
	vSin = _mm_shuffle_ps(vSin, vCos, _MM_SHUFFLE(3, 0, 3, 0));
	vCos = _mm_shuffle_ps(vSin, vSin, _MM_SHUFFLE(3, 0, 1, 2));
	vCos = _mm_mul_ps(vCos, gVNegateZ);

	// Set all rows
	Matrix m;
	m.r[0] = vCos;
	m.r[1] = gVIdentityR1;
	m.r[2] = vSin;
	m.r[3] = gVIdentityR3;
	return m;
}

////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build a matrix which rotates around the Y axis
//Matrix MatrixRotationY(Vector angle);
//
//*************************************************************************************************
// Build a matrix which rotates around the Z axis 
//*************************************************************************************************
Matrix MatrixRotationZ(float angle)
{
	// Load sin and cos
	SFLOAT sin = sinf(angle);
	SFLOAT cos = cosf(angle);

	Vector vSin = _mm_set_ss(sin);
	Vector vCos = _mm_set_ss(cos);

	// Load first and second rows
	vSin = _mm_unpacklo_ps(vSin, vCos);
	vCos = _mm_shuffle_ps(vSin, vSin, _MM_SHUFFLE(3, 3, 0, 1));
	vCos = _mm_mul_ps(vCos, gVNegateX);

	// Construct matrix
	Matrix m;
	m.r[0] = vSin;
	m.r[1] = vCos;
	m.r[2] = gVIdentityR2;
	m.r[3] = gVIdentityR3;
	return m;
}

////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build a matrix which rotates around the Z axis
//Matrix MatrixRotationZ(Vector angle);
//
////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build a matrix which rotates around an arbitrary axis
//Matrix MatrixRotationAxis(const Vector v, float angle);
//
////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build a matrix which rotates around an arbitrary axis
//Matrix MatrixRotationAxis(const Vector v, Vector angle);
//
////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build a matrix from a quaternion
//Matrix MatrixRotationQuaternion(const Vector q);
//
////*************************************************************************************************
//// 
////*************************************************************************************************
//// Yaw around the Y axis, a pitch around the X axis, and a roll around the Z axis
//Matrix MatrixRotationYawPitchRoll(float yaw, float pitch, float roll);
//
////*************************************************************************************************
//// 
////*************************************************************************************************
//// Yaw around the Y axis, a pitch around the X axis, and a roll around the Z axis
//Matrix MatrixRotationYawPitchRoll(Vector yaw, Vector pitch, Vector roll);
//
////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build transformation matrix with null arguments being treated as identity. 
//// Mout = Msc-1 * Msr-1 * Ms * Msr * Msc * Mrc-1 * Mr * Mrc * Mt
//Matrix MatrixTransformation(const Vector scalingCenter, const Vector scalingRotation, 
//	const Vector scaling, const Vector& rotationCenter, const Vector& rotation, const Vector& translation);
//
////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build 2D transformation matrix in XY plane. Null arguments treated as identity. Mout = Msc-1 * Msr-1 * Ms * Msr * Msc * Mrc-1 * Mr * Mrc * Mt
//Matrix MatrixTransformation2D(const Vector scalingCenter, float scalingRotation, const Vector scaling,
//	const Vector rotationCenter, float rotation, const Vector& translation);
//
////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build 2D transformation matrix in XY plane. Null arguments treated as identity. Mout = Msc-1 * Msr-1 * Ms * Msr * Msc * Mrc-1 * Mr * Mrc * Mt
//Matrix MatrixTransformation2D(const Vector scalingCenter, const Vector scalingRotation, const Vector scaling,
//	const Vector& rotationCenter, const Vector& rotation, const Vector& translation);
//
////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build affine transformation matrix. Null arguments treated as identity. Mout = Ms * Mrc-1 * Mr * Mrc * Mt
//Matrix MatrixAffineTransformation(float scaling, const Vector rotationCenter, const Vector rotation, 
//	const Vector translation);
//
////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build affine transformation matrix. Null arguments treated as identity. Mout = Ms * Mrc-1 * Mr * Mrc * Mt
//Matrix MatrixAffineTransformation(const Vector scaling, const Vector rotationCenter, const Vector rotation, 
//	const Vector& translation);
//
////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build 2D affine transformation matrix in XY plane. Null arguments treated as identity. Mout = Ms * Mrc-1 * Mr * Mrc * Mt
//Matrix MatrixAffineTransformation2D(float scaling, const Vector rotationCenter, float rotation, const Vector translation);
//
////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build 2D affine transformation matrix in XY plane. Null arguments treated as identity. Mout = Ms * Mrc-1 * Mr * Mrc * Mt
//Matrix MatrixAffineTransformation2D(const Vector scaling, const Vector rotationCenter, 
//	const Vector rotation, const Vector& translation);
//
////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build a lookat matrix (right-handed)
//Matrix MatrixLookAtRH(const Vector eye, const Vector at, const Vector up);
//
//*************************************************************************************************
// Build a lookat matrix (left-handed)
//
// Construct z axis
// zAxis = Vec3Sub(at, eye)
// zAxis = Vec3Normalize(zAxis)
//
// Construct x axis
// xAxis = Vec3Cross(up, zAxis)
// xAxis = Vec3Normalize(xAxis)
//
// Construct y axis
// yAxis = Vec3Cross(zAxis, xAxis)
//
// Splat x and y axes
// vTemp1 = _mm_shuffle_ps(xAxis, yAxis, _MM_SHUFFLE(1, 0, 1, 0)) -> x.x x.y y.x y.y
// vTemp2 = _mm_shuffle_ps(xAxis, yAxis, _MM_SHUFFLE(3, 2, 3, 2)) -> x.z x.w y.z y.w
//
// Splat z axis
// vTemp3 = _mm_shuffle_ps(zAxis, gVZero, _MM_SHUFFLE(1, 0, 1, 0)) -> z.x z.y 0 0
// vTemp4 = _mm_shuffle_ps(zAxis, gVZero, _MM_SHUFFLE(3, 2, 3, 2)) -> z.z z.w 0 0
//
// Construct R0
// r1 = _mm_shuffle_ps(vTemp1, vTemp3, _MM_SHUFFLE(3, 0, 2, 0));
//
// Construct R1
// r2 = _mm_shuffle_ps(vTemp1, vTemp3, _MM_SHUFFLE(3, 1, 3, 1));
//
// Construct R2
// r3 = _mm_shuffle_ps(vTemp2, vTemp4, _MM_SHUFFLE(3, 0, 2, 0))
//
// Construct R3
// vTemp1 = Vec3Dot(xAxis, eye)
// vTemp1 = Vec3Mul(gVNegOne, vTemp1)
// vTemp2 = Vec3Dot(yAxis, eye)
// vTemp2 = Vec3Mul(gVNegOne, vTemp2)
// vTemp3 = Vec3Dot(zAxis, eye)
// vTemp3 = Vec3Mul(gVNegOne, vTemp3)
//
// vTemp1 = _mm_unpacklo_ps(vTemp1, vTemp2)
// vTemp2 = _mm_unpacklo_ps(vTemp3, gVOne)
// r4 = _mm_unpacklo_ps(vTemp1, vTemp2)
//*************************************************************************************************
Matrix MatrixLookAtLH(const Vector eye, const Vector at, const Vector up)
{
	// Construct z axis
	Vector zAxis = Vec3Sub(at, eye);
	Vector l = Vec3Length(zAxis);
	zAxis = Vec3Normalize(zAxis);
	Vector l2 = Vec3Length(zAxis);

	// Construct x axis
	Vector xAxis = Vec3Cross(up, zAxis);
	Vector l3 = Vec3Length(xAxis);
	xAxis = Vec3Normalize(xAxis);
	Vector l4 = Vec3Length(xAxis);

	// Construct y axis
	Vector yAxis = Vec3Cross(zAxis, xAxis);
	Vector l5 = Vec3Length(yAxis);

	// Splat x and y axes
	Vector vTemp1 = _mm_shuffle_ps(xAxis, yAxis, _MM_SHUFFLE(1, 0, 1, 0));
	Vector vTemp2 = _mm_shuffle_ps(xAxis, yAxis, _MM_SHUFFLE(3, 2, 3, 2));

	// Splat z axis
	Vector vTemp3 = _mm_shuffle_ps(zAxis, gVZero, _MM_SHUFFLE(1, 0, 1, 0));
	Vector vTemp4 = _mm_shuffle_ps(zAxis, gVZero, _MM_SHUFFLE(3, 2, 3, 2));

	// Construct the matix
	Matrix m;

	// R0
	m.r[0] = _mm_shuffle_ps(vTemp1, vTemp3, _MM_SHUFFLE(3, 0, 2, 0));

	// R1
	m.r[1] = _mm_shuffle_ps(vTemp1, vTemp3, _MM_SHUFFLE(3, 1, 3, 1));

	// R2
	m.r[2] = _mm_shuffle_ps(vTemp2, vTemp4, _MM_SHUFFLE(3, 0, 2, 0));

	// R3
	vTemp1 = Vec3Dot(xAxis, eye);
	vTemp1 = Vec3Scale(vTemp1, gVNegOne);
	vTemp2 = Vec3Dot(yAxis, eye);
	vTemp2 = Vec3Scale(vTemp2, gVNegOne);
	vTemp3 = Vec3Dot(zAxis, eye);
	vTemp3 = Vec3Scale(vTemp3, gVNegOne);

	vTemp1 = _mm_unpacklo_ps(vTemp1, vTemp3);
	vTemp3 = _mm_unpacklo_ps(vTemp2, gVOne);
	m.r[3] = _mm_unpacklo_ps(vTemp1, vTemp3);

	return m;
}

////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build a perspective projection matrix (right-handed)
//Matrix MatrixPerspectiveRH(float w, float h, float zn, float zf);
//
////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build a perspective projection matrix (right-handed)
//Matrix MatrixPerspectiveRH(const Vector w, const Vector h, const Vector zn, const Vector& zf);
//
////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build a perspective projection matrix (left-handed)
//Matrix MatrixPerspectiveLH(float w, float h, float zn, float zf);
//
////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build a perspective projection matrix (left-handed)
//Matrix MatrixPerspectiveLH(const Vector w, const Vector h, const Vector zn, const Vector& zf);
//
////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build a perspective projection matrix (right-handed)
//Matrix MatrixPerspectiveFovRH(float fovy, float aspect, float zn, float zf);
//
////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build a perspective projection matrix (right-handed)
//Matrix MatrixPerspectiveFovRH(const Vector fovy, const Vector aspect, const Vector zn, const Vector& zf);
//
//*************************************************************************************************
// Build a perspective projection matrix (left-handed)
// 
// [cot(fovy/2)/aspect 0 0 0]
// [0 cot(fovy/2) 0 0]
// [0 0 (f)/(f-n) (nf)/(n-f)]
// [0 0 -1 0]
//*************************************************************************************************
Matrix MatrixPerspectiveFovLH(float fovy, float aspect, float zn, float zf)
{
	Vector vFovy = VectorReplicate(fovy);
	Vector vAspect = VectorReplicate(aspect);
	Vector vZn = VectorReplicate(zn);
	Vector vZf = VectorReplicate(zf);

	return MatrixPerspectiveFovLH(vFovy, vAspect, vZn, vZf);
}

//*************************************************************************************************
// Build a perspective projection matrix (left-handed) 
// 
// [cot(fovy/2)/aspect 0 0 0]
// [0 cot(fovy/2) 0 0]
// [0 0 (f)/(f-n) (nf)/(n-f)]
// [0 0 -1 0]
// 
// cot = cos/sin
//*************************************************************************************************
Matrix MatrixPerspectiveFovLH(const Vector fovy, const Vector aspect, const Vector zn, const Vector& zf)
{
	// Find fovy/2
	Vector fovy2 = VectorMul(fovy, gVOneHalf);

	// Find cot
	Vector sin, cos;
	VectorSinCos(&sin, &cos, fovy2);
	Vector cot = VectorDiv(cos, sin);
	fovy2 = VectorDiv(cot, aspect);

	// Matrix constructor
	Matrix m;

	// Construct the first row
	m.r[0] = _mm_move_ss(gVZero, fovy2);

	// Construct the second row
	m.r[1] = _mm_and_ps(gVYMask, cot);

	// Construct third row
	Vector range = VectorSub(zf, zn);
	range = VectorDiv(zf, range);
	Vector vTemp = _mm_and_ps(gVWMask, range);
	m.r[2] = _mm_unpackhi_ps(vTemp, gVIdentityR3);//, vTemp);

	/*vTemp1 = _mm_and_ps(gVYMask, vTemp1);
	range = VectorMul(gVNegOne, range);
	Vector vTemp2 = VectorMul(zn, zf);
	vTemp2 = VectorDiv(vTemp2, range);
	vTemp2 =  _mm_and_ps(gVYMask, vTemp2);
	m.r[2] = _mm_unpacklo_ps(vTemp1, vTemp2);*/

	// Construct fourth row	
	range = VectorMul(gVNegOne, range);
	range = VectorMul(range, zn);
	m.r[3] = _mm_and_ps(gVZMask, range);	

	return m;
}

////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build a matrix which flattens geometry into a plane, as if casting a shadow from a light
//Matrix MatrixShadow(const Vector light, const Vector plane);
//
////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build a matrix which reflects the coordinate system about a plane
//Matrix MatrixReflect(const Vector plane);
//
////*************************************************************************************************
//// 
////*************************************************************************************************
//// Creates a tensor product of given two 3D vectors
//Matrix MatrixTensorProduct(const Vector v1, const Vector v2);
