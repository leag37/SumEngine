//*************************************************************************************************
// Title: SumJobManager.inl
// Author: Gael Huber
// Description: Manages jobs and processes them accordingly. When a job is added to the job queue,
//	it checks whether there is a free JobExecutor. If there is an available JobExecutor, the next
//	job will be assigned to it. Otherwise, it waits for the next available JobExecutor.
//*************************************************************************************************

//*************************************************************************************************
// Add a job to the job queue
//*************************************************************************************************
SUMINLINE void JobManager::addJob(Job& j) 
{
	// Enter the critical section
	_criticalSection.enter();
	//_mutex.enter();

	// Add a the job to the list
	jobs.push_back(&j);

	// Leave the section
	_criticalSection.leave();
}

//*************************************************************************************************
// Return first available job to perform
//*************************************************************************************************
SUMINLINE Job* JobManager::requestJob(void) 
{


	// Get the next job if it exists (we might have concurrency problems, so check once more for 
	// existence now that we have properly acquired the lock
	Job* j(0);
	if(jobExists())
	{
		// Enter CS
		_criticalSection.enter();
		//_mutex.enter();

		if(jobExists())
		{
			// Grab job
			j = jobs.pop_front();
		}

		// Enter critical section
		_criticalSection.leave();
	}

	return j;
}

//*************************************************************************************************
// Returns whether a job currently exists for processing
//*************************************************************************************************
SUMINLINE SBOOL JobManager::jobExists(void) const 
{
	return jobs.hasHead();
}