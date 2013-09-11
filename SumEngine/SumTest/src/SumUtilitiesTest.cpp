//*************************************************************************************************
// Title: SumUtilitiesTest.h
// Author: Gael Huber
// Description: Driver for math tests.
//*************************************************************************************************
#include "SumUtilitiesTest.h"

void RunUtilitiesTests()
{
	// Init
	Test::printStart("Utilities Suite");

	// Total errors
	SUINT totalErrors = 0;
	SUINT totalTests = 0;

	// Errors for a given test
	SUINT errors = 0;
	SUINT tests = 0;

	// Run queue suite
	QueueSuite(errors, tests);
	Test::printSuiteResults(errors, tests, "Queue Suite");
	totalErrors += errors;
	totalTests += tests;
	errors = 0;
	tests = 0;

	// Bit test suite
	BitUtilsTest bitUtils("Bit Utils Suite");
	bitUtils.run();
	totalErrors += bitUtils.getErrors();
	totalTests += bitUtils.getTests();
}