
#include "SumMath.h"

//*************************************************************************************************
// Hermite interpolation between position V1, tangent T1 (when s == 0) and position V2, tangent T2 
// (when s == 1).
//
// Solve for a*v1 + b*v2 + c*t1 + d*t2
// a = 2s^3 - 3s^2 + 1
// b = -2s^3 + 3s^2
// c = s^3 - 2s^2 + s
// d = s^3 - s^2
//*************************************************************************************************
Vector Vec3Hermite(const Vector v1, const Vector t1, const Vector v2, const Vector& t2, float s)
{
	Vector vS = _mm_set1_ps(s);
	return Vec3Hermite(v1, t1, v2, t2, vS);
}

//*************************************************************************************************
// Hermite interpolation between position V1, tangent T1 (when s == 0) and position V2, tangent T2 
// (when s == 1).
//
// Solve for a*v1 + b*v2 + c*t1 + d*t2
// a = 2s^3 - 3s^2 + 1
// b = -2s^3 + 3s^2
// c = s^3 - 2s^2 + s
// d = s^3 - s^2
//*************************************************************************************************
Vector Vec3Hermite(const Vector v1, const Vector t1, const Vector v2, const Vector& t2, Vector& s)
{
	// Find double and triple of s
	Vector vS2 = _mm_mul_ps(s, s);
	Vector vS3 = _mm_mul_ps(s, vS2);

	// Calculate a, b, c, and d for the forumula
	// a = 2s^3 - 3s^2 + 1
	// b = -2s^3 + 3s^2
	// c = s^3 - 2s^2 + s
	// d = s^3 - s^2
	//----------------------------------------------

	// A
	Vector vTemp1 = _mm_mul_ps(_mm_set1_ps(2.0f), vS3);
	Vector vTemp2 = _mm_mul_ps(_mm_set1_ps(-3.0f), vS2);
	Vector vA = _mm_add_ps(vTemp1, vTemp2);
	vA = _mm_add_ps(_mm_set1_ps(1.0f), vA);

	// B
	vTemp1 = _mm_mul_ps(_mm_set1_ps(-2.0f), vS3);
	vTemp2 = _mm_mul_ps(_mm_set1_ps(3.0f), vS2);
	Vector vB = _mm_add_ps(vTemp1, vTemp2);
	
	// C
	vTemp1 = _mm_mul_ps(_mm_set1_ps(-2.0f), vS2);
	Vector vC = _mm_add_ps(vS3, vTemp1);
	vC = _mm_add_ps(vC, s);

	// D
	Vector vD = _mm_sub_ps(vS3, vS2);

	// Solve for a*v1 + b*v2 + c*t1 + d*t2
	vTemp1 = _mm_mul_ps(vA, v1);
	vTemp2 = _mm_mul_ps(vB, v2);
	Vector vResult = _mm_add_ps(vTemp1, vTemp2);

	vTemp1 = _mm_mul_ps(vC, t1);
	vTemp2 = _mm_mul_ps(vD, t2);
	vResult = _mm_add_ps(vResult, vTemp1);
	vResult = _mm_add_ps(vResult, vTemp2);

	return vResult;
}

//*************************************************************************************************
// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
//
// Calculate a, b, c, and d
// a = -s^3 + 2s^2 - s
// b = 3s^3 - 5s^2 + 2
// c = -3s^3 + 4s^2 + s
// d = s^3 - s^2
// 
// Solve for (a*p1 + b*p2 + c*p3 + d*p4)/2
//*************************************************************************************************
Vector Vec3CatmullRom(const Vector v0, const Vector v1, const Vector v2, const Vector& v3, float s)
{
	Vector vS = _mm_set1_ps(s);
	return Vec3CatmullRom(v0, v1, v2, v3, vS);
}

