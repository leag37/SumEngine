//*************************************************************************************************
// Title: SumJobManager.h
// Author: Gael Huber
// Description: Manages jobs and processes them accordingly. When a job is added to the job queue,
//	it checks whether there is a free JobExecutor. If there is an available JobExecutor, the next
//	job will be assigned to it. Otherwise, it waits for the next available JobExecutor.
//
// TODO: Allow JobManager to be initializable via game configuration
// TODO: Move configuration pulling into this manager instead of passing it in through init method
//*************************************************************************************************
#ifndef __SUMJOBMANAGER_H__
#define __SUMJOBMANAGER_H__

#include "SumInclude.h"
#include "SumCriticalSection.h"
//#include "SumGlobals.h"
#include "SumQueue.h"
#include "SumJob.h"
//#include <Windows.h>

class JobManager : public Singleton<JobManager> {
public:
	JobManager(void);	// Constructor
	~JobManager(void);	// Destructor
	
	// Returns the singleton instance
	SUMINLINE static JobManager& getSingleton(void)
	{
		assert(singleton);
		return *singleton;
	}

	// Returns a pointer to the singleton instance
	SUMINLINE static JobManager* getSingletonPtr(void)
	{
		return singleton;
	}

	void startUp(int numExecutors);		// Initialize job manager w/ number of executors
	void shutDown(void);	// Shut down job manager

	void addJob(Job* j);			// Add job to the job queue
	Job* requestJob(void);	// Return first available job to perform
	SBOOL jobExists(void) const;		// Returns whether a job currently exists
	void clearJobs(void);		// Clear out all existing jobs

private:
	Queue<Job*> _jobs;			// List of all jobs to perform
	HANDLE* _workerThreads;		// Array of worker threads
	SUINT _numWorkerThreads;		// The number of worker threads

	CriticalSection _criticalSection;	// Used to manage access for job requests

	SBOOL _runManager;		// Is the manager currently running

private:
	// Private function that acts as a worker thread
	static DWORD WINAPI WorkerThread(LPVOID param);

// Properties
public:
	SUMINLINE SBOOL runManager()
	{
		return _runManager;
	}
};

#include "SumJobManager.inl"

//*************************************************************************************************
// Helper function that waits for a job. This will also request new jobs from the job manager to 
// perform while waiting for the specified job to finish. This ensures that even on the main thread
// work is not wasted and tasks continue to be performed.
//*************************************************************************************************
SUMINLINE void WaitForJob(const Job& job)
{
	JobManager* manager = JobManager::getSingletonPtr();

	while(job.getStatus() != Job::DONE)
	{
	// Check for an existing job to perform while waiting
		// If there is a job to perform, get the job
		Job* j(manager->requestJob());

		// If the acquisition was successful, run the job
		if(j) 
		{
			j->setStatus(Job::IN_PROGRESS);
			j->operator()();
			j->setStatus(Job::DONE);
		}
		// There are no other jobs to perform while waiting for this one, so just sleep
		else
		{
			Sleep(THREAD_SLEEP_TIME);
		}
		//// Check for an existing job to perform while waiting
		//if(manager->jobExists()) 
		//{
		//	// If there is a job to perform, get the job
		//	Job* j(manager->requestJob());

		//	// If the acquisition was successful, run the job
		//	if(j) {
		//		j->setStatus(Job::IN_PROGRESS);
		//		j->operator()();
		//		j->setStatus(Job::DONE);
		//	}
		//}
		//// There are no other jobs to perform while waiting for this one, so just sleep
		//else
		//{
		//	Sleep(THREAD_SLEEP_TIME);
		//}
	}
}

//*************************************************************************************************
// Helper function to add a job to the queue
//*************************************************************************************************
SUMINLINE void RequestJob(Job& job)
{
	// Set the job status to pending
	job.setStatus(Job::PENDING);

	// Add job to the queue
	JobManager::getSingletonPtr()->addJob(&job);
}

#endif