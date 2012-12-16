//*************************************************************************************************
// Title: SumVector4.cpp
// Author: Gael Huber
// Description: Vector 4 mathematics.
//*************************************************************************************************
#include "SumVector4.h"

//*************************************************************************************************
// Cross
//
// x = (v1.y[v2.z*v3.w - v2.w*v3.z] - v1.z[v2.y*v3.w - v2.w*v3.y] + v1.w[v2.y*v3.z - v2.z*v3.y])
// y = (v1.x[v2.w*v3.z - v2.z*v3.w] - v1.z[v2.w*v3.x - v2.x*v3.w] + v1.w[v2.z*v3.x - v2.x*v3.z])
// z = (v1.x[v2.y*v3.w - v2.w*v3.y] - v1.y[v2.x*v3.w - v2.w*v3.x] + v1.w[v2.x*v3.y - v2.y*v3.x])
// w = (v1.x[v2.z*v3.y - v2.y*v3.z] - v1.y[v2.z*v3.x - v2.x*v3.z] + v1.z[v2.y*v3.x - v2.x*v3.y])
//*************************************************************************************************
Vector Vec4Cross(const Vector v1, const Vector v2, const Vector v3)
{
	// Set 1
	// v1.y[v2.z*v3.w - v2.w*v3.z]
	// v1.x[v2.w*v3.z - v2.z*v3.w]
	// v1.x[v2.y*v3.w - v2.w*v3.y]
	// v1.x[v2.z*v3.y - v2.y*v3.z]
	Vector vTemp1 = _mm_shuffle_ps(v2, v2, _MM_SHUFFLE(2, 1, 3, 2));
	Vector vTemp2 = _mm_shuffle_ps(v3, v3, _MM_SHUFFLE(1, 3, 2, 3));
	Vector vResult = _mm_mul_ps(vTemp1, vTemp1);

	vTemp1 = _mm_shuffle_ps(v2, v2, _MM_SHUFFLE(1, 3, 2, 3));
	vTemp2 = _mm_shuffle_ps(v3, v3, _MM_SHUFFLE(2, 1, 3, 2));
	vTemp1 = _mm_mul_ps(vTemp1, vTemp2);
	vResult = _mm_sub_ps(vResult, vTemp1);

	vTemp1 = _mm_shuffle_ps(v1, v1, _MM_SHUFFLE(0, 0, 0, 1));
	vResult = _mm_mul_ps(vResult, vTemp1);

	// Set 2
	// v1.z[v2.y*v3.w - v2.w*v3.y]
	// v1.z[v2.w*v3.x - v2.x*v3.w]
	// v1.y[v2.x*v3.w - v2.w*v3.x]
	// v1.y[v2.z*v3.x - v2.x*v3.z]
	vTemp1 = _mm_shuffle_ps(v2, v2, _MM_SHUFFLE(2, 0, 3, 1));
	vTemp2 = _mm_shuffle_ps(v3, v3, _MM_SHUFFLE(0, 3, 0, 3));
	Vector vTemp3 = _mm_mul_ps(vTemp1, vTemp2);
	
	vTemp1 = _mm_shuffle_ps(v2, v2, _MM_SHUFFLE(0, 3, 0, 3));
	vTemp2 = _mm_shuffle_ps(v3, v3, _MM_SHUFFLE(2, 0, 3, 1));
	vTemp1 = _mm_mul_ps(vTemp1, vTemp2);

	vTemp3 = _mm_sub_ps(vTemp3, vTemp1);

	vTemp1 = _mm_shuffle_ps(v1, v1, _MM_SHUFFLE(1, 1, 2, 2));
	vTemp3 = _mm_mul_ps(vTemp1, vTemp3);
	vResult = _mm_sub_ps(vResult, vTemp3);

	// Set 3
	// v1.w[v2.y*v3.z - v2.z*v3.y])
	// v1.w[v2.z*v3.x - v2.x*v3.z])
	// v1.w[v2.x*v3.y - v2.y*v3.x])
	// v1.z[v2.y*v3.x - v2.x*v3.y])
	vTemp1 = _mm_shuffle_ps(v2, v2, _MM_SHUFFLE(1, 0, 2, 1));
	vTemp2 = _mm_shuffle_ps(v3, v3, _MM_SHUFFLE(0, 1, 0, 2));
	vTemp3 = _mm_mul_ps(vTemp1, vTemp2);

	vTemp1 = _mm_shuffle_ps(v2, v2, _MM_SHUFFLE(0, 1, 0, 2));
	vTemp2 = _mm_shuffle_ps(v3, v3, _MM_SHUFFLE(1, 0, 2, 1));
	vTemp1 = _mm_mul_ps(vTemp1, vTemp2);
	
	vTemp3 = _mm_sub_ps(vTemp3, vTemp1);

	vTemp1 = _mm_shuffle_ps(v1, v1, _MM_SHUFFLE(2, 3, 3, 3));
	vTemp3 = _mm_mul_ps(vTemp3, vTemp1);

	return _mm_add_ps(vResult, vTemp3);
}

