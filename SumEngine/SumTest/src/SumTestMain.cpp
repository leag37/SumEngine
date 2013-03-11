//*************************************************************************************************
// Title: SumTestMain.cpp
// Author: Gael Huber
// Description: Entry point for test suite.
//*************************************************************************************************
#include "SumTestDriver.h"

#include <string>
#include <cstdio>

using namespace std;

bool processInput(string);

int main()
{
	bool run = true;
	
	cout << "Welcome to the Sum Engine Test Suite!" << endl;

	while(run)
	{
		cout << "Please enter a suite to test or 'help' for help..." << endl << ">> ";

		string input;
		cin >> input;

		run = processInput(input);
	}
	return 0;
}

// Process the input
bool processInput(string input)
{
	// Exit case
	if(input == "exit")
		return false;

	// Help
	if(input == "help")
		runHelp();
	
	// All
	else if(input == "all")
		runAllSuites();
	
	// Math
	else if(input == "math")
		runMathSuite();

	// Utilities
	else if(input == "utilities")
	{
		runUtilitiesSuite();
	}

	return true;
}