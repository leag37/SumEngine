//*************************************************************************************************
// Title: SumMathTest.h
// Author: Gael Huber
// Description: Driver for math tests.
//*************************************************************************************************
#ifndef __SUMMATHTEST_H__
#define __SUMMATHTEST_H__

#include "SumVectorTest.h"
#include "SumMatrixTest.h"
#include "SumQuaternionTest.h"

// Run entire math suite
void runMathTests()
{
	// Init
	Test::printStart("Math Suite");

	// Total errors
	SUINT totalErrors = 0;
	SUINT totalTests = 0;

	// Errors for a given test
	SUINT errors = 0;
	SUINT tests = 0;

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

	QuaternionTest quaternions("Quaternion Suite");
	quaternions.run();
	totalErrors += quaternions.getErrors();
	totalTests += quaternions.getTests();
}

#endif