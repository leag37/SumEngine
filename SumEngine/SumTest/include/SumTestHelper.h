//*************************************************************************************************
// Title: SumTestHelper.h
// Author: Gael Huber
// Description: Series of helper function to help print results and assert desired outcomes.
//*************************************************************************************************
#ifndef __SUMTESTHELPER_H__
#define __SUMTESTHELPER_H__

#include <iostream>
using namespace std;

namespace Test
{

// Print start of test
inline void printStart(const char* title)
{
	cout << "********************************************************************************" << endl;
	cout << "Beginning " << title << "." << endl << endl << endl;
}

// Print results of a test
inline void printResult(int errors, const char* title)
{
	// Success
	if(errors == 0)
	{
		cout << "Success! " << title << " completed with 0 errors." << endl;
	}

	// Failure
	else
	{
		cout << "Failed! " << title << " completed with " << errors << " errors." << endl;
	}
}

// Print an error
inline void printError(const char* testName, int testCase)
{
	cout << testName << " failed on case " << testCase << "!" << endl;
}

// Print suite results
inline void printSuiteResults(int errors, int tests, const char* title)
{
	cout << endl;
	cout << title << " ran " << tests << " tests with " << errors << " errors. " << endl;
	cout << "The percentage of tests passed is " << static_cast<float>(tests - errors) / static_cast<float>(tests) * 100.0f << "%." << endl;
	cout << "********************************************************************************" << endl << endl;
}

// Print help
inline void printHelp()
{
	cout << "Active configurations: " << endl;
	cout << "all -- run all test suites" << endl;
	cout << "math -- run math suites" << endl;
}

// Assertion statement
inline SBOOL assertExpression(SBOOL a, SBOOL b)
{
	return a == b;
}

}

#endif