//*************************************************************************************************
// Title: SumMovableEntity.h
// Author: Gael Huber
// Description: A movable entity. This means the entity must have a physics component associated
//	with it.
//*************************************************************************************************
#ifndef __SUMMOVABLEENTITY_H__
#define __SUMMOVABLEENTITY_H__

#include "SumEntity.h"
#include "SumPhysicsBody.h"

class MovableEntity : public Entity
{
public:
	// Constructor
	MovableEntity();

	// Constructor from name
	MovableEntity(const String& name, const String& assetName);

	// Destructor
	virtual ~MovableEntity();

	// Retrieve the physics body
	PhysicsBody* getPhysicsBody() const;

	// Set the position
	virtual void setPosition(SFLOAT x, SFLOAT y, SFLOAT z);

private:
	// Physics object
	PhysicsBody* _physicsBody;
};

#endif // __SUMMOVABLEENTITY_H__