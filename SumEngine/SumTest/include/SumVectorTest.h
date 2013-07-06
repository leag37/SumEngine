//*************************************************************************************************
// Title: SumVectorTest.h
// Author: Gael Huber
// Description: Vector test suite
// 
// TODO: Port to new class-based style of running tests
//*************************************************************************************************
#ifndef __SUMVECTORTEST_H__
#define __SUMVECTORTEST_H__

#include "SumMath.h"
#include "SumTestHelper.h"

using namespace std;

extern "C"
{
	void vectorSuite(SUINT& errors, SUINT& tests);
	
	SUINT vectorInit(SUINT& tests);
	SUINT vectorSet(SUINT& tests);
	int vectorNegate(int& tests);
	int vectorScale(int& tests);
	int vectorAdd(int& tests);
	int vectorSubtract(int& tests);
	int vectorDivide(int& tests);
	int vectorMultiply(int& tests);
	int vectorEqual(int& tests);
	int vectorNotEqual(int& tests);
	void TestVectorCompareEqual(SUINT& errors, SUINT& tests);
	void TestVectorCompareNotEqual(SUINT& errors, SUINT& tests);

}

#endif