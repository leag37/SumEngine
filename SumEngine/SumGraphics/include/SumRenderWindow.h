//*************************************************************************************************
// Title: SumRenderWindow.h
// Author: Gael Huber
// Description: Maintains a physical window for the client to attach the render context.
//*************************************************************************************************
#ifndef __SUMRENDERWINDOW_H__
#define __SUMRENDERWINDOW_H__

#include "SumInclude.h"
#include "SumString.h"

// Temp
#include <sstream>
#include <iostream>

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

	// Window caption
	String _caption;

// Inline functions
public:
	// Get the window handle
	SUMINLINE HWND clientHandle() const
	{
		return _clientWindow;
	}

	// Get the client width
	SUMINLINE SUINT clientWidth() const
	{
		return _clientWidth;
	}

	// Get the client height
	SUMINLINE SUINT clientHeight() const
	{
		return _clientHeight;
	}

	// Return whether or not the window is active
	SUMINLINE SBOOL windowActive() const
	{
		return _windowActive;
	}

	// Get the aspect ratio
	SUMINLINE SFLOAT aspectRatio() const
	{
		return static_cast<float>(_clientWidth) / _clientHeight;
	}

	// Return the window caption
	SUMINLINE const String& caption() const
	{
		return _caption;
	}
};

#endif