//*************************************************************************************************
// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
//
// Calculate a, b, c, and d
// a = -s^3 + 2s^2 - s
// b = 3s^3 - 5s^2 + 2
// c = -3s^3 + 4s^2 + s
// d = s^3 - s^2
// 
// Solve for (a*p1 + b*p2 + c*p3 + d*p4)/2
//*************************************************************************************************
Vector Vec3CatmullRom(const Vector v0, const Vector v1, const Vector v2, const Vector& v3, const Vector& s)
{
		// Calculate s^2 and s^3
	Vector vS2 = _mm_mul_ps(s, s);
	Vector vS3 = _mm_mul_ps(vS2, s);

	// Calculate a, b, c, and d
	// a = -s^3 + 2s^2 - s
	// b = 3s^3 - 5s^2 + 2
	// c = -3s^3 + 4s^2 + s
	// d = s^3 - s^2

	// A
	Vector vTemp1 = _mm_mul_ps(_mm_set1_ps(-1.0f), vS3);
	Vector vTemp2 = _mm_mul_ps(_mm_set1_ps(2.0f), vS2);
	Vector vA = _mm_add_ps(vTemp1, vTemp2);
	vA = _mm_sub_ps(vA, s);

	// B
	vTemp1 = _mm_mul_ps(_mm_set1_ps(3.0f), vS3);
	vTemp2 = _mm_mul_ps(_mm_set1_ps(-5.0f), vS2);
	Vector vB = _mm_add_ps(vTemp1, vTemp2);
	vB = _mm_add_ps(_mm_set1_ps(2.0f), vB);

	// C
	vTemp1 = _mm_mul_ps(_mm_set1_ps(-3.0f), vS3);
	vTemp2 = _mm_mul_ps(_mm_set1_ps(4.0f), vS2);
	Vector vC = _mm_add_ps(vTemp1, vTemp2);
	vC = _mm_add_ps(vC, s);

	// D
	Vector vD = _mm_sub_ps(vS3, vS2);

	// Solve for (a*p1 + b*p2 + c*p3 + d*p4)/2
	vTemp1 = _mm_mul_ps(vA, v0);
	vTemp2 = _mm_mul_ps(vB, v1);
	Vector vResult = _mm_add_ps(vTemp1, vTemp2);
	vTemp1 = _mm_mul_ps(vC, v2);
	vTemp2 = _mm_mul_ps(vD, v3);
	vResult = _mm_add_ps(vTemp1, vResult);
	vResult = _mm_add_ps(vTemp2, vResult);
	vResult = _mm_mul_ps(vResult, _mm_set1_ps(0.5f));

	return vResult;
}

//*************************************************************************************************
// Barycentric V1 + f(V2 - V1) + g(V3 - V1) 
//*************************************************************************************************
Vector Vec3Barycentric(const Vector v1, const Vector v2, const Vector v3, float f, float g)
{
	Vector vF = _mm_set1_ps(f);
	Vector vG = _mm_set1_ps(g);
	return Vec3Barycentric(v1, v2, v3, vF, vG);
}

//*************************************************************************************************
// Barycentric V1 + f(V2 - V1) + g(V3 - V1) 
//*************************************************************************************************
Vector Vec3Barycentric(const Vector v1, const Vector v2, const Vector v3, const Vector& f, const Vector& g)
{
	// Differences
	Vector vTemp1 = _mm_sub_ps(v2, v1);
	Vector vTemp2 = _mm_sub_ps(v3, v1);
	
	// Multiply by constants
	vTemp1 = _mm_mul_ps(f, vTemp1);
	vTemp2 = _mm_mul_ps(g, vTemp2);

	// Add
	vTemp1 = _mm_add_ps(v1, vTemp1);
	return _mm_add_ps(vTemp1, vTemp2);
}

//*************************************************************************************************
// Transform by matrix (x, y, z, 1)
//*************************************************************************************************
Vector Vec3Transform(const Vector v, const Matrix& m)
{
	// X
	Vector vTemp = _mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 0, 0, 0));
	Vector vResult = _mm_mul_ps(vTemp, m.r[0]);

	// Y
	vTemp = _mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 1, 1, 1));
	vTemp = _mm_mul_ps(vTemp, m.r[1]);
	vResult = _mm_add_ps(vResult, vTemp);

	// Z
	vTemp = _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 2, 2, 2));
	vTemp = _mm_mul_ps(vTemp, m.r[2]);
	vResult = _mm_add_ps(vResult, vTemp);
	return _mm_add_ps(vResult, m.r[3]);
}

