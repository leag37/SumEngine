//*************************************************************************************************
// Title: SumVectorTest.cpp
// Author: Gael Huber
// Description: Vector test suite
//*************************************************************************************************
#include "SumVectorTest.h"

//*************************************************************************************************
// Vector suite
//*************************************************************************************************
void vectorSuite(int& errors, int& tests)
{
	errors += vectorInit(tests);
	errors += vectorSet(tests);
}

//*************************************************************************************************
// Vector initialization
//*************************************************************************************************
int vectorInit(int& tests)
{
	int errors = 0;

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
	
	Test::printResult(errors, "VectorInit");
	return errors;
}

// Set a vector
int vectorSet(int& tests)
{
	int errors = 0;

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

	Test::printResult(errors, "VectorSet");
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
