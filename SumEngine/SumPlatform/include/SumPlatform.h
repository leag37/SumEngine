//*************************************************************************************************
// Title: SumPlatform.h
// Author: Gael Huber
// Description: Header file containing links to required SumEngine platform commonalities.
//*************************************************************************************************
#ifndef __SUMPLATFORM_H__
#define __SUMPLATFORM_H__

#pragma warning(disable: 4201)

// Exports
//***********************************************
#define SUMEXPORT __declspec (dllexport)

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

typedef bool SBOOL;

typedef unsigned char SUCHAR;
typedef char SCHAR;
typedef wchar_t SWCHAR_T;

// SIMD intrinsics
//***********************************************
#if defined(_M_AMD64) || defined(_AMD64)
#define SUM_X64
#elif defined (_M_IX86) || defined(_X86_)
#define SUM_X86
#endif

#if defined(SUM_X64) || defined(SUM_X86)
#define SUMSIMD
#endif

// Inlining
//***********************************************
#define SUMINLINE_F __forceinline
#define SUMINLINE inline

#define SUMGLOBALCONST	extern const __declspec (selectany)
#define SUMGLOBAL extern __declspec (selectany)
#define SUMEXTERN extern "C++"

// Alignment
//***********************************************
#define SUM_DECLSPEC_ALIGN_16 __declspec(align(16))

// Error checking function
//***********************************************
#if defined(DEBUG) | defined(_DEBUG)
	#include <iostream>
	using namespace std;
	#ifndef HR
	#define HR(x)												\
	{															\
		HRESULT hr = (x);										\
		if(FAILED(hr))											\
		{														\
			cout << __FILE__ << " ; ";							\
			cout << (DWORD)__LINE__ << " ; ";					\
			cout << hr << " ; ";								\
			cout << #x << " ; ";								\
			cout << endl;										\
		}														\
	}
	#endif
//	DXTrace(__FILE__, (DWORD)__LINE__, hr, #x, true);	
#else
	#ifndef HR
	#define HR(x) (x)
	#endif
#endif

// Safe deletion of objects
//***********************************************
#ifndef ReleaseCOM
#define ReleaseCOM(x) { if(x) x->Release(); x = 0; }
#endif

// Callbacks
//***********************************************
#define SUMCALLBACK __stdcall

#endif