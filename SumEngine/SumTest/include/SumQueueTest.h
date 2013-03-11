//*************************************************************************************************
// Title: SumQueueTest.h
// Author: Gael Huber
// Description: Queue tests.
//*************************************************************************************************
#ifndef __SUMQUEUETEST_H__
#define __SUMQUEUETEST_H__

#include "SumInclude.h"
#include "SumQueue.h"
#include "SumTestHelper.h"

using namespace Test;

extern "C"
{
	// Queue suite of tests
	void QueueSuite(SUINT& errors, SUINT& tests);

	// Initialize the queue
	void TestQueueInit(SUINT& errors, SUINT& tests);

	// Enqueue
	void TestQueueEnqueue(SUINT& errors, SUINT& tests);

	// Dequeue
	void TestQueueDequeue(SUINT& errors, SUINT& tests);

	// Queue growth
	void TestQueueGrowth(SUINT& errors, SUINT& tests);

	// Enqueue and dequeue
	void TestQueueEnqueueDequeue(SUINT& errors, SUINT& tests);

	// Queue deletion
	void TestQueueDelete(SUINT& errors, SUINT& tests);

	// Clear
	void TestQueueClear(SUINT& errors, SUINT& tests);
}


#endif