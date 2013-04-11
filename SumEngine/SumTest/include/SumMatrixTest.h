//*************************************************************************************************
// Title: SumMatrixTest.cpp
// Author: Gael Huber
// Description: Matrix test suite
//*************************************************************************************************
#ifndef __SUMMATRIXTEST_H__
#define __SUMMATRIXTEST_H__

#include "SumMath.h"
#include "SumTestHelper.h"

using namespace std;
using namespace Test;

extern "C"
{
	void matrixSuite(SUINT& errors, SUINT& tests);
	
	SUINT matrixInit(SUINT& tests);
	SUINT matrixEqual(SUINT& tests);
	SUINT matrixNotEqual(SUINT& tests);
	SUINT matrixTranspose(SUINT& tests);
	SUINT matrixInverse(SUINT& tests);
}

#endif