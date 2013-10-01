//*************************************************************************************************
// Title: SumPhysicsBody.h
// Author: Gael Huber
// Description: A basic physics body. All physical bodies will inherit from this base type. 
//	Physical bodies have the following properties:
//	1) Position
//	2) Linear velocity
//	3) Linear acceleration
//	4) Angular velocity
//	5) Angular acceleration
//	6) Axis Aligned Bounding Box
//	7) Oriented Bounding Box
//	8) Complex polyhedra
//
//	From this, we can have rigid bodies, deformable bodies, etc.
//*************************************************************************************************
#ifndef __SUMPHYSICSBODY_H__
#define __SUMPHYSICSBODY_H__

#include "SumInclude.h"
#include "SumMath.h"
#include "SumAxisAlignedBox.h"
#include "SumRenderable.h"

class SUM_DECLSPEC_ALIGN_16 PhysicsBody
{
public:
	_SUM_ALIGN(PhysicsBody);

	// Constructor for physics body
	PhysicsBody();

	// Constructor with pointer to renderable. All relevant information about the body will be assembled via the renderable data.
	PhysicsBody(Renderable* inRenderable);

	// Copy constructor
	PhysicsBody(const PhysicsBody& value);

	// Destructor
	~PhysicsBody();

	// Update the box based on its updated mesh
	void update();

private:
	// Initialize the bounding volumes
	void init();

private:
	// Pointer to the renderable
	Renderable* _renderable;

	// Position
	Vector _position;

	// Orientation
	Quaternion _orientation;

	// Axis aligned bounding box
	AxisAlignedBox _aabb;
};

#endif // __SUMPHYSICSBODY_H__