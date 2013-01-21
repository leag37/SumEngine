//*************************************************************************************************
// Title: SumRenderWindow.h
// Author: Gael Huber
// Description: Maintains a physical window for the client to attach the render context.
//*************************************************************************************************
#ifndef __SUMRENDERWINDOW_H__
#define __SUMRENDERWINDOW_H__

#include "SumInclude.h"

class RenderWindow
{
public:
	// Constructor
	RenderWindow(SUINT clientWidth, SUINT clientHeight);

	// Destructor
	~RenderWindow();

	// Process a Windows message
	LRESULT processMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	// Window handle
	HWND _clientWindow;

	// Client width
	SUINT _clientWidth;

	// Client height
	SUINT _clientHeight;

	// Is the window active?
	SBOOL _windowActive;

// Inline functions
public:
	SUMINLINE SUINT clientWidth() const
	{
		return _clientWidth;
	}

	SUMINLINE SUINT clientHeight() const
	{
		return _clientHeight;
	}
};

#endif