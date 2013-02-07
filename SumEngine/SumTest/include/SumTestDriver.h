//*************************************************************************************************
// Title: SumTestDriver.h
// Author: Gael Huber
// Description: Driver for tests.
//
// TODO: Write math suite
// TODO: Write utilities suite
// TODO: Write threading suite
//*************************************************************************************************
#ifndef __SUMTESTDRIVER_H__
#define __SUMTESTDRIVER_H__

#include "SumMathTest.h"
//#include "SumUtilitiesTest.h"

// Run help
void runHelp()
{
	Test::printHelp();
}

// Math
void runMathSuite()
{
	runMathTests();
}

// Utilities
void runUtilitiesSuite()
{
//	runUtilitiesTests();
}

// All
void runAllSuites()
{
	runMathSuite();
	runUtilitiesSuite();
}
	

#endif