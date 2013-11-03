//*************************************************************************************************
// Title: SumPhysicsBody.cpp
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
#include "SumPhysicsBody.h"

//*************************************************************************************************
// Constructor for physics body
//*************************************************************************************************
PhysicsBody::PhysicsBody()
	:	_renderable(0), _position(gVZero), _orientation(gVIdentity)
{

}

//*************************************************************************************************
// Constructor with pointer to renderable. All relevant information about the body will be assembled via the renderable data.
//*************************************************************************************************
PhysicsBody::PhysicsBody(Renderable* inRenderable)
	:	_renderable(inRenderable), _position(gVZero), _orientation(gVIdentity)
{
	init();
}

//*************************************************************************************************
// Copy constructor
//*************************************************************************************************
PhysicsBody::PhysicsBody(const PhysicsBody& value)
	:	_renderable(value._renderable), _position(value._position), _orientation(value._orientation),
		_aabb(value._aabb)
{ }

//*************************************************************************************************
// Destructor
//*************************************************************************************************
PhysicsBody::~PhysicsBody()
{
	_renderable = 0;
}

//*************************************************************************************************
// Initialize the bounding volumes
//*************************************************************************************************
void PhysicsBody::init()
{
	// Run through the vertices of renderable
	if(_renderable == 0)
	{
		return;
	}

	// Get the mesh data
	const MeshData& data = _renderable->mesh()->getMeshData();
	
	// Initialize max values
	SFLOAT maxX = 0.0f, maxY = 0.0f, maxZ = 0.0f;

	Array<Vertex>::Iterator endItr = data.vertices.end();
	for(Array<Vertex>::Iterator itr = data.vertices.begin(); itr != endItr; ++itr)
	{
		Vertex v = *itr;
		if(abs(v.position().x) > maxX)
		{
			maxX = abs(v.position().x);
		}
		if(abs(v.position().y) > maxY)
		{
			maxY = abs(v.position().y);
		}
		if(abs(v.position().z) > maxZ)
		{
			maxZ = abs(v.position().z);
		}
	}

	// XYZ max are the extrema
	_aabb = AxisAlignedBox(_position, VectorSet(maxX, maxY, maxZ, 0.0f));
}

//*************************************************************************************************
// Update the box based on its updated mesh
//*************************************************************************************************
void PhysicsBody::update()
{
	// Ensure the position of the AABB matches the position of the renderable
	_aabb.update(_renderable->world().r[3], QuaternionRotationMatrix(_renderable->world()));
}

//*************************************************************************************************
// Get the body's axis aligned box
//*************************************************************************************************
const AxisAlignedBox& PhysicsBody::getAABB()
{
	return _aabb;
}
