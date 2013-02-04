/**************************************************************************************************
* Title: SumHashMapFunctions.cpp
* Author: Gael Huber
* Description: Contains various hash functions to be used for hash map. A given number of these
*	will be chosen randomly at start up to help evenly distribute hash map behavior.
**************************************************************************************************/
#include "SumHashMap.h"

/**************************************************************************************************
* Hash function created by Robert Sedgwicks
**************************************************************************************************/
unsigned int RSHash(const char* str) {
	unsigned int b = 378551;
	unsigned int a = 63689;
	unsigned int hash = 0;
	unsigned int length = std::strlen(str);

	for(unsigned int i = 0; i < length; ++i) {
		hash = hash*a + str[i];
		a *= b;
	}
	return hash;
}

/**************************************************************************************************
* Bitwise hash function created by Justin Sobel
**************************************************************************************************/
unsigned int JSHash(const char* str) {
	unsigned int length = std::strlen(str);
	unsigned int hash = 1315423911;

	for(unsigned int i = 0; i < length; ++i) {
		hash ^= ((hash << 5) + str[i] + (hash >> 2));
	}

	return hash;
}

/**************************************************************************************************
* Hash algorithm developed by Peter J. Weinberger
**************************************************************************************************/
unsigned int PJWHash(const char* str) {
	unsigned int bitsInUnsignedInt = (unsigned int) (sizeof(unsigned int) * 8);
	unsigned int threeQuarters = (unsigned int) ((bitsInUnsignedInt * 3) / 4);
	unsigned int oneEighth = (unsigned int) (bitsInUnsignedInt / 8);
	unsigned int highBits = (unsigned int) (0xFFFFFFFF) << (bitsInUnsignedInt - oneEighth);
	unsigned int hash = 0;
	unsigned int test = 0;
	unsigned int length = std::strlen(str);

	for(unsigned int i = 0; i < length; ++i) {
		hash = (hash << oneEighth) + str[i];

		if((test = hash & highBits) != 0) {
			hash = ((hash ^ (test >> threeQuarters)) & (~highBits));
		}
	}

	return hash;
}

/**************************************************************************************************
* PJW hash tweaked for 32 bit processors
**************************************************************************************************/
unsigned int ELFHash(const char* str) {
	unsigned int hash = 0;
	unsigned int x = 0;
	unsigned int length = std::strlen(str);

	for(unsigned int i = 0; i < length; ++i) {
		hash = (hash << 4) + str[i];
		if((x = hash & 0xF0000000L) != 0) {
			hash ^= (x >> 24);
		}
		hash &= ~x;
	}

	return hash;
}

/**************************************************************************************************
* Hash function developed by Brian Kernighan and Dennis Ritchie
**************************************************************************************************/
unsigned int BKDRHash(const char* str) {
	unsigned int seed = 131;
	unsigned int hash = 0;
	unsigned int length = std::strlen(str);

	for(unsigned int i = 0; i < length; ++i) {
		hash = (hash * seed) + str[i];
	}

	return hash;
}

/**************************************************************************************************
* Hash function used in SDBM open source project
**************************************************************************************************/
unsigned int SDBMHash(const char* str) {
	unsigned int hash = 0;
	unsigned int length = std::strlen(str);

	for(unsigned int i = 0; i < length; ++i) {
		hash = str[i] + (hash << 6) + (hash << 16) - hash;
	}

	return hash;
}

/**************************************************************************************************
* Hash function developed by Daniel J. Bernstein
**************************************************************************************************/
unsigned int DJBHash(const char* str) {
	unsigned int hash = 5381;
	unsigned int length = std::strlen(str);

	for(unsigned int i = 0; i < length; ++i) {
		hash = ((hash << 5) + hash) + str[i];
	}
	
	return hash;
}

/**************************************************************************************************
* Hash function developed by Donald E. Knuth
**************************************************************************************************/
unsigned int DEKHash(const char* str) {
	unsigned int hash = std::strlen(str);
	unsigned int length = hash;

	for(unsigned int i = 0; i < length; ++i) {
		hash = ((hash << 5) ^ (hash >> 27)) ^ str[i];
	}

	return hash;
}

/**************************************************************************************************
* BP hash function
**************************************************************************************************/
unsigned int BPHash(const char* str) {
	unsigned int hash = 0;
	unsigned int length = std::strlen(str);

	for(unsigned int i = 0; i < length; ++i) {
		hash = hash << 7 ^ str[i];
	}

	return hash;
}

/**************************************************************************************************
* FNV hash function
**************************************************************************************************/
unsigned int FNVHash(const char* str) {
	const unsigned int fnvPrime = 0x811C9DC5;
	unsigned int hash = 0;
	unsigned int length = std::strlen(str);

	for(unsigned int i = 0; i < length; ++i) {
		hash *= fnvPrime;
		hash ^= str[i];
	}

	return hash;
}

/**************************************************************************************************
* Hash function developed by Arash Partow
**************************************************************************************************/
unsigned int APHash(const char* str) {
	unsigned int hash = 0xAAAAAAAA;
	unsigned int length = std::strlen(str);

	for(unsigned int i = 0; i < length; ++i) { 
		hash ^= ((i & 1) == 0) ? 
			((hash << 7) ^ str[i] * (hash >> 3)) :
			(~((hash << 11) + (str[i] ^ (hash >> 5))));
	}

	return hash;
}