//*************************************************************************************************
// Title: SumGraphicsManager.h
// Author: Gael Huber
// Description: Graphics manager. Keeps track of various effects, renderable objects, and scene
//	graphs.
//*************************************************************************************************
#ifndef __SUMGRAPHICSMANAGER_H__
#define __SUMGRAPHICSMANAGER_H__

#include <SumIncludes.h>

class GraphicsManager : public Singleton<GraphicsManager>
{
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
};

#endif