//*************************************************************************************************
// Title: SumBaseTest.h
// Author: Gael Huber
// Description: Base class for other test suites to inherit from. Takes care of standard operations
//	like keeping track of total error count per suite, logging success vs. failure, etc.
//*************************************************************************************************
#ifndef __SUMBASETEST_H__
#define __SUMBASETEST_H__

#include "SumInclude.h"
#include "SumString.h"

#include <iostream>
using namespace std;

class BaseTest
{
public:
	// Constructor
	BaseTest();

	// Constructor
	BaseTest(const String& suiteName);

	// Copy constructor
	BaseTest(const BaseTest& rhs);

	// Destructor
	virtual ~BaseTest();

	// Assignment
	BaseTest& operator=(const BaseTest& rhs);

	// Run the test suite
	void run();

	// Get the number of errors
	SUINT getErrors();

	// Get the number of tests
	SUINT getTests();

protected:
	// Reset a test
	void reset();

	// Log an error
	void logError(SUINT testCase);

	// Log the start of a test
	void logStart();

	// Log results of a test suite
	void logResults();

protected:
	// Name of test suite, for example Vector
	String _suiteName;

	// Name of individual test case, for example Init
	String _testName;

	// Errors
	SUINT _errors;

	// Tests executed
	SUINT _tests;
};

#endif