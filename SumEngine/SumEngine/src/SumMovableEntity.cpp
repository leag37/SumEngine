//*************************************************************************************************
// Title: SumMovableEntity.h
// Author: Gael Huber
// Description: A movable entity. This means the entity must have a physics component associated
//	with it.
//*************************************************************************************************
#include "SumMovableEntity.h"

//*************************************************************************************************
// Constructor
//*************************************************************************************************
MovableEntity::MovableEntity()
	: Entity(), _physicsBody(0)
{ }

//*************************************************************************************************
// Constructor from name
//*************************************************************************************************
MovableEntity::MovableEntity(const String& name, const String& assetName)
	: Entity(name, assetName), _physicsBody(0)
{ 
	_renderable = new Renderable(name, assetName);
	_physicsBody = new PhysicsBody(_renderable);
}

//*************************************************************************************************
// Destructor
//*************************************************************************************************
MovableEntity::~MovableEntity()
{ }


//*************************************************************************************************
// Physics body
//*************************************************************************************************
PhysicsBody* MovableEntity::getPhysicsBody() const
{
	return _physicsBody;
}

//*************************************************************************************************
// Set the position
//*************************************************************************************************
void MovableEntity::setPosition(SFLOAT x, SFLOAT y, SFLOAT z)
{
	Entity::setPosition(x, y, z);
	_physicsBody->update();
}
