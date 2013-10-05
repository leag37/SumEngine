//*************************************************************************************************
// Title: SumPhysicsJob.h
// Author: Gael Huber
// Description: A base event for the physics system. This will be utilized for processing the
//	physics generic events queue.
//*************************************************************************************************
#ifndef __SUMPHYSICSJOB_H__
#define __SUMPHYSICSJOB_H__

class PhysicsJob
{
public:
	// Constructor
	PhysicsJob();

	// Execute the job
	virtual void execute();
};

#endif // __SUMPHYSICSJOB_H__