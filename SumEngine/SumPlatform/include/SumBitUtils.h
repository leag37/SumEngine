//*************************************************************************************************
// Title: SumBitUtils.h
// Author: Gael Huber
// Description: A series of bit utility functions
//*************************************************************************************************
#ifndef __SUMBITUTILS_H__
#define __SUMBITUTILS_H__

#include "SumPlatform.h"

// Reverse the bits in an int
SUCHAR ReverseBits(SUINT* mask);
SUCHAR ReverseBits64(SUINT64* mask);

// Returns the index of the least significant 'on' bit
SUCHAR ForwardBitScan(SUINT* index, SUINT mask);
SUCHAR ForwardBitScan64(SUINT* index, SUINT64 mask);

// Returns the index of the most significant 'on' bit
SUCHAR ReverseBitScan(SUINT* index, SUINT mask);
SUCHAR ReverseBitScan64(SUINT* index, SUINT64 mask);

// Count the number of trailing zeros
SUCHAR CountTrailingZeros(SUINT* zeros, SUINT mask);
SUCHAR CountTrailingZeros64(SUINT* zeros, SUINT64 mask);

// Count the number of leading zeros
SUCHAR CountLeadingZeros(SUINT* zeros, SUINT mask);
SUCHAR CountLeadingZeros64(SUINT* zeros, SUINT64 mask);

#endif	// __SMBITUTILS_H__
