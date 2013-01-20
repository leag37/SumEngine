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
	RenderWindow(SINT clientWidth, SINT clientHeight);

	// Destructor
	~RenderWindow();

private:
	// Client width
	SINT _clientWidth;

	// Client height
	SINT _clientHeight;

	// Is the window active?
	SBOOL _windowActive;
};

#endif