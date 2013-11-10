//*************************************************************************************************
// Title: SumRenderWindow.h
// Author: Gael Huber
// Description: Maintains a physical window for the client to attach the render context.
//*************************************************************************************************
#ifndef __SUMRENDERWINDOW_H__
#define __SUMRENDERWINDOW_H__

#include "SumInclude.h"
#include "SumString.h"

namespace SumEngine
{
	/** \addtogroup Rendering
	 *	@{
	 */

	class RenderWindow
	{
	public:
		/** Default constructor
		*/
		RenderWindow();

		/** Destructor
		*/
		virtual ~RenderWindow();

		/** Initializes the window
		* @param
		*	name The name of the window
		* @param
		*	width The width of the window resolution
		* @param
		*	height The window height
		* @param
		*	fullscreen The window will be created in fullscreen if true
		*/
		virtual void create(const String& name, SUINT width, SUINT height, SBOOL fullscreen) = 0;

		/** Destroy the window
		*/
		virtual void destroy() = 0;

		/** Change the window position
		* @param
		*	x The x position of the window's top-left corner
		* @param
		*	y The y position of the window's top-left corner
		*/
		virtual void setPosition(SUINT x, SUINT y) = 0;

		/** Change the window's fullscreen parameter and adjust as necessary
		* @param
		*	fullscreen Set the window to fullscreen if true, windowed if false
		*/
		virtual void setFullscreen(SBOOL fullscreen) = 0;

		/** Get an attribute of the render window
		* @param
		*	attribute A pointer to the desired class type
		* @param 
		*	data Pointer to the data being retrieved
		*/
		virtual void getAttribute(SUINT attribute, void* data) = 0;

		/** Swap the buffers for the window
		*/
		virtual void swapBuffers() = 0;

	protected:
		/** Name of this window 
		*/
		String _name;

		/** Width of the window 
		*/
		SUINT _width;

		/** Height of the window 
		*/
		SUINT _height;

		/** Is the window fullscreen 
		*/
		SBOOL _isFullscreen;

		/** X position of the window 
		*/
		SUINT _x;

		/** Y position of the window 
		*/
		SUINT _y;
	};

	/** @} */

}	// Namespace

#endif	// __SUMRENDERWINDOW_H__