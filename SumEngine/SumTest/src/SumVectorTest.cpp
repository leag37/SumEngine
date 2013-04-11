//*************************************************************************************************
// Title: SumVectorTest.cpp
// Author: Gael Huber
// Description: Vector test suite
//*************************************************************************************************
#include "SumVectorTest.h"

//*************************************************************************************************
// Vector suite
//*************************************************************************************************
void vectorSuite(SUINT& errors, SUINT& tests)
{
	errors += vectorInit(tests);
	errors += vectorSet(tests);
	TestVectorCompareEqual(errors, tests);
	TestVectorCompareNotEqual(errors, tests);
}

//*************************************************************************************************
// Vector initialization
//*************************************************************************************************
SUINT vectorInit(SUINT& tests)
{
	SUINT errors = 0;

	// Test case 1 - zero vector
	Vector v0 = VectorZero();
	if(v0.m128_f32[0] != 0.0f || v0.m128_f32[1] != 0.0f || v0.m128_f32[2] != 0.0f || v0.m128_f32[3] != 0.0f)
		++errors;
	++tests;

	// Test case 2 - set to array
	Vector v1 = {0.0f, 0.0f, 0.0f, 0.0f};
	if(v1.m128_f32[0] != 0.0f || v1.m128_f32[1] != 0.0f || v1.m128_f32[2] != 0.0f || v1.m128_f32[3] != 0.0f)
		++errors;
	++tests;
	
	Test::printResult(errors, tests, "VectorInit");
	return errors;
}

// Set a vector
SUINT vectorSet(SUINT& tests)
{
	SUINT errors = 0;

	// Test case 1 - set a vector using VectorSet
	Vector v0 = VectorSet(0.0f, 1.0f, 2.0f, 3.0f);
	if(v0.m128_f32[0] != 0.0f || v0.m128_f32[1] != 1.0f || v0.m128_f32[2] != 2.0f || v0.m128_f32[3] != 3.0f)
		++errors;
	++tests;

	// Test case 2 - set a vector using assignment
	Vector v1 = v0;
	if(v1.m128_f32[0] != 0.0f || v1.m128_f32[1] != 1.0f || v1.m128_f32[2] != 2.0f || v1.m128_f32[3] != 3.0f)
		++errors;
	++tests;

	// Test case 3 - set a vector by manipulating individual components
	Vector v2;
	v2.m128_f32[0] = 0.0f;
	v2.m128_f32[1] = 1.0f;
	v2.m128_f32[2] = 2.0f;
	v2.m128_f32[3] = 3.0f;
	if(v2.m128_f32[0] != 0.0f || v2.m128_f32[1] != 1.0f || v2.m128_f32[2] != 2.0f || v2.m128_f32[3] != 3.0f)
		++errors;
	++tests;

	Test::printResult(errors, tests, "VectorSet");
	return errors;
}

//int vectorNegate(int& tests);
//int vectorScale(int& tests);
//int vectorAdd(int& tests);
//int vectorSubtract(int& tests);
//int vectorDivide(int& tests);
//int vectorMultiply(int& tests);
//int vectorEqual(int& tests);
//int vectorNotEqual(int& tests);

void TestVectorCompareEqual(SUINT& errors, SUINT& tests)
{
	const String title = "VectorCompareEqual";

	// Count local errors and tests run
	SUINT tErrors = 0;
	SUINT tTests = 0;

	// Test variables
	Vector v1 = VectorZero();
	Vector v2 = VectorZero();
	SBOOL result = false;

	// Test case 1: Complete equality
	v1 = v2 = gVOne;
	result = VectorCompareEqual(v1, v2);
	if(result == false)
	{
		Test::printError(title, 1);
		++tErrors;
	}
	++tTests;

	// Test case 2: Partial equality
	v2 = VectorSet(1.0f, 1.0f, 2.0f, 2.0f);
	result = VectorCompareEqual(v1, v2);
	if(result == true)
	{
		Test::printError(title, 2);
		++tErrors;
	}
	++tTests;

	// Test case 3: Complete inequality
	v2 = VectorSet(2.0f, 2.0f, 2.0f, 2.0f);
	result = VectorCompareEqual(v1, v2);
	if(result == true)
	{
		Test::printError(title, 3);
		++tErrors;
	}
	++tTests;

	// Print results
	Test::printResult(tErrors, tTests, title);

	// Increase total error count
	errors += tErrors;
	tests += tTests;
}

void TestVectorCompareNotEqual(SUINT& errors, SUINT& tests)
{
	const String title = "VectorCompareNotEqual";

	// Count local errors and tests run
	SUINT tErrors = 0;
	SUINT tTests = 0;

	// Test variables
	Vector v1 = VectorZero();
	Vector v2 = VectorZero();
	SBOOL result = false;

	// Test case 1: Complete equality
	v1 = v2 = gVOne;
	result = VectorCompareNotEqual(v1, v2);
	if(result == true)
	{
		Test::printError(title, 1);
		++tErrors;
	}
	++tTests;

	// Test case 2: Partial equality
	v2 = VectorSet(1.0f, 1.0f, 2.0f, 2.0f);
	result = VectorCompareNotEqual(v1, v2);
	if(result == false)
	{
		Test::printError(title, 2);
		++tErrors;
	}
	++tTests;

	// Test case 3: Complete inequality
	v2 = VectorSet(2.0f, 2.0f, 2.0f, 2.0f);
	result = VectorCompareNotEqual(v1, v2);
	if(result == false)
	{
		Test::printError(title, 3);
		++tErrors;
	}
	++tTests;

	// Print results
	Test::printResult(tErrors, tTests, title);

	// Increase total error count
	errors += tErrors;
	tests += tTests;
}

