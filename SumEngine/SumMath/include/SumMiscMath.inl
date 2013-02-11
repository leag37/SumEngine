//*************************************************************************************************
// Title: SumMiscMath.inl
// Author: Gael Huber
// Description: Miscellaneous mathematics functions
//*************************************************************************************************

//*************************************************************************************************
// Sin of an angle
// sin(V) ~= V - V^3 / 3! + V^5 / 5! - V^7 / 7! + V^9 / 9! - V^11 / 11! + V^13 / 13! - 
//           V^15 / 15! + V^17 / 17! - V^19 / 19! + V^21 / 21! - V^23 / 23! (for -PI <= V < PI)
//*************************************************************************************************
SUMINLINE Vector VectorSin(const Vector v)
{
	// Get squared vector to ease transitions between coefficients
	Vector v2 = _mm_mul_ps(v, v);

	// v^3
	Vector vPower = _mm_mul_ps(v, v2);
	Vector vConstant = _mm_load1_ps(&gVSinCoefficient0.f[1]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	Vector vResult = _mm_add_ps(v, vConstant);

	// v^5
	vPower = _mm_mul_ps(vPower, v2);
	vConstant = _mm_load1_ps(&gVSinCoefficient0.f[2]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	vResult = _mm_add_ps(vResult, vConstant);

	// v^7
	vPower = _mm_mul_ps(vPower, v2);
	vConstant = _mm_load1_ps(&gVSinCoefficient0.f[3]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	vResult = _mm_add_ps(vResult, vConstant);

	// v^9
	vPower = _mm_mul_ps(vPower, v2);
	vConstant = _mm_load1_ps(&gVSinCoefficient1.f[0]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	vResult = _mm_add_ps(vResult, vConstant);

	// v^11
	vPower = _mm_mul_ps(vPower, v2);
	vConstant = _mm_load1_ps(&gVSinCoefficient1.f[1]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	vResult = _mm_add_ps(vResult, vConstant);

	// v^13
	vPower = _mm_mul_ps(vPower, v2);
	vConstant = _mm_load1_ps(&gVSinCoefficient1.f[2]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	vResult = _mm_add_ps(vResult, vConstant);

	// v^15
	vPower = _mm_mul_ps(vPower, v2);
	vConstant = _mm_load1_ps(&gVSinCoefficient1.f[3]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	vResult = _mm_add_ps(vResult, vConstant);

	// v^17
	vPower = _mm_mul_ps(vPower, v2);
	vConstant = _mm_load1_ps(&gVSinCoefficient2.f[0]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	vResult = _mm_add_ps(vResult, vConstant);

	// v^19
	vPower = _mm_mul_ps(vPower, v2);
	vConstant = _mm_load1_ps(&gVSinCoefficient2.f[1]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	vResult = _mm_add_ps(vResult, vConstant);

	// v^21
	vPower = _mm_mul_ps(vPower, v2);
	vConstant = _mm_load1_ps(&gVSinCoefficient2.f[2]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	vResult = _mm_add_ps(vResult, vConstant);

	// v^23
	vPower = _mm_mul_ps(vPower, v2);
	vConstant = _mm_load1_ps(&gVSinCoefficient2.f[3]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	vResult = _mm_add_ps(vResult, vConstant);

	return vResult;
}

//*************************************************************************************************
// Cosine of an angle
// cos(V) ~= 1 - V^2 / 2! + V^4 / 4! - V^6 / 6! + V^8 / 8! - V^10 / 10! + V^12 / 12! - 
//           V^14 / 14! + V^16 / 16! - V^18 / 18! + V^20 / 20! - V^22 / 22! (for -PI <= V < PI)
//*************************************************************************************************
SUMINLINE Vector VectorCos(const Vector v)
{
	// Get squared vector to ease transitions between coefficients
	Vector v2 = _mm_mul_ps(v, v);
	
	// v^2
	Vector vConstant = _mm_load1_ps(&gVCosCoefficient0.f[1]);
	vConstant = _mm_mul_ps(v2, vConstant);
	Vector vResult = _mm_add_ps(v, vConstant);

	// v^4
	Vector vPower = _mm_mul_ps(v2, v2);
	vConstant = _mm_load1_ps(&gVCosCoefficient0.f[2]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	vResult = _mm_add_ps(vResult, vConstant);

	// v^6
	vPower = _mm_mul_ps(vPower, v2);
	vConstant = _mm_load1_ps(&gVCosCoefficient0.f[3]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	vResult = _mm_add_ps(vResult, vConstant);

	// v^8
	vPower = _mm_mul_ps(vPower, v2);
	vConstant = _mm_load1_ps(&gVCosCoefficient1.f[0]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	vResult = _mm_add_ps(vResult, vConstant);

	// v^10
	vPower = _mm_mul_ps(vPower, v2);
	vConstant = _mm_load1_ps(&gVCosCoefficient1.f[1]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	vResult = _mm_add_ps(vResult, vConstant);

	// v^12
	vPower = _mm_mul_ps(vPower, v2);
	vConstant = _mm_load1_ps(&gVCosCoefficient1.f[2]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	vResult = _mm_add_ps(vResult, vConstant);

	// v^14
	vPower = _mm_mul_ps(vPower, v2);
	vConstant = _mm_load1_ps(&gVCosCoefficient1.f[3]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	vResult = _mm_add_ps(vResult, vConstant);

	// v^16
	vPower = _mm_mul_ps(vPower, v2);
	vConstant = _mm_load1_ps(&gVCosCoefficient2.f[0]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	vResult = _mm_add_ps(vResult, vConstant);

	// v^18
	vPower = _mm_mul_ps(vPower, v2);
	vConstant = _mm_load1_ps(&gVCosCoefficient2.f[1]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	vResult = _mm_add_ps(vResult, vConstant);

	// v^20
	vPower = _mm_mul_ps(vPower, v2);
	vConstant = _mm_load1_ps(&gVCosCoefficient2.f[2]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	vResult = _mm_add_ps(vResult, vConstant);

	// v^22
	vPower = _mm_mul_ps(vPower, v2);
	vConstant = _mm_load1_ps(&gVCosCoefficient2.f[3]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	vResult = _mm_add_ps(vResult, vConstant);

	return vResult;
}

//*************************************************************************************************
// Sin and cosine of an angle
//*************************************************************************************************
SUMINLINE void VectorSinCos(Vector* pSin, Vector* pCos, const Vector v)
{
	// Declare result vectors
	Vector sin, cos;

	// v^2
	Vector vPower = _mm_mul_ps(v, v);
	Vector vConstant = _mm_load1_ps(&gVCosCoefficient0.f[1]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	cos = _mm_add_ps(gVOne, vConstant);

	// v^3
	vPower = _mm_mul_ps(vPower, v);
	vConstant = _mm_load1_ps(&gVSinCoefficient0.f[1]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	sin = _mm_add_ps(v, vConstant);

	// v^4
	vPower = _mm_mul_ps(vPower, v);
	vConstant = _mm_load1_ps(&gVCosCoefficient0.f[2]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	cos = _mm_add_ps(cos, vConstant);

	// v^5
	vPower = _mm_mul_ps(vPower, v);
	vConstant = _mm_load1_ps(&gVSinCoefficient0.f[2]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	sin = _mm_add_ps(sin, vConstant);

	// v^6
	vPower = _mm_mul_ps(vPower, v);
	vConstant = _mm_load1_ps(&gVCosCoefficient0.f[3]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	cos = _mm_add_ps(cos, vConstant);

	// v^7
	vPower = _mm_mul_ps(vPower, v);
	vConstant = _mm_load1_ps(&gVSinCoefficient0.f[3]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	sin = _mm_add_ps(sin, vConstant);

	// v^8
	vPower = _mm_mul_ps(vPower, v);
	vConstant = _mm_load1_ps(&gVCosCoefficient1.f[0]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	cos = _mm_add_ps(cos, vConstant);

	// v^9
	vPower = _mm_mul_ps(vPower, v);
	vConstant = _mm_load1_ps(&gVSinCoefficient1.f[0]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	sin = _mm_add_ps(sin, vConstant);

	// v^10
	vPower = _mm_mul_ps(vPower, v);
	vConstant = _mm_load1_ps(&gVCosCoefficient1.f[1]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	cos = _mm_add_ps(cos, vConstant);

	// v^11
	vPower = _mm_mul_ps(vPower, v);
	vConstant = _mm_load1_ps(&gVSinCoefficient1.f[1]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	sin = _mm_add_ps(sin, vConstant);

	// v^12
	vPower = _mm_mul_ps(vPower, v);
	vConstant = _mm_load1_ps(&gVCosCoefficient1.f[2]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	cos = _mm_add_ps(cos, vConstant);

	// v^13
	vPower = _mm_mul_ps(vPower, v);
	vConstant = _mm_load1_ps(&gVSinCoefficient1.f[2]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	sin = _mm_add_ps(sin, vConstant);

	// v^14
	vPower = _mm_mul_ps(vPower, v);
	vConstant = _mm_load1_ps(&gVCosCoefficient1.f[3]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	cos = _mm_add_ps(cos, vConstant);

	// v^15
	vPower = _mm_mul_ps(vPower, v);
	vConstant = _mm_load1_ps(&gVSinCoefficient1.f[3]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	sin = _mm_add_ps(sin, vConstant);

	// v^16
	vPower = _mm_mul_ps(vPower, v);
	vConstant = _mm_load1_ps(&gVCosCoefficient2.f[0]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	cos = _mm_add_ps(cos, vConstant);

	// v^17
	vPower = _mm_mul_ps(vPower, v);
	vConstant = _mm_load1_ps(&gVSinCoefficient2.f[0]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	sin = _mm_add_ps(sin, vConstant);

	// v^18
	vPower = _mm_mul_ps(vPower, v);
	vConstant = _mm_load1_ps(&gVCosCoefficient2.f[1]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	cos = _mm_add_ps(cos, vConstant);

	// v^19
	vPower = _mm_mul_ps(vPower, v);
	vConstant = _mm_load1_ps(&gVSinCoefficient2.f[1]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	sin = _mm_add_ps(sin, vConstant);

	// v^20
	vPower = _mm_mul_ps(vPower, v);
	vConstant = _mm_load1_ps(&gVCosCoefficient2.f[2]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	cos = _mm_add_ps(cos, vConstant);

	// v^21
	vPower = _mm_mul_ps(vPower, v);
	vConstant = _mm_load1_ps(&gVSinCoefficient2.f[2]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	sin = _mm_add_ps(sin, vConstant);

	// v^22
	vPower = _mm_mul_ps(vPower, v);
	vConstant = _mm_load1_ps(&gVCosCoefficient2.f[3]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	cos = _mm_add_ps(cos, vConstant);

	// v^23
	vPower = _mm_mul_ps(vPower, v);
	vConstant = _mm_load1_ps(&gVSinCoefficient2.f[3]);
	vConstant = _mm_mul_ps(vPower, vConstant);
	sin = _mm_add_ps(sin, vConstant);

	// Final assignment
	*pCos = cos;
	*pSin = sin;
}

//*************************************************************************************************
//
//*************************************************************************************************

