//*************************************************************************************************
// Title: SumBitUtilsTest.h
// Author: Gael Huber
// Description: Driver for bit utilities tests.
//*************************************************************************************************
#ifndef __SUMBITUTILSTEST_H__
#define __SUMBITUTILSTEST_H__

#include "SumBitUtils.h"
#include "SumBaseTest.h"

class BitUtilsTest : public BaseTest
{
public:
	// Constructor
	BitUtilsTest();

	BitUtilsTest(const String& suiteName);

	void run();

private:
	void testScanReverse();
	void testScanForward();
};

#endif // __SUMBITTEST_H__