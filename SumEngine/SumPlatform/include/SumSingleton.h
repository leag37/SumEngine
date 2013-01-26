//*************************************************************************************************
// Title: SumSingleton.h
// Authors: Gael Huber
// Description: Interface for singleton pattern.
//*************************************************************************************************
#ifndef __SUMSINGLETON_H__
#define __SUMSINGLETON_H__

#include <assert.h>
#include "SumPlatform.h"

template <typename T> class Singleton {
public:
	// Constructor implemented locally
	SUMINLINE Singleton(void) {
		// Ensure the singleton does not already exist
		assert(!singleton);
		singleton = static_cast<T*> (this);
	};

	// Deconstructor implemented locally
	SUMINLINE ~Singleton(void) {
		// Ensure the singleton exists
		assert(singleton);
		singleton = 0;
	};

	// Get the singleton instance
	SUMINLINE static T& getSingleton(void) {
		// Return the instance if it exists
		assert(singleton);
		return *singleton;
	};

	// Get the singleton pointer
	SUMINLINE static T* getSingletonPtr() {
		return singleton;
	};

protected:
	static T* singleton;

private:
	Singleton(const Singleton<T> &);

	// Used to internally assign singleton value to class value
	Singleton& operator=(const Singleton<T> &);
};

#endif