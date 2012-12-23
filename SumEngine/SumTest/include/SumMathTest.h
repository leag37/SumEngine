//*************************************************************************************************
// Title: SumMathTest.h
// Author: Gael Huber
// Description: Driver for math tests.
//*************************************************************************************************
#ifndef __SUMMATHTEST_H__
#define __SUMMATHTEST_H__

#include "SumVectorTest.h"
#include "SumMatrixTest.h"

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
	totalErrors += errors;
	totalTests += tests;
	errors = 0;
	tests = 0;

	// Run matrix suite
	matrixSuite(errors, tests);
	Test::printSuiteResults(errors, tests, "Matrix Suite");
	totalErrors += errors;
	totalTests += tests;
	errors = 0;
	tests = 0;
}

#endif