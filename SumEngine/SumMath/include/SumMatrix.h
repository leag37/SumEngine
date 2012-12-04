//*************************************************************************************************
// Title: SumMatrix.h
// Author: Gael Huber
// Description: Matrix math functions.
//*************************************************************************************************
#ifndef __SUMMATRIX_H__
#define __SUMMATRIX_H__

#include "SumMath.h"

//-----------------------------------------------
// 4D Matrix
//-----------------------------------------------

// Identity
Matrix MatrixIdentity();

// Is identity
bool MatrixIsIdentity(const Matrix& m);

// Sum of two matrices
Matrix MatrixAdd(const Matrix& m1, const Matrix& m2);

// Difference between two matrices
Matrix MatrixSub(const Matrix& m1, const Matrix& m2);

// Scale a matrix
Matrix MatrixScale(const Matrix& m, SFLOAT s);

// Scale a matrix
Matrix MatrixScale(const Matrix& m, const Vector s);

extern "C++"
{
// Determinant
Vector MatrixDeterminant(const Matrix& m);

// Decompose
SBOOL MatrixDecompose(Vector* pOutScale, Vector* pOutRotation, Vector* pOutTranslation, const Matrix& m);

// Transpose
Matrix MatrixTranspose(const Matrix& m);

// Multiply
Matrix MatrixMultiply(const Matrix& m1, const Matrix& m2);

// Multiply, followed by a transpose T(M1 * M2)
Matrix MatrixMultiplyTranspose(const Matrix& m1, const Matrix& m2);

// Inverse
Matrix MatrixInverse(Vector* pDeterminant, const Matrix& m);

// Build a matrix which scales by (sx, sy, sz)
Matrix MatrixScaling(float sx, float sy, float sz);

// Build a matrix which scales by (sx, sy, sz)
Matrix MatrixScaling(Vector sx, Vector sy, Vector sz);

// Build a matrix which tranlates by (x, y, z)
Matrix MatrixTranslation(float x, float y, float z);

// Build a matrix which tranlates by (x, y, z)
Matrix MatrixTranslation(Vector x, Vector y, Vector z);

// Build a matrix which rotates around the X axis
Matrix MatrixRotationX(float angle);

// Build a matrix which rotates around the X axis
Matrix MatrixRotationX(Vector angle);

// Build a matrix which rotates around the Y axis
Matrix MatrixRotationY(float angle);

// Build a matrix which rotates around the Y axis
Matrix MatrixRotationY(Vector angle);

// Build a matrix which rotates around the Z axis
Matrix MatrixRotationZ(float angle);

// Build a matrix which rotates around the Z axis
Matrix MatrixRotationZ(Vector angle);

// Build a matrix which rotates around an arbitrary axis
Matrix MatrixRotationAxis(const Vector v, float angle);

// Build a matrix which rotates around an arbitrary axis
Matrix MatrixRotationAxis(const Vector v, Vector angle);

// Build a matrix from a quaternion
Matrix MatrixRotationQuaternion(const Vector q);

// Yaw around the Y axis, a pitch around the X axis, and a roll around the Z axis
Matrix MatrixRotationYawPitchRoll(float yaw, float pitch, float roll);

// Yaw around the Y axis, a pitch around the X axis, and a roll around the Z axis
Matrix MatrixRotationYawPitchRoll(Vector yaw, Vector pitch, Vector roll);

// Build transformation matrix with null arguments being treated as identity. 
// Mout = Msc-1 * Msr-1 * Ms * Msr * Msc * Mrc-1 * Mr * Mrc * Mt
Matrix MatrixTransformation(const Vector scalingCenter, const Vector scalingRotation, 
	const Vector scaling, const Vector& rotationCenter, const Vector& rotation, const Vector& translation);

// Build 2D transformation matrix in XY plane. Null arguments treated as identity. Mout = Msc-1 * Msr-1 * Ms * Msr * Msc * Mrc-1 * Mr * Mrc * Mt
Matrix MatrixTransformation2D(const Vector scalingCenter, float scalingRotation, const Vector scaling,
	const Vector& rotationCenter, float rotation, const Vector& translation);

// Build 2D transformation matrix in XY plane. Null arguments treated as identity. Mout = Msc-1 * Msr-1 * Ms * Msr * Msc * Mrc-1 * Mr * Mrc * Mt
Matrix MatrixTransformation2D(const Vector scalingCenter, const Vector scalingRotation, const Vector scaling,
	const Vector& rotationCenter, const Vector& rotation, const Vector& translation);

// Build affine transformation matrix. Null arguments treated as identity. Mout = Ms * Mrc-1 * Mr * Mrc * Mt
Matrix MatrixAffineTransformation(float scaling, const Vector rotationCenter, const Vector rotation, 
	const Vector translation);

// Build affine transformation matrix. Null arguments treated as identity. Mout = Ms * Mrc-1 * Mr * Mrc * Mt
Matrix MatrixAffineTransformation(const Vector scaling, const Vector rotationCenter, const Vector rotation, 
	const Vector& translation);

// Build 2D affine transformation matrix in XY plane. Null arguments treated as identity. Mout = Ms * Mrc-1 * Mr * Mrc * Mt
Matrix MatrixAffineTransformation2D(float scaling, const Vector rotationCenter, float rotation, const Vector translation);

// Build 2D affine transformation matrix in XY plane. Null arguments treated as identity. Mout = Ms * Mrc-1 * Mr * Mrc * Mt
Matrix MatrixAffineTransformation2D(const Vector scaling, const Vector rotationCenter, 
	const Vector rotation, const Vector& translation);

// Build a lookat matrix (right-handed)
Matrix MatrixLookAtRH(const Vector eye, const Vector at, const Vector up);

// Build a lookat matrix (left-handed)
Matrix MatrixLookAtLH(const Vector eye, const Vector at, const Vector up);

// Build a perspective projection matrix (right-handed)
Matrix MatrixPerspectiveRH(float w, float h, float zn, float zf);

// Build a perspective projection matrix (right-handed)
Matrix MatrixPerspectiveRH(const Vector w, const Vector h, const Vector zn, const Vector& zf);

// Build a perspective projection matrix (left-handed)
Matrix MatrixPerspectiveLH(float w, float h, float zn, float zf);

// Build a perspective projection matrix (left-handed)
Matrix MatrixPerspectiveLH(const Vector w, const Vector h, const Vector zn, const Vector& zf);

// Build a perspective projection matrix (right-handed)
Matrix MatrixPerspectiveFovRH(float fovy, float aspect, float zn, float zf);

// Build a perspective projection matrix (right-handed)
Matrix MatrixPerspectiveFovRH(const Vector fovy, const Vector aspect, const Vector zn, const Vector& zf);

// Build a perspective projection matrix (left-handed)
Matrix MatrixPerspectiveFovLH(float fovy, float aspect, float zn, float zf);

// Build a perspective projection matrix (left-handed)
Matrix MatrixPerspectiveFovLH(const Vector fovy, const Vector aspect, const Vector zn, const Vector& zf);

// Build a matrix which flattens geometry into a plane, as if casting a shadow from a light
Matrix MatrixShadow(const Vector light, const Vector plane);

// Build a matrix which reflects the coordinate system about a plane
Matrix MatrixReflect(const Vector plane);

// Creates a tensor product of given two 3D vectors
Matrix MatrixTensorProduct(const Vector v1, const Vector v2);
}

#include "SumMatrix.inl"

#endif