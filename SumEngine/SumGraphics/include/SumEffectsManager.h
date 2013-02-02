//*************************************************************************************************
// Title: SumEffectsManager.h
// Author: Gael Huber
// Description: Manages lifecycle of all rendering effects.
//*************************************************************************************************
#ifndef __SUMEFFECTSMANAGER_H__
#define __SUMEFFECTSMANAGER_H__

#include "SumRenderCore.h"

// TEMPORARY
#include <unordered_map>

class EffectsManager : public Singleton<EffectsManager>
{
public:
	// Construtor
	EffectsManager();

	// Destructor
	~EffectsManager();

	// Start up the effects
	void startUp();

	// Shut down the effects
	void shutDown();

private:
	// TEMP: map of effects
	std::unordered_map<std::string, Effect*> _effects;

// Inline functions
public:
	// Singleton instance
	SUMINLINE static EffectsManager& getSingleton()
	{
		assert(singleton);
		return *singleton;
	}

	// Singleton pointer
	SUMINLINE static EffectsManager* getSingletonPtr()
	{
		return singleton;
	}
};

#endif
