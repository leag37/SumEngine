//*************************************************************************************************
// Title: SumRenderManager.h
// Author: Gael Huber
// Description: Render manager. Keeps track of various effects, renderable objects, and scene
//	graphs.
//*************************************************************************************************
#include "SumRenderManager.h"

//*************************************************************************************************
// Initialize the singleton instance of this class to 0
//*************************************************************************************************
template <> RenderManager* Singleton<RenderManager>::singleton = 0;

//*************************************************************************************************
// Constructor
//*************************************************************************************************
RenderManager::RenderManager()
	:	_renderContext(0),
		_renderWindow(0),
		_renderViewport(0),
		_effectsManager(0)
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
	// Get width and height
	Configuration* config = ConfigurationManager::getSingletonPtr()->getConfiguration("Engine");
	SUINT width = config->retrieveValue("width").toUInt();
	SUINT height = config->retrieveValue("height").toUInt();

	// Initialize the three primary components
	_renderWindow = new RenderWindow(width, height);
	_renderContext = new RenderContext(_renderWindow->clientHandle(), _renderWindow->clientWidth(), _renderWindow->clientHeight());
	_renderViewport = new RenderViewport();
	_renderViewport->configure(_renderContext, _renderWindow);

	// Initialize the effects manager
	_effectsManager = new EffectsManager();
	_effectsManager->startUp(_renderContext->d3dDevice());
	InputLayouts::InitAll(_renderContext->d3dDevice());
}

//*************************************************************************************************
// Shut down the render manager
//*************************************************************************************************
void RenderManager::shutDown()
{
	SafeDelete(_effectsManager);

	SafeDelete(_renderContext);
	SafeDelete(_renderWindow);
	SafeDelete(_renderViewport);
}

//*************************************************************************************************
// Update the manager
//*************************************************************************************************
void RenderManager::update()
{
	// TODO: Prune the scene and update draw list

	// TODO: Update any effects

	// Render the scene
	renderScene();
}

//*************************************************************************************************
// Render the current scene
//*************************************************************************************************
void RenderManager::renderScene()
{
	// Clear the viewports
	_renderViewport->clearViewport(_renderContext);
	
	// Present the swap chain
	HR(_renderContext->swapChain()->Present(0, 0));
}

