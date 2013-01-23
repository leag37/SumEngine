//*************************************************************************************************
// Title: SumRenderManager.h
// Author: Gael Huber
// Description: Render manager. Keeps track of various effects, renderable objects, and scene
//	graphs.
//*************************************************************************************************
#include "SumRenderManager.h"

//*************************************************************************************************
// Constructor
//*************************************************************************************************
RenderManager::RenderManager()
	:	_renderContext(0),
		_renderWindow(0),
		_renderViewport(0)
{

}

//*************************************************************************************************
// Destructor
//*************************************************************************************************
RenderManager::~RenderManager()
{ }

//*************************************************************************************************
// Initialize render manager
//*************************************************************************************************
void RenderManager::startUp()
{
	// Initialize the three primary components
	_renderWindow = new RenderWindow(400, 600);
	_renderContext = new RenderContext(_renderWindow->clientHandle(), _renderWindow->clientWidth(), _renderWindow->clientHeight());
	_renderViewport = new RenderViewport();
	_renderViewport->configure(_renderContext, _renderWindow);
}

//*************************************************************************************************
// Shut down the render manager
//*************************************************************************************************
void RenderManager::shutDown()
{
	SafeDelete(_renderContext);
	SafeDelete(_renderWindow);
	SafeDelete(_renderViewport);
}

//*************************************************************************************************
// Update the manager
//*************************************************************************************************
void RenderManager::update()
{

}

//*************************************************************************************************
// Render the current scene
//*************************************************************************************************
void RenderManager::renderScene()
{

}

