//*************************************************************************************************
// Title: SumTestDriver.h
// Author: Gael Huber
// Description: Driver for tests.
//*************************************************************************************************
#ifndef __SUMTESTDRIVER_H__
#define __SUMTESTDRIVER_H__

#include "SumMathTest.h"

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

// All
void runAllSuites()
{
	runMathSuite();
}
	

#endif