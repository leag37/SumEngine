//*************************************************************************************************
// Title: SumBitUtils.cpp
// Author: Gael Huber
// Description: A series of bit utility functions
//*************************************************************************************************
#include "SumBitUtils.h"

//*************************************************************************************************
// Reverse the bits in an int
// Use the following masks to reverse the bit in a series of steps:
// 01010101010101010101010101010101 = 0x55555555u
// 00110011001100110011001100110011 = 0x33333333u
// 00001111000011110000111100001111 = 0x0f0f0f0fu
// 00000000111111110000000011111111 = 0x00ff00ffu
// 00000000000000001111111111111111 = 0xffffu
//*************************************************************************************************
SUCHAR ReverseBits(SUINT* mask)
{
	*mask = ((*mask >> 1) & 0x55555555u) | ((*mask & 0x55555555u) << 1);	// Reverse order of individual bits (least significant bucket)
	*mask = ((*mask >> 2) & 0x33333333u) | ((*mask & 0x33333333u) << 2);
	*mask = ((*mask >> 4) & 0x0f0f0f0fu) | ((*mask & 0x0f0f0f0fu) << 4);
	*mask = ((*mask >> 8) & 0x00ff00ffu) | ((*mask & 0x00ff00ffu) << 8);
	*mask = ((*mask >> 16) & 0xffffu) | ((*mask & 0xffffu) << 16);			// Finally, swap one half with other half

	return 1;
}

//*************************************************************************************************
// Reverse the bits in an int
//*************************************************************************************************
SUCHAR ReverseBits64(SUINT64* mask)
{
	*mask = ((*mask >> 1) & 0x5555555555555555u) | ((*mask & 0x5555555555555555u) << 1);	// Reverse order of individual bits (least significant bucket)
	*mask = ((*mask >> 2) & 0x3333333333333333u) | ((*mask & 0x3333333333333333u) << 2);
	*mask = ((*mask >> 4) & 0x0f0f0f0f0f0f0f0fu) | ((*mask & 0x0f0f0f0f0f0f0f0fu) << 4);
	*mask = ((*mask >> 8) & 0x00ff00ff00ff00ffu) | ((*mask & 0x00ff00ff00ff00ffu) << 8);
	*mask = ((*mask >> 16) & 0x0000ffff0000ffffu) | ((*mask & 0x0000ffff0000ffffu) << 16);			
	*mask = ((*mask >> 32) & 0xffffffffu) | ((*mask & 0xffffffffu) << 32);					// Finally, swap one half with other half

	return 1;
}

//*************************************************************************************************
// Returns the index of the least significant 'on' bit
// ALGORITHM:
// a
// b = -a
// c = a | b
// shift = ~c
//*************************************************************************************************
SUCHAR ForwardBitScan(SUINT* index, SUINT mask)
{
	// Invalid mask
	if(mask == 0)
	{
		return 0;
	}

	SUINT ind;
	if(mask & 0x1)
	{
		ind = 0;
	}
	else
	{
		ind = 1;
		if((mask & 0xFFFF) == 0)
		{
			mask >>= 16;
			ind += 16;
		}
		if((mask & 0xFF) == 0)
		{
			mask >>= 8;
			ind += 8;
		}
		if((mask & 0xF) == 0)
		{
			mask >>= 4;
			ind += 4;
		}
		if((mask & 0x3) == 0)
		{
			mask >>= 2;
			ind += 2;
		}
		ind -= mask & 0x1;
	}
	*index = ind;
	return 1;
}

//*************************************************************************************************
// Returns the index of the least significant 'on' bit
//*************************************************************************************************
//SUCHAR ForwardBitScan64(SUINT* index, SUINT64 mask);

//*************************************************************************************************
// Returns the index of the most significant 'on' bit
// TODO: Does starting at 31 and using subtraction work?
//*************************************************************************************************
SUCHAR ReverseBitScan(SUINT* index, SUINT mask)
{
	// Invalid mask
	if(mask == 0)
	{
		return 0;
	}

	SUINT ind = 31;
	if(mask <= 0x000FFFF)
	{
		mask <<= 16;
		ind -= 16;
	}
	if(mask <= 0x00FFFFFF)
	{
		mask <<= 8;
		ind -= 8;
	}
	if(mask <= 0x0FFFFFFF)
	{
		mask <<= 4;
		ind -= 4;
	}
	if(mask <=0x3FFFFFFF)
	{
		mask <<= 2;
		ind -= 2;
	}
	if(mask <= 0x7FFFFFFF)
	{
		--ind;
	}
	*index = ind;
	return 1;
}

//*************************************************************************************************
// Returns the index of the most significant 'on' bit
//*************************************************************************************************
//SUCHAR ReverseBitScan64(SUINT* index, SUINT64 mask);

//*************************************************************************************************
// Count the number of trailing zeros
//*************************************************************************************************
//SUCHAR CountTrailingZeros(SUINT* zeros, SUINT mask);

//*************************************************************************************************
// Count the number of trailing zeros
//*************************************************************************************************
//SUCHAR CountTrailingZeros64(SUINT* zeros, SUINT64 mask);

//*************************************************************************************************
// Count the number of leading zeros
//*************************************************************************************************
//SUCHAR CountLeadingZeros(SUINT* zeros, SUINT mask);

//*************************************************************************************************
// Count the number of leading zeros
//*************************************************************************************************
//SUCHAR CountLeadingZeros64(SUINT* zeros, SUINT64 mask);
