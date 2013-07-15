//*************************************************************************************************
// Title: SumEntity.h
// Author: Gael Huber
// Description: Sum Engine entity. Contains basic components for any object in the system. Every
//	entity in the system must at least have a Renderable component.
//*************************************************************************************************
#ifndef __SUMENTITY_H__
#define __SUMENTITY_H__

#include "SumInclude.h"
#include "SumRenderable.h"
#include "SumString.h"

class Entity
{
public:
	// Constructor
	Entity();

	// Constructor from name
	Entity(const String& name, const String& assetName);

	// Destructor
	virtual ~Entity();

	// Name
	const String& name();

	// Renderable
	Renderable* renderable();

protected:
	// Entity name
	String _name;

	// Renderable component
	Renderable* _renderable;
};

#endif // __SUMENTITY_H__