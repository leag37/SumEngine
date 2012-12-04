
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
Vector Vec3Hermite(const Vector v1, const Vector t1, const Vector v2, const Vector t2, float s)
{
	Vector vS = _mm_load1_ps(&s);
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
Vector Vec3Hermite(const Vector v1, const Vector t1, const Vector v2, const Vector t2, Vector s)
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
Vector Vec3CatmullRom(const Vector v0, const Vector v1, const Vector v2, const Vector v3, float s)
{
	Vector vS = _mm_load1_ps(&s);
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
Vector Vec3CatmullRom(const Vector v0, const Vector v1, const Vector v2, const Vector v3, const Vector s)
{

}

//*************************************************************************************************
// 
//*************************************************************************************************

//*************************************************************************************************
// 
//*************************************************************************************************
