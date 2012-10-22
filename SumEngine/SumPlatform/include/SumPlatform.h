//*************************************************************************************************
// Title: SumPlatform.h
// Author: Gael Huber
// Description: Header file containing links to required SumEngine platform commonalities.
//*************************************************************************************************
#ifndef __SUMPLATFORM_H__
#define __SUMPLATFORM_H__

// Exports
//***********************************************
#define _SUMEXPORT __declspec (dllexport)

// Primitive data types typedefs
//***********************************************
typedef unsigned __int8 SUINT8;
typedef __int8 SINT8;
typedef unsigned __int16 SUINT16;
typedef __int16 SINT16;
typedef unsigned __int32 SUINT;
typedef __int32 SINT;
typedef unsigned __int64 SUINT64;
typedef __int64 SINT64;

#ifdef _WIN64
typedef unsigned __int128 SUINT128;
typedef __int128 SINT128;
#endif

typedef float SFLOAT;
typedef double SDOUBLE;

typedef bool SBOOl;

typedef unsigned char SUCHAR;
typedef char SCHAR;
typedef wchar_t SWCHAR_T;

// SIMD intrinsics
//***********************************************
#define _SUMSIMD

#endif