//*************************************************************************************************
// Transform by matrix and project back to w = 1 (x, y, z, 1)
//*************************************************************************************************
Vector Vec3TransformCoord(const Vector v, const Matrix& m)
{
	// X
	Vector vTemp = _mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 0, 0, 0));
	Vector vResult = _mm_mul_ps(vTemp, m.r[0]);

	// Y
	vTemp = _mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 1, 1, 1));
	vTemp = _mm_mul_ps(vTemp, m.r[1]);
	vResult = _mm_add_ps(vResult, vTemp);

	// Z
	vTemp = _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 2, 2, 2));
	vTemp = _mm_mul_ps(vTemp, m.r[2]);
	vResult = _mm_add_ps(vResult, vTemp);
	vResult = _mm_add_ps(vResult, m.r[3]);

	vTemp = _mm_shuffle_ps(vResult, vResult, _MM_SHUFFLE(3, 3, 3, 3));
	return _mm_div_ps(vResult, vTemp);
}

//*************************************************************************************************
// Transform normal by matix (x, y, z, 0) 
//*************************************************************************************************
Vector Vec3TransformNormal(const Vector v, const Matrix& m)
{
	// X
	Vector vTemp = _mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 0, 0, 0));
	Vector vResult = _mm_mul_ps(vTemp, m.r[0]);

	// Y
	vTemp = _mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 1, 1, 1));
	vTemp = _mm_mul_ps(vTemp, m.r[1]);
	vResult = _mm_add_ps(vResult, vTemp);

	// Z
	vTemp = _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 2, 2, 2));
	vTemp = _mm_mul_ps(vTemp, m.r[2]);
	return _mm_add_ps(vResult, vTemp);
}

// Project from object space into screen space
Vector Vec3Project(const Vector v, SFLOAT viewportX, SFLOAT viewportY, SFLOAT viewportWidth, 
	SFLOAT viewportHeight, SFLOAT viewportMinZ, SFLOAT viewportMaxZ, 
	const Matrix& projection, const Matrix& view, const Matrix& world)
{
	// Create the scale and offset vectors
	SFLOAT vpHalfWidth = viewportWidth * 0.5f;
	SFLOAT vpHalfHeight = viewportHeight * 0.5f;
	Vector scale = VectorSet(vpHalfWidth, vpHalfHeight, viewportMaxZ - viewportMinZ, 0.0f);
	Vector offset = VectorSet(viewportX + vpHalfWidth, viewportY + vpHalfHeight, viewportMinZ, 0.0f);

	// Construct transform matrix
	Matrix transform = MatrixMultiply(world, view);
	transform = MatrixMultiply(transform, projection);

	// Transform the coordinate
	Vector result = Vec3TransformCoord(v, transform);

	// Scale the coordinate to the viewport and offset it appropriately so it appears at the right location
	result = _mm_mul_ps(result, scale);
	return _mm_add_ps(result, offset);
}

//*************************************************************************************************
// Project from screen space into object space 
//*************************************************************************************************
Vector Vec3Unproject(const Vector v, SFLOAT viewportX, SFLOAT viewportY, SFLOAT viewportWidth,
	SFLOAT viewportHeight, SFLOAT viewportMinZ, SFLOAT viewportMaxZ,
	const Matrix& projection, const Matrix& view, const Matrix& world)
{
	// Create the scale and offset vectors
	SFLOAT vpHalfWidth = viewportWidth * 0.5f;
	SFLOAT vpHalfHeight = viewportHeight * 0.5f;
	Vector scale = VectorSet(vpHalfWidth, vpHalfHeight, viewportMaxZ - viewportMinZ, 0.0f);
	Vector offset = VectorSet(viewportX + vpHalfWidth, viewportY + vpHalfHeight, viewportMinZ, 0.0f);

	// Shift vectors
	Vector result = _mm_sub_ps(v, offset);
	
	// Anti-scale
	result = _mm_div_ps(result, scale);

	// Get the transform matrix
	Vector determinant;
	Matrix transform = MatrixMultiply(world, view);
	transform = MatrixMultiply(transform, projection);
	transform = MatrixInverse(&determinant, transform);

	// Reverse the transformation
	return Vec3TransformCoord(result, transform);
}
