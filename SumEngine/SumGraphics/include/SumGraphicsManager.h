//*************************************************************************************************
// Title: SumGraphicsManager.h
// Author: Gael Huber
// Description: Graphics manager. Keeps track of various effects, renderable objects, and scene
//	graphs.
//*************************************************************************************************
#ifndef __SUMGRAPHICSMANAGER_H__
#define __SUMGRAPHICSMANAGER_H__

#include <SumIncludes.h>
#include "SumRenderContext.h"

class GraphicsManager : public Singleton<GraphicsManager>
{
public:
	// Constructor
	GraphicsManager();

	// Destructor
	~GraphicsManagr();

	// Singleton
	SUMINLINE static GraphicsManager& getSingleton()
	{
		assert(singleton);
		return *singleton;
	}

	SUMINLINE static GraphicsManager* getSingletonPtr()
	{
		return singleton;
	}

	// Initialize render manager
	void startUp();

	// Shut down the render manager
	void shutDown();

	// Update the manager
	void update();

private:
	// Render the current scene
	void renderScene();

private:
	// Render context
	RenderContext* _renderContext;
};

#endif