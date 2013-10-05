//*************************************************************************************************
// Title: SumPhysicsCollisionTestJob.cpp
// Author: Gael Huber
// Description: We have determined that a pair might be colliding, so a test must be performed to
//	determine whether there is actually a collision state or whether this test can be safely 
//	ignored.
//*************************************************************************************************
#include "SumPhysicsCollisionTestJob.h"

//*************************************************************************************************
// Constructor
//*************************************************************************************************
PhysicsCollisionTestJob::PhysicsCollisionTestJob(Delegate2<PhysicsBody*, PhysicsBody*> inProcessor, PhysicsBody* inA, PhysicsBody* inB)
	:	PhysicsJob(), _processor(inProcessor), _bodyA(inA), _bodyB(inB)
{
}

//*************************************************************************************************
//*************************************************************************************************
// Copy constructor
PhysicsCollisionTestJob::PhysicsCollisionTestJob(const PhysicsCollisionTestJob& value)
	:	PhysicsJob(), _processor(value._processor), _bodyA(value._bodyA), _bodyB(value._bodyB)
{
}

//*************************************************************************************************
// Execute the function
//*************************************************************************************************
void PhysicsCollisionTestJob::execute()
{
	_processor(_bodyA, _bodyB);
}