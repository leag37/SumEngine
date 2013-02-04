/**************************************************************************************************
* Title: SumRandom.h
* Author: Gael Huber
* Description: Implements George Marsaglia's Mother of all RNGs with slight modifications for ease
*	of usability. Core algorithm remains identical.
**************************************************************************************************/
#ifndef __SUMRANDOM_H__
#define __SUMRANDOM_H__

#include <string>
#include <time.h>

static short mother1[10];
static short mother2[10];
static short mStart = 1;
static unsigned long* s;	// Seed value

#define m16Long 65536L			// 2^16
#define m16Mask 0xFFFF			// Mask for lower 16 bits
#define m15Mask 0x7FFF			// Mask for lower 15 bits
#define m31Mask 0x7FFFFFFF		// Mask for lower 15 bits
#define m32Double 4294967295.0	// 2^32 - 1
#define m32Float 4294967295.0f	// 2^32 - 1

/* Mother **************************************************************
|	George Marsaglia's The mother of all random number generators
|		producing uniformly distributed pseudo random 32 bit values 
with
|		period about 2^250.
|	The text of Marsaglia's posting is appended at the end of the function.
|
|	The arrays mother1 and mother2 store carry values in their
|		first element, and random 16 bit numbers in elements 1 to 8.
|		These random numbers are moved to elements 2 to 9 and a new
|		carry and number are generated and placed in elements 0 and 1.
|	The arrays mother1 and mother2 are filled with random 16 bit values
|		on first call of Mother by another generator.  mStart is the 
switch.
|
|	Returns:
|	A 32 bit random number is obtained by combining the output of the
|		two generators and returned in *pSeed.  It is also scaled by
|		2^32-1 and returned as a double between 0 and 1
|
|	SEED:
|	The inital value of *pSeed may be any long value
|
|	Bob Wheeler 8/8/94
*/

void seed(unsigned long pSeed);	// Seed random number generator
void seed(void);	// Seed the random generator with a self-generated value
double nextDouble(void);	// Generate a random double between 0 and 1
float nextFloat(void);	// Generate a random float between 0 and 1

#endif	