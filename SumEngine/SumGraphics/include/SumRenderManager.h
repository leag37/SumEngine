//*************************************************************************************************
// Title: SumRenderManager.h
// Author: Gael Huber
// Description: Render manager. Keeps track of various effects, renderable objects, and scene
//	graphs.
//
// Notes:
// RenderContext -> Device and swap chain info
// SceneGraph -> Scene graph information for render objects
// ClientWindow -> Physical application window
// RenderViewport -> Contains the viewport and manages draw buffers, etc.
// EffectsManager -> Manages all active effects
// LightManager -> Manages all lighting effects
//
// TODO: Read configuration file and initialize based on RenderConfig
// TODO: Add debugging information to the top of the window
// TODO: Add actual camera for register camera
//*************************************************************************************************
#ifndef __SUMRENDERMANAGER_H__
#define __SUMRENDERMANAGER_H__

#include "SumRenderCore.h"
#include "SumRenderContext.h"
#include "SumRenderWindow.h"
#include "SumRenderViewport.h"
#include "SumEffectsManager.h"
#include "SumInputLayout.h"
#include "SumConfigurationManager.h"
#include "SumResourceManager.h"

class RenderManager : public Singleton<RenderManager>
{
public:
	// Constructor
	RenderManager();

	// Destructor
	~RenderManager();

	// Singleton
	SUMINLINE static RenderManager& getSingleton()
	{
		assert(singleton);
		return *singleton;
	}

	SUMINLINE static RenderManager* getSingletonPtr()
	{
		return singleton;
	}

	// Initialize render manager
	void startUp();

	// Shut down the render manager
	void shutDown();

	// Update the manager
	void update();

	// Register a camera
	void registerCamera(const Matrix& camera);

private:
	// Render the current scene
	void renderScene();

private:
	// Render context
	RenderContext* _renderContext;

	// Render window
	RenderWindow* _renderWindow;

	// Render viewport
	RenderViewport* _renderViewport;

	// Effects manager
	EffectsManager* _effectsManager;

	// TEMP
	Renderable* _renderable;
	Float4x4 _view;
	Float4x4 _proj;
	Float3 _eyePosW;
	SFLOAT _theta;
	SFLOAT _phi;
	SFLOAT _radius;

// Inline accessor functions
public:
	SUMINLINE ID3D11Device* d3dDevice() const
	{
		return _renderContext->d3dDevice();
	}

	// Return the current window handle
	SUMINLINE HWND handle() const
	{
		return _renderWindow->clientHandle();
	}
};

#endif