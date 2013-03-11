//*************************************************************************************************
// Title: SumTestHelper.h
// Author: Gael Huber
// Description: Series of helper function to help print results and assert desired outcomes.
//
// TODO: Convert to using SumPlatform variables
// TOOD: Define helper Struct and Class
//*************************************************************************************************
#ifndef __SUMTESTHELPER_H__
#define __SUMTESTHELPER_H__

#include "SumInclude.h"
#include "SumString.h"

#include <iostream>
using namespace std;

namespace Test
{

// Print start of test
inline void printStart(const String& title)
{
	cout << "********************************************************************************" << endl;
	cout << "Beginning " << title.c_str() << "." << endl << endl << endl;
}

// Print results of a test
inline void printResult(SUINT errors, SUINT tests, const String& title)
{
	// Success
	if(errors == 0)
	{
		cout << "Success! " << title.c_str() << " completed " << tests << " tests with 0 errors." << endl;
	}

	// Failure
	else
	{
		cout << "Failed! " << title.c_str() << " completed " << tests << " with " << errors << " errors." << endl;
	}
}

// Print an error
inline void printError(const String& testName, int testCase)
{
	cout << testName.c_str() << " failed on case " << testCase << "!" << endl;
}

// Print suite results
inline void printSuiteResults(SUINT errors, SUINT tests, const String& title)
{
	cout << endl;
	cout << title.c_str() << " ran " << tests << " tests with " << errors << " errors. " << endl;
	cout << "The percentage of tests passed is " << static_cast<float>(tests - errors) / static_cast<float>(tests) * 100.0f << "%." << endl;
	cout << "********************************************************************************" << endl << endl;
}

// Print help
inline void printHelp()
{
	cout << "Active configurations: " << endl;
	cout << "all -- run all test suites" << endl;
	cout << "math -- run math suite" << endl;
	cout << "utilities -- run utilities suite" << endl;
}

// Assertion statement
inline SBOOL assertExpression(SBOOL a, SBOOL b)
{
	return a == b;
}


//***************************
// TEST STRUCT
//***************************
struct TestStruct
{
	TestStruct()
		: a(0), b(1)
	{ 
		c = this;
	}

	SBOOL operator==(const TestStruct& rhs)
	{
		return a == rhs.a && b == rhs.b && c == rhs.c;
	}

	SBOOL operator!=(const TestStruct& rhs)
	{
		return a != rhs.a || b != rhs.b || c != rhs.c;
	}

	int a;
	int b;
	TestStruct* c;
};

//***************************
// TEST CLASS
//***************************
class TestClass
{
public:
	TestClass()
		: a(2), b(3)
	{ 
		c = this;
	}

	SBOOL operator==(const TestClass& rhs)
	{
		return a == rhs.a && b == rhs.b && c == rhs.c;
	}

	SBOOL operator!=(const TestClass& rhs)
	{
		return a != rhs.a || b != rhs.b || c != rhs.c;
	}

	int a;
	int b;
	TestClass* c;
};

}

#endif