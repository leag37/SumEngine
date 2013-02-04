/**************************************************************************************************
* Title: SumRandom.h
* Author: Gael Huber
* Description: Implements George Marsaglia's Mother of all RNGs with slight modifications for ease
*	of usability. Core algorithm remains identical.
**************************************************************************************************/
#include "SumRandom.h"

/**************************************************************************************************
* Seed random number generator
**************************************************************************************************/
void seed(unsigned long pSeed) {
	// Initialize motheri with 9 random values the first time
	if(mStart) {
		s = (unsigned long*) malloc(sizeof(unsigned long));
		*s = pSeed;	// Set the seed

		unsigned long number;
		unsigned short sNumber;
		short n;
		short* p;

		sNumber = *s & m16Mask;		// The low 16-bits
		number = *s & m31Mask;		// Only want 31 bits

		p = mother1;
		for(n = 18; n--;) {
			number = 30903 * sNumber + (number >> 16);	// One line multiply-with-carry
			*p++ = sNumber = number & m16Mask;

			if(n == 9)
				p = mother2;
		}

		// Make carry 15 bits
		mother1[0] &= m15Mask;
		mother2[0] &= m15Mask;
		mStart = 0;
	}
}

/**************************************************************************************************
* Seed the random generator with a self-generated value
**************************************************************************************************/
void seed(void) {
	seed((unsigned long) time(0));
}

/**************************************************************************************************
* Generate a random double between 0 and 1
**************************************************************************************************/
double nextDouble(void) {
	unsigned long number1, number2;
	
	// Move elements 1 to 8 to 2 to 9
	memmove(mother1 + 2, mother1 + 1, 8 * sizeof(short));
	memmove(mother2 + 2, mother2 + 1, 8 * sizeof(short));

	// Put the carry values in numberi
	number1 = mother1[0];
	number2 = mother2[0];

	// Form the linear combination
	number1 += 1941*mother1[2] + 1860*mother1[3] + 1812*mother1[4] + 1776*mother1[5] + 
		1492*mother1[6] + 1215*mother1[7] + 1066*mother1[8] + 12013*mother1[9];
	
	number2 += 1111*mother2[2] + 2222*mother2[3] + 3333*mother2[4] + 4444*mother2[5] +
		5555*mother2[6] + 6666*mother2[7] + 7777*mother2[8] + 9272*mother2[9];

	// Save the high bits of numberi as the new carry
	mother1[0] = (short) (number1 / m16Long);
	mother2[0] = (short) (number2 / m16Long);

	// Put the low bits of numberi into motheri[1]
	mother1[1] = m16Mask & number1;
	mother2[1] = m16Mask & number2;

	// Combine the two 16 bit random numbers into one 32 bit
	*s = (((long)mother1[1]) << 16) + (long)mother2[1];

	// Return a double value between 0 and 1
	return ((double)*s) / m32Double;
}

/**************************************************************************************************
* Generate a random float between 0 and 1
**************************************************************************************************/
float nextFloat(void) {
	unsigned long number1, number2;
	
	// Move elements 1 to 8 to 2 to 9
	memmove(mother1 + 2, mother1 + 1, 8 * sizeof(short));
	memmove(mother2 + 2, mother2 + 1, 8 * sizeof(short));

	// Put the carry values in numberi
	number1 = mother1[0];
	number2 = mother2[0];

	// Form the linear combination
	number1 += 1941*mother1[2] + 1860*mother1[3] + 1812*mother1[4] + 1776*mother1[5] + 
		1492*mother1[6] + 1215*mother1[7] + 1066*mother1[8] + 12013*mother1[9];
	
	number2 += 1111*mother2[2] + 2222*mother2[3] + 3333*mother2[4] + 4444*mother2[5] +
		5555*mother2[6] + 6666*mother2[7] + 7777*mother2[8] + 9272*mother2[9];

	// Save the high bits of numberi as the new carry
	mother1[0] = (short) (number1 / m16Long);
	mother2[0] = (short) (number2 / m16Long);

	// Put the low bits of numberi into motheri[1]
	mother1[1] = m16Mask & number1;
	mother2[1] = m16Mask & number2;

	// Combine the two 16 bit random numbers into one 32 bit
	*s = (((long)mother1[1]) << 16) + (long)mother2[1];

	// Return a float value between 0 and 1
	return ((float)*s) / m32Float;
}