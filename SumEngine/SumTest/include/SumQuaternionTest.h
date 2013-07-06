//*************************************************************************************************
// Title: SumQuaternionTest.h
// Author: Gael Huber
// Description: Quaternion test suite
//*************************************************************************************************
#ifndef __SUMQUATERNIONTEST_H__
#define __SUMQUATERNIONTEST_H__

#include "SumBaseTest.h"
#include "SumMath.h"

class QuaternionTest : public BaseTest
{
public:
	// Constructor
	QuaternionTest();

	QuaternionTest(const String& suiteName);

	void run();

private:
	void testInit();
	void testAssignment();
};

#endif