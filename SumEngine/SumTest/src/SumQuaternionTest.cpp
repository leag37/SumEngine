//*************************************************************************************************
// Title: SumQuaternionTest.cpp
// Author: Gael Huber
// Description: Quaternion test suite
//*************************************************************************************************
#include "SumQuaternionTest.h"

QuaternionTest::QuaternionTest()
	: BaseTest()
{ }

QuaternionTest::QuaternionTest(const String& suiteName)
	: BaseTest(suiteName)
{ }

void QuaternionTest::run()
{
	// Reset error count
	reset();

	// Log start of test
	logStart();

	// Run test cases
	testInit();
	testAssignment();

	// Log the results
	logResults();
}

// Test initialization
void QuaternionTest::testInit()
{
	_testName = "Init";

	// Count local errors and tests run
	SUINT tErrors = 0;
	SUINT tTests = 0;
	SBOOL result = false;

	// Test case 1: Base init, expect identity quaternion
	SUINT tCase = 1;
	Vector q = QuaternionIdentity();
	Vector r = VectorEqual(q, QuaternionIdentity());
	result = _mm_movemask_ps(r) == 15;
	if(result == false)
	{
		logError(tCase);
		++tErrors;
	}
	++tTests;

	// Test case 2: Quaternion from matrix (identity)
	++tCase;
	Matrix m = MatrixIdentity();
	//Vector q = QuaternionRotationMatrix(m);

	// Test case 3: Quaternion from matrix (rotated)
	++tCase;

	// Test case 4: Quaternion from axis-angle (x-axis)
	++tCase;
	Float4 f;
	Vector axis = gVIdentityR0;
	Vector angle = VectorReplicate(S_PI);
//	Vector hAngle = VectorMul(angle, gVOneHalf);
	Vector sin, cos;
	VectorSinCos(&sin, &cos, angle);
	q = QuaternionRotationAxis(axis, angle);
	StoreFloat4(&f, q);
	
	r = VectorEqual(q, VectorSet(1.0f, 0.0f, 0.0f, 0.0f));
	// Test case 5: Quaternion from axis-angle (y-axis)

	// Test case 6: Quaternion from axis-angle (z-axis)

	// Test case 7: Quaternion from axis-angle (arbitrary)

	// Test case 8: Quaternion from yaw pitch roll (yaw)

	// Test case 9: Quaternion from yaw pitch roll (pitch)

	// Test case 10: Quaternion from yaw pitch roll (roll)

	// Test case 11: Quaternion from yaw pitch roll (yaw, pitch)

	// Test case 12: Quaternion from yaw pitch roll (yaw, roll)

	// Test case 13: Quaternion from yaw pitch roll (pitch, roll)

	// Test case 14: Quaternion from yaw pitch roll (yaw, pitch, roll)


	// Increment tests and stuff at the end
	_tests += tTests;
	_errors += tErrors;
}

// Test assignment
void QuaternionTest::testAssignment()
{

}