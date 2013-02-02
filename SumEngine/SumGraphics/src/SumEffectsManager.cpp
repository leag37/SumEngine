#include "SumEffectsManager.h"

//*************************************************************************************************
// Initialize the singleton instance of this class to 0
//*************************************************************************************************
template <> EffectsManager* Singleton<EffectsManager>::singleton = 0;

// Construtor
EffectsManager::EffectsManager(){}

	// Destructor
EffectsManager::~EffectsManager(){}