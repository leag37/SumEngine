//*************************************************************************************************
// Title: SumRenderWindow.cpp
// Author: Gael Huber
// Description: Maintains a physical window for the client to attach the render context.
//*************************************************************************************************
#include "SumRenderWindow.h"

namespace SumEngine
{
	//*************************************************************************************************
	// Default constructor
	//*************************************************************************************************
	RenderWindow::RenderWindow()
	{ }

	//*************************************************************************************************
	// Destructor
	//*************************************************************************************************
	RenderWindow::~RenderWindow()
	{ }

}	// Namespace

//namespace
//{
//	// Use this to foward windows messages from a global function to a local one
//	RenderWindow* gRenderWindow = 0;
//}
//
//// Window process handler
//LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	return gRenderWindow->processMessage(hWnd, msg, wParam, lParam);
//}
//
////*************************************************************************************************
//// Constructor
////*************************************************************************************************
//RenderWindow::RenderWindow(SUINT clientWidth, SUINT clientHeight)
//	:	_clientWindow(0), 
//		_clientWidth(clientWidth), 
//		_clientHeight(clientHeight), 
//		_windowActive(false)
//{
//	// Set pointer to Window
//	gRenderWindow = this;
//	
//	// Initialize the window
//	WNDCLASS wc;
//	wc.style = CS_HREDRAW | CS_VREDRAW;
//	wc.lpfnWndProc = MainWndProc;
//	wc.cbClsExtra = 0;
//	wc.cbWndExtra = 0;
//	wc.hInstance = gHInstance;//GetModuleHandle(0);
//	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
//	wc.hCursor = LoadCursor(0, IDC_ARROW);
//	wc.hbrBackground = (HBRUSH) GetStockObject(NULL_BRUSH);
//	wc.lpszMenuName = 0;
//	wc.lpszClassName = "SumRenderWindowClass";
//
//	if(!RegisterClass(&wc))
//	{
//		MessageBox(0, "RegisterClass failed", 0, 0);
//		return;
//	}
//
//	// Compute window rectangle dimensions based on requested client area dimensions
//	RECT r = {0, 0, _clientWidth, _clientHeight};
//	AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, false);
//	int width = r.right - r.left;
//	int height = r.bottom - r.top;
//
//	_caption = "SumEngine v0.0.1";
//
//	_clientWindow = CreateWindow(
//		wc.lpszClassName,
//		LPCSTR(_caption.c_str()),
//		WS_OVERLAPPEDWINDOW,
//		CW_USEDEFAULT,
//		CW_USEDEFAULT,
//		width,
//		height,
//		0,
//		0,
//		wc.hInstance,
//		0
//		);
//	if(!_clientWindow)
//	{
//		MessageBox(0, "CreateWindow failed", 0, 0);
//		return;
//	}
//
//	gWindowHandle = _clientWindow;
//
//	ShowWindow(_clientWindow, SW_SHOW);
//	UpdateWindow(_clientWindow);
//
//	_windowActive = true;
//}
//
////*************************************************************************************************
//// Destructor
////*************************************************************************************************
//RenderWindow::~RenderWindow()
//{
//
//}
//
////*************************************************************************************************
//// Process a Windows message
////*************************************************************************************************
//LRESULT RenderWindow::processMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	switch(msg)		
//	{
//	// The window is being destroyed, quit application
//	case WM_DESTROY:
//		// Send message to quit application
//		PostQuitMessage(0);
//
//		// Destroy window function
//		gCanRun = false;
//		
//		return 0;
//	}
//
//	// Return default process
//	return DefWindowProc(hWnd, msg, wParam, lParam);
//}