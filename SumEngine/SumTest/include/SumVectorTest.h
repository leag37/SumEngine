#ifndef __SUMVECTORTEST_H__
#define __SUMVECTORTEST_H__

#include "SumMath.h"
#include "SumTestHelper.h"

using namespace std;

extern "C"
{
	void vectorSuite(int& errors, int& tests);
	
	int initVector(int& tests);
	int setVector(int& tests);
	int negateVector(int& tests);
	int scaleVector(int& tests);
	int addVector(int& tests);
	int subtractVector(int& tests);
	int divideVector(int& tests);
	int multiplyVector(int& tests);
	int equalVector(int& tests);
	int notEqualVector(int& tests);

}

#endif