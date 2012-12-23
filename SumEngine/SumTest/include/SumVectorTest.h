//*************************************************************************************************
// Title: SumVectorTest.h
// Author: Gael Huber
// Description: Vector test suite
//*************************************************************************************************
#ifndef __SUMVECTORTEST_H__
#define __SUMVECTORTEST_H__

#include "SumMath.h"
#include "SumTestHelper.h"

using namespace std;

extern "C"
{
	void vectorSuite(int& errors, int& tests);
	
	int vectorInit(int& tests);
	int vectorSet(int& tests);
	int vectorNegate(int& tests);
	int vectorScale(int& tests);
	int vectorAdd(int& tests);
	int vectorSubtract(int& tests);
	int vectorDivide(int& tests);
	int vectorMultiply(int& tests);
	int vectorEqual(int& tests);
	int vectorNotEqual(int& tests);

}

#endif