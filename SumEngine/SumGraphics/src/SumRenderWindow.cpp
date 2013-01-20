//*************************************************************************************************
// Title: SumRenderWindow.cpp
// Author: Gael Huber
// Description: Maintains a physical window for the client to attach the render context.
//*************************************************************************************************
#include "SumRenderWindow.h"

// Window process handler

//*************************************************************************************************
// Constructor
//*************************************************************************************************
RenderWindow::RenderWindow(SINT clientWidth, SINT clientHeight)
	: _clientWidth(clientWidth), _clientHeight(clientHeight)
{

}

//*************************************************************************************************
// Destructor
//*************************************************************************************************
RenderWindow::~RenderWindow()
{

}
