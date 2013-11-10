//*************************************************************************************************
// Title: SumWindowEventHandler.cpp
// Author: Gael Huber
// Description: Class for handling standard window events and message pump.
//*************************************************************************************************
#include "SumWindowEventHandler.h"

namespace SumEngine
{
	/** Active window listening to events
	*/
	RenderWindow* WindowEventHandler::_activeWindow = 0;

	void WindowEventHandler::addRenderWindow(RenderWindow* window)
	{
		// TODO: Make this an actual list
		_activeWindow = window;
	}

#ifdef WIN32
	LRESULT CALLBACK WindowEventHandler::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		// If we are creating this window, store the pointer to the user data area for Win32Window
		if(msg == WM_CREATE)
		{
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)(((LPCREATESTRUCT)lParam)->lpCreateParams));
		}

		// Look up the window instance
		// Note that it's possible to get WM_SIZE before WM_CREATE
		RenderWindow* win = reinterpret_cast<RenderWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		if(!win)
		{
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}

		// Process messages	
		switch(msg)
		{
		// The window is destroyed, quit application
		case WM_DESTROY:
			// Send quit message to application
			PostQuitMessage(0);

			// Initiate shutdown
			gCanRun = false;

			return 0;
		}
		
		// Default process
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
#endif
}	// Namespace