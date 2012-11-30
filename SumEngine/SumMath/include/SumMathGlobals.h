//*************************************************************************************************
// Title: SumMathGlobals.h
// Author: Gael Huber
// Description: Mathematical global constants.
//*************************************************************************************************
#ifndef __SUMMATHGLOBALS_H__
#define __SUMMATHGLOBALS_H__

#include "SumMath.h"

// Vector
//***********************************************

SUMGLOBALCONST VectorF32 gVEpsilon = {1.192092896e-7f, 1.192092896e-7f, 1.192092896e-7f, 1.192092896e-7f};
SUMGLOBALCONST VectorI32 gVInfinity = {0x7F800000, 0x7F800000, 0x7F800000, 0x7F800000};
SUMGLOBALCONST VectorI32 gVQNaN = {0x7FC00000, 0x7FC00000, 0x7FC00000, 0x7FC00000};

// Matrix
//***********************************************

SUMGLOBALCONST VectorF32 gVIdentityR0 = {1.0f, 0.0f, 0.0f, 0.0f};
SUMGLOBALCONST VectorF32 gVIdentityR1 = {0.0f, 1.0f, 0.0f, 0.0f};
SUMGLOBALCONST VectorF32 gVIdentityR2 = {0.0f, 0.0f, 1.0f, 0.0f};
SUMGLOBALCONST VectorF32 gVIdentityR3 = {0.0f, 0.0f, 0.0f, 1.0f};
SUMGLOBALCONST VectorF32 gVDeterminantNegate = {1.0f, -1.0f, 1.0f, -1.0f};

// Shuffles
//***********************************************
SUMGLOBALCONST SUINT gVShuffleXXXX = _MM_SHUFFLE(1, 1, 1, 1);
SUMGLOBALCONST SUINT gVShuffleYXXX = _MM_SHUFFLE(2, 1, 1, 1);
SUMGLOBALCONST SUINT gVShuffleYYYY = _MM_SHUFFLE(2, 2, 2, 2);
SUMGLOBALCONST SUINT gVShuffleZZYY = _MM_SHUFFLE(3, 3, 2, 2);
SUMGLOBALCONST SUINT gVShuffleZZZZ = _MM_SHUFFLE(3, 3, 3, 3);
SUMGLOBALCONST SUINT gVShuffleWWWZ = _MM_SHUFFLE(4, 4, 4, 3);
SUMGLOBALCONST SUINT gVShuffleWWWW = _MM_SHUFFLE(4, 4, 4, 4);


#endif