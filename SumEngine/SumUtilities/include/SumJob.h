//*************************************************************************************************
// Title: SumJob.h
// Author: Gael Huber
// Description: Base class for any asynchronous job type.
//*************************************************************************************************
#ifndef __SUMJOB_H__
#define __SUMJOB_H__

#include <process.h>
#include "SumInclude.h"
#include "SumDelegate.h"

// Thread sleep time
#define THREAD_SLEEP_TIME 1

class Job {
public:
	// Enumeration representative of job status
	enum Status { 
		PENDING = 0,	// Job is currently awaiting processing
		IN_PROGRESS,	// Job is being completed
		DONE			// Job is complete
	};

	// Constructor
	SUMINLINE Job(void) 
	: jobStatus(Job::DONE) 
	{ }

	// Constructor given the function pointer
	SUMINLINE Job(Delegate0 del)
		: jobStatus(Job::DONE), _delegate(del)
	{ }

	// Destructor
	~Job(void)
	{ }

	// Invoke the function
	SUMINLINE void operator()(void) const {
		_delegate();
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

	// The current status of the job
	Job::Status jobStatus;

	// Delegate containing job function
	Delegate0 _delegate;
};

#endif