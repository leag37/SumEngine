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
	void matrixSuite(int& errors, int& tests);
	
	int matrixInit(int& tests);
	int matrixEqual(int& tests);
	int matrixNotEqual(int& tests);
	int matrixTranspose(int& tests);
}

#endif