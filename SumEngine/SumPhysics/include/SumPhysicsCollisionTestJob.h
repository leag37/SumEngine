//*************************************************************************************************
// Title: SumPhysicsCollisionTestJob.h
// Author: Gael Huber
// Description: We have determined that a pair might be colliding, so a test must be performed to
//	determine whether there is actually a collision state or whether this test can be safely 
//	ignored.
//*************************************************************************************************
#ifndef __SUMPHYSICSCOLLISIONTESTJOB_H__
#define __SUMPHYSICSCOLLISIONTESTJOB_H__

#include "SumPhysicsCore.h"
#include "SumPhysicsJob.h"
#include "SumDelegate.h"

class PhysicsCollisionTestJob : public PhysicsJob
{
public:
	// Constructor
	PhysicsCollisionTestJob(Delegate2<PhysicsBody*, PhysicsBody*> inProcessor, PhysicsBody* inA, PhysicsBody* inB);

	// Copy constructor
	PhysicsCollisionTestJob(const PhysicsCollisionTestJob& value);

	// Execute the function
	virtual void execute();

private:
	Delegate2<PhysicsBody*, PhysicsBody*> _processor;
	PhysicsBody* _bodyA;
	PhysicsBody* _bodyB;
};

#endif // __SUMPHYSICSCOLLISIONTESTJOB_H__