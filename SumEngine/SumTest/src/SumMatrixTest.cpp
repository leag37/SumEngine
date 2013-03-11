//*************************************************************************************************
// Title: SumMatrixTest.cpp
// Author: Gael Huber
// Description: Matrix test suite
//*************************************************************************************************
#include "SumMatrixTest.h"

void matrixSuite(int& errors, int& tests)
{
	//errors += matrixInit(tests);
	errors += matrixEqual(tests);
	errors += matrixNotEqual(tests);
	errors += matrixTranspose(tests);
}

// Test initialization patterns for matrix
int matrixInit(int& tests)
{
	int errors = 0;

	// Test case 1 - load individually
	++tests;
	
	return errors;
}

int matrixEqual(int& tests)
{
	int errors = 0;

	// Test Case 1 - Equality
	Matrix m1 = Matrix(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
	Matrix m2 = Matrix(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
	if(!MatrixEqual(m1, m2))
	{
		Test::printError("MatrixEqual", 1);
		++errors;
	}
	++tests;

	// Test Case 2 - Partial Inequality
	m2 = Matrix(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 17.0f);
	if(MatrixEqual(m1, m2))
	{
		Test::printError("MatrixEqual", 2);
		++errors;
	}
	++tests;

	// Test Case 3 - Full Inequality
	m2 = Matrix(16.0f, 15.0f, 14.0f, 13.0f, 12.0f, 11.0f, 10.0f, 9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f);
	if(MatrixEqual(m1, m2))
	{
		Test::printError("MatrixEqual", 3);
		++errors;
	}
	++tests;

	return errors;
}

int matrixNotEqual(int& tests)
{
		int errors = 0;

	// Test Case 1 - Equality
	Matrix m1 = Matrix(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
	Matrix m2 = Matrix(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
	if(!assertExpression(MatrixNotEqual(m1, m2), false))
	{
		Test::printError("MatrixNotEqual", 1);
		++errors;
	}
	++tests;

	// Test Case 2 - Partial Inequality
	m2 = Matrix(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 17.0f);
	if(!MatrixNotEqual(m1, m2))
	{
		Test::printError("MatrixNotEqual", 2);
		++errors;
	}
	++tests;

	// Test Case 3 - Full Inequality
	m2 = Matrix(16.0f, 15.0f, 14.0f, 13.0f, 12.0f, 11.0f, 10.0f, 9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f);
	if(!MatrixNotEqual(m1, m2))
	{
		Test::printError("MatrixNotEqual", 3);
		++errors;
	}
	++tests;

	return errors;
}

int matrixTranspose(int& tests)
{
	int errors = 0;

	// Test case 1
	// [1  2  3  4 ]
	// [5  6  7  8 ]
	// [9  10 11 12]
	// [13 14 15 16]
	//
	// Tranpose:
	// [1  5  9  13]
	// [2  6  10 14]
	// [3  7  11 15]
	// [4  8  12 16]
	Matrix m0 = Matrix(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
	Matrix m1 = MatrixTranspose(m0);
	Matrix m2 = Matrix(1.0f, 5.0f, 9.0f, 13.0f, 2.0f, 6.0f, 10.0f, 14.0f, 3.0f, 7.0f, 11.0f, 15.0f, 4.0f, 8.0f, 12.0f, 16.0f);
	if(MatrixNotEqual(m1, m2))
	{
		Test::printError("MatrixTranpose", 1);
		++errors;
	}
	++tests;

	Test::printResult(errors, tests, "MatrixTranpose");
	return errors;
}
