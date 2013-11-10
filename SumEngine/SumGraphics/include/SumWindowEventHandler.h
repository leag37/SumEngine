//*************************************************************************************************
// Title: SumWindowEventHandler.h
// Author: Gael Huber
// Description: Class for handling standard window events and message pump.
//*************************************************************************************************
#ifndef __SUMWINDOWEVENTHANDLER_H__
#define __SUMWINDOWEVENTHANDLER_H__

#include "SumRenderCore.h"
#include "SumRenderWindow.h"

namespace SumEngine
{
	/** \addtogroup Rendering
	*	@{
	*/

	class WindowEventHandler
	{
	public:
		/** Add a render window to the event handler system
		* @param
		*	renderWindow The render window to be added
		*/
		static void addRenderWindow(RenderWindow* window);

#ifdef WIN32
		/** WndProc handler for windows 
		*/
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif

	private:
		/** Active window listening to events
		*/
		static RenderWindow* _activeWindow;
	};

	/** @} */

}	// Namespace

#endif // __SUMWINDOWEVENTHANDLER_H__