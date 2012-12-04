//*************************************************************************************************
// Title: SumMathTest.h
// Author: Gael Huber
// Description: Driver for math tests.
//*************************************************************************************************
#ifndef __SUMMATHTEST_H__
#define __SUMMATHTEST_H__

#include "SumVectorTest.h"

// Run entire math suite
void runMathTests()
{
	// Init
	Test::printStart("Math Suite");

	// Total errors
	int totalErrors = 0;
	int totalTests = 0;

	// Errors for a given test
	int errors = 0;
	int tests = 0;

	// Run vector suite
	vectorSuite(errors, tests);
	Test::printSuiteResults(errors, tests, "Vector Suite");

	// Reset errors
}

#endif