//*************************************************************************************************
// Normalize
//*************************************************************************************************
Vector Vec4Normalize(const Vector v)
{
	// Find length
	Vector vLength = _mm_mul_ps(v, v);

	// Splat y and w
	Vector vTemp = _mm_shuffle_ps(vLength, vLength, _MM_SHUFFLE(3, 3, 1, 1));

	// x+y && z+w
	vLength = _mm_add_ps(vLength, vTemp);

	// Splat z+w
	vTemp = _mm_shuffle_ps(vLength, vLength, _MM_SHUFFLE(2, 2, 2, 2));

	// Full dot product
	vLength = _mm_add_ps(vLength, vTemp);

	// Splat result
	vLength = _mm_shuffle_ps(vLength, vLength, _MM_SHUFFLE(0, 0, 0, 0));

	// Return normalized vector
	return _mm_div_ps(v, vLength);
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
Vector Vec4Hermite(const Vector v1, const Vector t1, const Vector v2, const Vector& t2, float s)
{
	Vector vS = _mm_set1_ps(s);
	return Vec4Hermite(v1, t1, v2, t2, vS);
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
Vector Vec4Hermite(const Vector v1, const Vector t1, const Vector v2, const Vector& t2, const Vector& s)
{
	// Find s^2 and s^3
	Vector vS2 = _mm_mul_ps(s, s);
	Vector vS3 = _mm_mul_ps(s, vS2);

	// Set constants
	Vector vTemp1 = _mm_set_ps(2.0f, -2.0f, 1.0f, 1.0f);
	vS3 = _mm_mul_ps(vTemp1, vS3);

	vTemp1 = _mm_set_ps(-3.0f, 3.0f, -2.0f, -1.0f);
	vS2 = _mm_mul_ps(vTemp1, vS2);

	vTemp1 = _mm_set_ps(1.0f, 0.0f, s.m128_f32[0], 0.0f);
	
	vTemp1 = _mm_add_ps(vTemp1, vS2);
	vTemp1 = _mm_add_ps(vTemp1, vS3);

	// Find products and sum of primary formula
	Vector vTemp2 = _mm_shuffle_ps(vTemp1, vTemp1, _MM_SHUFFLE(0, 0, 0, 0));
	Vector vResult = _mm_mul_ps(v1, vTemp2);

	vTemp2 = _mm_shuffle_ps(vTemp1, vTemp1, _MM_SHUFFLE(1, 1, 1, 1));
	vTemp2 = _mm_mul_ps(v2, vTemp2);
	vResult = _mm_add_ps(vResult, vTemp2);

	vTemp2 = _mm_shuffle_ps(vTemp1, vTemp1, _MM_SHUFFLE(2, 2, 2, 2));
	vTemp2 = _mm_mul_ps(t1, vTemp2);
	vResult = _mm_add_ps(vResult, vTemp2);

	vTemp2 = _mm_shuffle_ps(vTemp1, vTemp1, _MM_SHUFFLE(3, 3, 3, 3));
	vTemp2 = _mm_mul_ps(t2, vTemp2);
	return _mm_add_ps(vResult, vTemp2);
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
Vector Vec4CatmullRom(const Vector v0, const Vector v1,	const Vector v2, const Vector& v3, float s)
{
	Vector vS = _mm_set1_ps(s);
	return Vec4CatmullRom(v0, v1, v2, v3, vS);
}

//*************************************************************************************************
// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
//
// q(t) = 0.5 * (1.0f, t, t^2, t^3) * [0  2  0  0 ] [P0]
//									  [-1 0  1  0 ] [P1]
//									  [2  -5 4  -1] [P2]
//									  [-1 3  -3  1] [P3]
// 
// q(t) = 0.5 * ((2*P1) + t*(-P0 + P2) + t^2*(2*P0 - 5*P1 + 4*P2 - 1*P3) + 
//			t^3*(-1*P0 + 3*P1 - 3*P2 + P3))
//*************************************************************************************************
Vector Vec4CatmullRom(const Vector v0, const Vector v1,	const Vector v2, const Vector& v3, const Vector& s)
{
	// Multiplicative constants
	static const Vector cat2 = {2.0f, 2.0f, 2.0f, 2.0f};
	static const Vector cat3 = {3.0f, 3.0f, 3.0f, 3.0f};
	static const Vector cat4 = {4.0f, 4.0f, 4.0f, 4.0f};
	static const Vector cat5 = {5.0f, 5.0f, 5.0f, 5.0f};
	
	// Find s^2 and s^3
	Vector vS2 = _mm_mul_ps(s, s);
	Vector vS3 = _mm_mul_ps(vS2, s);

	// Calulate first phase - (2*P1)
	Vector vResult = _mm_mul_ps(v1, cat2);

	// Calculate second phase - t*(-P0 + P2)
	Vector vTemp1 = _mm_sub_ps(v2, v0);
	vTemp1 = _mm_mul_ps(s, vTemp1);
	vResult = _mm_add_ps(vTemp1, vResult);

	// Calculate third phase - t^2*(2*P0 - 5*P1 + 4*P2 - 1*P3)
	vTemp1 = _mm_mul_ps(cat2, v0);
	Vector vTemp2 = _mm_mul_ps(cat5, v1);
	vTemp1 = _mm_sub_ps(vTemp1, vTemp2);
	vTemp2 = _mm_mul_ps(cat4, v2);
	vTemp1 = _mm_add_ps(vTemp1, vTemp2);
	vTemp1 = _mm_sub_ps(vTemp1, v3);
	vTemp1 = _mm_mul_ps(vTemp1, vS2);
	vResult = _mm_add_ps(vTemp1, vResult);

	// Calculate fourth phase - t^3*(-1*P0 + 3*P1 - 3*P2 + P3))
	vTemp1 = _mm_mul_ps(cat3, v1);
	vTemp1 = _mm_sub_ps(vTemp1, v0);
	vTemp2 = _mm_mul_ps(cat3, v2);
	vTemp1 = _mm_sub_ps(vTemp1, vTemp2);
	vTemp1 = _mm_add_ps(vTemp1, v3);
	vTemp1 = _mm_mul_ps(vTemp1, vS3);
	vResult = _mm_add_ps(vTemp1, vResult);

	// Multiply by one half
	return _mm_mul_ps(vResult, gVOneHalf);
}

//*************************************************************************************************
// Barycentric V1 + f(V2 - V1) + g(V3 - V1)
//*************************************************************************************************
Vector Vec4Barycentric(const Vector v1, const Vector v2, const Vector v3, float f, float g)
{
	Vector vF = _mm_set1_ps(f);
	Vector vG = _mm_set1_ps(g);
	return Vec4Barycentric(v1, v2, v3, vF, vG);
}

//*************************************************************************************************
// Barycentric V1 + f(V2 - V1) + g(V3 - V1)
//*************************************************************************************************
Vector Vec4Barycentric(const Vector v1, const Vector v2, const Vector v3, const Vector& f, const Vector& g)
{
	Vector vTemp1 = _mm_sub_ps(v2, v1);
	vTemp1 = _mm_mul_ps(vTemp1, f);
	Vector vResult = _mm_add_ps(v1, vTemp1);

	vTemp1 = _mm_sub_ps(v3, v1);
	vTemp1 = _mm_mul_ps(vTemp1, g);
	return _mm_add_ps(vResult, vTemp1);
}

//*************************************************************************************************
// Transform vector by matrix
//*************************************************************************************************
Vector Vec4Transform(const Vector v, const Matrix& m)
{
	// Splat x, y, z, w
	Vector vX = _mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 0, 0, 0));
	Vector vY = _mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 1, 1, 1));
	Vector vZ = _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 2, 2, 2));
	Vector vW = _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 3, 3, 3));
	
	// Find values
	vX = _mm_mul_ps(vX, m.r[0]);
	vY = _mm_mul_ps(vY, m.r[1]);
	vZ = _mm_mul_ps(vZ, m.r[2]);
	vW = _mm_mul_ps(vW, m.r[3]);

	// Sumation
	vX = _mm_add_ps(vX, vY);
	vX = _mm_add_ps(vX, vZ);
	return _mm_add_ps(vX, vW);	
}
