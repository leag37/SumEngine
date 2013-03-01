/**************************************************************************************************
* Title: SumJobManager.cpp
* Author: Gael Huber
* Description: Manages jobs and processes them accordingly. When a job is added to the job queue,
*	it checks whether there is a free JobExecutor. If there is an available JobExecutor, the next
*	job will be assigned to it. Otherwise, it waits for the next available JobExecutor.
**************************************************************************************************/
#include "SumJobManager.h"

//*************************************************************************************************
// Initialize the singleton instance of this class to 0
//*************************************************************************************************
template <> JobManager* Singleton<JobManager>::singleton = 0;

//*************************************************************************************************
// Constructor
//*************************************************************************************************
JobManager::JobManager(void) 
	: workerThreads(0), _runManager(false)
{ 
	_criticalSection = CriticalSection();
}

//*************************************************************************************************
// Destructor
//*************************************************************************************************
JobManager::~JobManager(void) 
{ }

//*************************************************************************************************
// Start up job manager
//**************************************************************************************************
void JobManager::startUp(SINT numExecutors) 
{
	// Set the manager to a running state
	_runManager = true;

	// Allocate memory for the array of worker threads
	workerThreads = (HANDLE*) malloc(sizeof(HANDLE*) * numExecutors);

	// Set the number of worker threads
	numWorkerThreads = numExecutors;

	// Create the worker threads
	for(SINT i(0); i < numWorkerThreads; ++i) {
		workerThreads[i] = (HANDLE) CreateThread(0, 0, JobManager::WorkerThread, static_cast<void*>(this), 0, 0);
	}
}

//*************************************************************************************************
// Shut down job manager
//*************************************************************************************************
void JobManager::shutDown(void) 
{
	// Stop the manager
	_runManager = false;
	
	// Clear the job queue
	clearJobs();

	// Wait for the threads
	WaitForMultipleObjects(numWorkerThreads, workerThreads, TRUE, 0x000000FF);
	free(workerThreads);
}

//*************************************************************************************************
// Clear the job queue and mark all jobs as done
//*************************************************************************************************
void JobManager::clearJobs(void) 
{
	// Empty job queue
	_criticalSection.enter();
	while(jobs.hasHead()) {
		Job* j(jobs.pop_front());
		j->setStatus(Job::DONE);
	}
	_criticalSection.leave();
}


//*************************************************************************************************
// Function that manages a given worker thread
//*************************************************************************************************
DWORD WINAPI JobManager::WorkerThread(LPVOID param) 
{
	JobManager* manager = static_cast<JobManager*>(param);

	// Get the thread priority
	//int priority = GetThreadPriority(GetCurrentThread());
	//SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);
	
	// Run provided that the simulation is active
	while(manager->runManager()) 
	{
		// Check whether there is a job to perform
		while(manager->jobExists()) 
		{
			// If there is a job to perform, get the job
			Job* j(manager->requestJob());

			// If the acquisition was successful, run the job
			if(j) {
				j->setStatus(Job::IN_PROGRESS);
				j->operator()();
				j->setStatus(Job::DONE);
			}
		}
		
		// If we still need to run the thread, go to sleep, otherwise return 0
		//if(manager->runManager())
		//{
			Sleep(THREAD_SLEEP_TIME);
		//}
		//else
		//{
		//	return 0;
		//}
	}

	return 0;
}