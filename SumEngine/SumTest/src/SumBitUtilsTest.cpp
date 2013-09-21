//*************************************************************************************************
// Title: SumBitUtilsTest.h
// Author: Gael Huber
// Description: Driver for bit utilities tests.
//*************************************************************************************************
#include "SumBitUtilsTest.h"

//*************************************************************************************************
// Constructor
//*************************************************************************************************
BitUtilsTest::BitUtilsTest()
	: BaseTest()
{ }

//*************************************************************************************************
// Constructor
//*************************************************************************************************
BitUtilsTest::BitUtilsTest(const String& suiteName)
	: BaseTest(suiteName)
{ }

//*************************************************************************************************
// Run the test
//*************************************************************************************************
void BitUtilsTest::run()
{
	// Reset the error count
	reset();

	// Log the start of the test
	logStart();

	// Run test cases
	testScanReverse();

	// Log the result
	logResults();
}

//*************************************************************************************************
// Test bit scan reverese
//*************************************************************************************************
void BitUtilsTest::testScanReverse()
{
	_testName = "BitScanReverse";

	// Count local errors
	SUINT tErrors = 0;
	SUINT tTests = 0;
	SUINT tCase = 0;
//	SBOOL result = false;

	// Prep variables
	SUCHAR success;
	SUINT index;
	SUINT mask;

	// Test case 1: 0
	// 00000000000000000000000000000000
	++tTests;
	++tCase;
	mask = 0;
	success = ReverseBitScan(&index, mask);
	if(success != 0)
	{
		logError(tCase);
		++tErrors;
	}

	// Test case 2: 0xFFFFFFFF
	// 11111111111111111111111111111111
	++tTests;
	++tCase;
	mask = 0xFFFFFFFF;
	success = ReverseBitScan(&index, mask);
	if(success == 0 || index != 31)
	{
		logError(tCase);
		++tErrors;
	}

	// TODO
	// Test case 3: 0xF0F0F0F0
	// 11110000111100001111000011110000
	++tTests;
	++tCase;
	mask = 0xF0F0F0F0;
	success = ReverseBitScan(&index, mask);
	if(success == 0 || index != 31)
	{
		logError(tCase);
		++tErrors;
	}

	// Test case 4: 1
	// 00000000000000000000000000000001
	++tTests;
	++tCase;
	mask = 1;
	success = ReverseBitScan(&index, mask);
	if(success == 0 || index != 0)
	{
		logError(tCase);
		++tErrors;
	}

	// Test case 5: 3
	// 00000000000000000000000000000011
	++tTests;
	++tCase;
	mask = 3;
	success = ReverseBitScan(&index, mask);
	if(success == 0 || index != 1)
	{
		logError(tCase);
		++tErrors;
	}

	// Test case 6: 120
	// 00000000000000000000000001111000
	++tTests;
	++tCase;
	mask = 120;
	success = ReverseBitScan(&index, mask);
	if(success == 0 || index != 6)
	{
		logError(tCase);
		++tErrors;
	}

	// Test case 7: 123
	// 00000000000000000000000001111011
	++tTests;
	++tCase;
	mask = 123;
	success = ReverseBitScan(&index, mask);
	if(success == 0 || index != 6)
	{
		logError(tCase);
		++tErrors;
	}

	// Test case 8: 0x0F0F0F0F
	// 00001111000011110000111100001111
	++tTests;
	++tCase;
	mask = 0x0F0F0F0F;
	success = ReverseBitScan(&index, mask);
	if(success == 0 || index != 27)
	{
		logError(tCase);
		++tErrors;
	}

	// Test case 9: 0xFFFF0000
	// 11111111111111110000000000000000
	++tTests;
	++tCase;
	mask = 0xFFFF0000;
	success = ReverseBitScan(&index, mask);
	if(success == 0 || index != 31)
	{
		logError(tCase);
		++tErrors;
	}

	// Test case 10: 0x0000FFFF
	// 00000000000000001111111111111111
	++tTests;
	++tCase;
	mask = 0x0000FFFF;
	success = ReverseBitScan(&index, mask);
	if(success == 0 || index != 15)
	{
		logError(tCase);
		++tErrors;
	}
}

//*************************************************************************************************
// Test bit scan forward
//*************************************************************************************************
//void BitUtilsTest::testScanForward();
