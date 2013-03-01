//*************************************************************************************************
// Title: SumGlobals.h
// Author: Gael Huber
// Description: Global variables for the engine.
//
// NOTE: THESE SHOULD ONLY BE USED TEMPORARILY UNTIL ENGINE STATE MACHINE IS IMPLEMENTED
// TODO: Implement a state machine for the engine
//*************************************************************************************************
#ifndef __SUMGLOBALS_H__
#define __SUMGLOBALS_H__

#include "SumPlatform.h"

SUMGLOBAL SBOOL gCanRun = false;

SUMGLOBAL HINSTANCE gHInstance = 0;

SUMGLOBAL HWND gWindowHandle = 0;

#endif