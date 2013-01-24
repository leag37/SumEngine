//*************************************************************************************************
// Title: SumJob.h
// Author: Gael Huber
// Description: Base class for any asynchronous job type.
//*************************************************************************************************
#ifndef __SUMJOB_H__
#define __SUMJOB_H__

#include <process.h>
#include "SumInclude.h"

class Job {
public:
	// Enumeration representative of job status
	enum Status { 
		PENDING = 0,	// Job is currently awaiting processing
		IN_PROGRESS,	// Job is being completed
		DONE			// Job is complete
	};

	// Constructor
	Job(void) 
	: jobStatus(Job::PENDING) 
	{ }

	// Constructor given the function pointer
	Job(void (*pF)(void*), void* pP)
		: jobStatus(Job::PENDING), pFunction(pF), pParams(pP)
	{ }

	// Destructor
	~Job(void)
	{ }

	// Invoke the function
	SUMINLINE void operator()(void) const {
		pFunction(pParams);
	}

	// Return the status of the job
	SUMINLINE const Job::Status getStatus(void) const
	{
		return jobStatus;
	}

	// Set the status of the job
	SUMINLINE void setStatus(Status value)
	{
		jobStatus = value;
	}

private:
	// Assign the next available job id to this job
	SUMINLINE SUINT64 assignNextID(void) 
	{
		static SUINT64 id = 0;
		return id++;
	}

	Job::Status jobStatus;		// The current status of the job
	void (*pFunction)(void*);	// Pointer to function attached to the job
	void* pParams;				// Pointer to function parameters
};

#endif