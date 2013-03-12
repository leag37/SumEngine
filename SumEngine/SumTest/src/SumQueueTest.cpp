//*************************************************************************************************
// Title: SumQueueTest.cpp
// Author: Gael Huber
// Description: Queue tests.
//*************************************************************************************************
#include "SumQueueTest.h"

//*************************************************************************************************
// Queue suite of tests
//*************************************************************************************************
void QueueSuite(SUINT& errors, SUINT& tests)
{
	TestQueueInit(errors, tests);
	TestQueueEnqueue(errors, tests);
	TestQueueDequeue(errors, tests);
	TestQueueGrowth(errors, tests);
	TestQueueEnqueueDequeue(errors, tests);
}

//*************************************************************************************************
// Initialize the queue
//*************************************************************************************************
void TestQueueInit(SUINT& errors, SUINT& tests)
{
	String title = "QueueInit";

	// Number of errors in this test
	SUINT tErrors = 0;
	SUINT tTests = 0;

	// Test case 1: Primitive queue: Queue<SINT>
	Queue<SINT> q1 = Queue<SINT>();
	if(q1.size() != 0 || q1.maxSize() != 1)
	{
		Test::printError(title, 1);
		++tErrors;
	}
	++tTests;

	// Test case 2: Struct queue: Queue<Struct>
	Queue<Test::TestStruct> q2 = Queue<Test::TestStruct>();
	if(q2.size() != 0 || q2.maxSize() != 1)
	{
		Test::printError(title, 2);
		++tErrors;
	}
	++tTests;

	// Test case 3: Struct pointer queue: Queue<Struct*>
	Queue<Test::TestStruct*> q3 = Queue<Test::TestStruct*>();
	if(q3.size() != 0 || q3.maxSize() != 1)
	{
		Test::printError(title, 3);
		++tErrors;
	}
	++tTests;

	// Test case 4: Class queue: Queue<Class>
	Queue<Test::TestClass> q4 = Queue<Test::TestClass>();
	if(q4.size() != 0 || q4.maxSize() != 1)
	{
		Test::printError(title, 4);
		++tErrors;
	}
	++tTests;

	// Test case 5: Class pointer queue: Queue<Class*>
	Queue<Test::TestClass*> q5 = Queue<Test::TestClass*>();
	if(q5.size() != 0 || q5.maxSize() != 1)
	{
		Test::printError(title, 5);
		++tErrors;
	}
	++tTests;

	// Test case 6: Default size
	Queue<SINT> q6 = Queue<SINT>(100);
	if(q6.size() != 0 || q6.maxSize() != 100)
	{
		Test::printError(title, 6);
		++tErrors;
	}
	++tTests;

	// Print results
	Test::printResult(tErrors, tTests, title);

	// Increase total error count
	errors += tErrors;
	tests += tTests;
}

//*************************************************************************************************
// Enqueue
//*************************************************************************************************
void TestQueueEnqueue(SUINT& errors, SUINT& tests)
{
	const String& title = "QueueEnqueue";

	// Number of errors in this test
	SUINT tErrors = 0;
	SUINT tTests = 0;

	// Test variables
	Test::TestStruct str = Test::TestStruct();
	Test::TestClass cls = Test::TestClass();

	// Test case 1: Primitive queue: Queue<SINT>
	Queue<SINT> q1 = Queue<SINT>(100);
	q1.enqueue(1);
	if(q1.size() != 1 && q1.maxSize() != 100)
	{
		Test::printError(title, 1);
		++tErrors;
	}
	++tTests;

	// Test case 2: Struct queue: Queue<Struct>
	Queue<Test::TestStruct> q2 = Queue<Test::TestStruct>(100);
	q2.enqueue(str);
	if(q2.size() != 1 || q2.maxSize() != 100)
	{
		Test::printError(title, 2);
		++tErrors;
	}
	++tTests;

	// Test case 3: Struct pointer queue: Queue<Struct*>
	Queue<Test::TestStruct*> q3 = Queue<Test::TestStruct*>(100);
	q3.enqueue(&str);
	if(q3.size() != 1 || q3.maxSize() != 100)
	{
		Test::printError(title, 3);
		++tErrors;
	}
	++tTests;

	// Test case 4: Class queue: Queue<Class>
	Queue<Test::TestClass> q4 = Queue<Test::TestClass>(100);
	q4.enqueue(cls);
	if(q4.size() != 1 || q4.maxSize() != 100)
	{
		Test::printError(title, 4);
		++tErrors;
	}
	++tTests;

	// Test case 5: Class pointer queue: Queue<Class*>
	Queue<Test::TestClass*> q5 = Queue<Test::TestClass*>(100);
	q5.enqueue(&cls);
	if(q5.size() != 1 || q5.maxSize() != 100)
	{
		Test::printError(title, 5);
		++tErrors;
	}
	++tTests;

	// Test case 6: No default size
	Queue<SINT> q6 = Queue<SINT>();
	q6.enqueue(1);
	if(q6.size() != 1 && q6.maxSize() != 1)
	{
		Test::printError(title, 6);
		++tErrors;
	}
	++tTests;

	// Test case 7: Multiple enqueues
	Queue<SINT> q7 = Queue<SINT>(100);
	for(SINT i = 0; i < 10; ++i)
	{
		q7.enqueue(i);
	}
	if(q7.size() != 10)
	{
		Test::printError(title, 7);
		++tErrors;
	}
	++tTests;

	// Print results
	Test::printResult(tErrors, tTests, title);

	// Increase total error count
	errors += tErrors;
	tests += tTests;
}

//*************************************************************************************************
// Dequeue
//*************************************************************************************************
void TestQueueDequeue(SUINT& errors, SUINT& tests)
{
	const String& title = "QueueDequeue";

	// Number of errors in this test
	SUINT tErrors = 0;
	SUINT tTests = 0;

	// Test variables
	Test::TestStruct str = Test::TestStruct();
	Test::TestClass cls = Test::TestClass();

	// Test case 1: Primitive queue: Queue<SINT>
	Queue<SINT> q1 = Queue<SINT>(100);
	q1.enqueue(1);
	SINT val = q1.dequeue();
	SBOOL result = val != 1;
	result |= q1.size() != 0;
	result |= q1.maxSize() != 100;
	if(result)
	{
		Test::printError(title, 1);
		++tErrors;
	}
	++tTests;

	// Test case 2: Struct queue: Queue<Struct>
	Queue<Test::TestStruct> q2 = Queue<Test::TestStruct>(100);
	q2.enqueue(str);
	TestStruct s = q2.dequeue();
	if(s != str || q2.size() != 0 || q2.maxSize() != 100)
	{
		Test::printError(title, 2);
		++tErrors;
	}
	++tTests;

	// Test case 3: Struct pointer queue: Queue<Struct*>
	Queue<Test::TestStruct*> q3 = Queue<Test::TestStruct*>(100);
	q3.enqueue(&str);
	TestStruct* sPtr = q3.dequeue();
	if(*sPtr != str || q3.size() != 0 || q3.maxSize() != 100)
	{
		Test::printError(title, 3);
		++tErrors;
	}
	++tTests;

	// Test case 4: Class queue: Queue<Class>
	Queue<Test::TestClass> q4 = Queue<Test::TestClass>(100);
	q4.enqueue(cls);
	TestClass c = q4.dequeue();
	if(c != cls || q4.size() != 0 || q4.maxSize() != 100)
	{
		Test::printError(title, 4);
		++tErrors;
	}
	++tTests;

	// Test case 5: Class pointer queue: Queue<Class*>
	Queue<Test::TestClass*> q5 = Queue<Test::TestClass*>(100);
	q5.enqueue(&cls);
	TestClass* cPtr = q5.dequeue();
	if(*cPtr != cls || q5.size() != 0 || q5.maxSize() != 100)
	{
		Test::printError(title, 5);
		++tErrors;
	}
	++tTests;

	// Test case 6: No default size
	Queue<SINT> q6 = Queue<SINT>();
	q6.enqueue(1);
	SINT tempInt = q6.dequeue();
	if(tempInt != 1 || q6.size() != 0 && q6.maxSize() != 1)
	{
		Test::printError(title, 6);
		++tErrors;
	}
	++tTests;

	// Test case 7: Multiple enqueues
	Queue<SINT> q7 = Queue<SINT>(100);
	for(SINT i = 0; i < 10; ++i)
	{
		q7.enqueue(i);
	}
	for(SINT i = 0; i < 10; ++i)
	{
		tempInt = q7.dequeue();

		if(tempInt != i)
		{
			printError(title, 7);
			++tErrors;
		}
	}
	if(q7.size() != 0)
	{
		Test::printError(title, 7);
		++tErrors;
	}
	++tTests;

	// Print results
	Test::printResult(tErrors, tTests, title);

	// Increase total error count
	errors += tErrors;
	tests += tTests;
}

//*************************************************************************************************
// Queue growth
//*************************************************************************************************
void TestQueueGrowth(SUINT& errors, SUINT& tests)
{
	const String& title = "QueueGrowth";

	// Number of errors in this test
	SUINT tErrors = 0;
	SUINT tTests = 0;

	// Test variables
	Test::TestStruct str[10];
	Test::TestClass cls[10];
	for(SINT i = 0; i < 10; ++i)
	{
		str[i] = TestStruct(i, i + 1);
		cls[i] = TestClass(i, i + 1);
	}

	// Test case 1: Primitive queue: Queue<SINT>
	Queue<SINT> q1 = Queue<SINT>();
	SBOOL result = false;
	for(SINT i = 0; i < 10; ++i)
	{
		q1.enqueue(i);
	}
	for(SINT i = 0; i < 10; ++i)
	{
		SINT val = q1.dequeue();
		result |= val != i;
	}
	result |= q1.size() != 0;
	if(result)
	{
		Test::printError(title, 1);
		++tErrors;
	}
	++tTests;

	// Test case 2: Struct queue: Queue<Struct>
	Queue<Test::TestStruct> q2 = Queue<Test::TestStruct>();
	result = false;
	for(SINT i = 0; i < 10; ++i)
	{
		q2.enqueue(str[i]);
	}
	for(SINT i = 0; i < 10; ++i)
	{
		TestStruct val = q2.dequeue();
		result |= val != str[i];
	}
	if(result || q2.size() != 0)
	{
		Test::printError(title, 2);
		++tErrors;
	}
	++tTests;

	// Test case 3: Struct pointer queue: Queue<Struct*>
	Queue<Test::TestStruct*> q3 = Queue<Test::TestStruct*>();
	result = false;
	for(SINT i = 0; i < 10; ++i)
	{
		q3.enqueue(&str[i]);
	}
	for(SINT i = 0; i < 10; ++i)
	{
		TestStruct val = *q3.dequeue();
		result |= val != str[i];
	}
	if(result || q3.size() != 0)
	{
		Test::printError(title, 3);
		++tErrors;
	}
	++tTests;

	// Test case 4: Class queue: Queue<Class>
	Queue<Test::TestClass> q4 = Queue<Test::TestClass>();
	result = false;
	for(SINT i = 0; i < 10; ++i)
	{
		q4.enqueue(cls[i]);
	}
	for(SINT i = 0; i < 10; ++i)
	{
		TestClass val = q4.dequeue();
		result |= val != cls[i];
	}
	if(result || q4.size() != 0)
	{
		Test::printError(title, 4);
		++tErrors;
	}
	++tTests;

	// Test case 5: Class pointer queue: Queue<Class*>
	Queue<Test::TestClass*> q5 = Queue<Test::TestClass*>();
	result = false;
	for(SINT i = 0; i < 10; ++i)
	{
		q5.enqueue(&cls[i]);
	}
	for(SINT i = 0; i < 10; ++i)
	{
		TestClass* val = q5.dequeue();
		result |= *val != cls[i];
	}
	if(result || q5.size() != 0)
	{
		Test::printError(title, 5);
		++tErrors;
	}
	++tTests;

	// Print results
	Test::printResult(tErrors, tTests, title);

	// Increase total error count
	errors += tErrors;
	tests += tTests;
}

//*************************************************************************************************
// Enqueue and dequeue
//*************************************************************************************************
void TestQueueEnqueueDequeue(SUINT& errors, SUINT& tests)
{
	const String& title = "QueueEnqueueDequeue";

	// Number of errors in this test
	SUINT tErrors = 0;
	SUINT tTests = 0;

	// Test variables
	Test::TestStruct str[10];
	Test::TestClass cls[10];
	for(SINT i = 0; i < 10; ++i)
	{
		str[i] = TestStruct(i, i + 1);
		cls[i] = TestClass(i, i + 1);
	}

	// Test case 1: Primitive queue: Queue<SINT>
	Queue<SINT> q1 = Queue<SINT>();
	SBOOL result = false;
	SINT expected = 0;
	for(SINT i = 0; i < 10; ++i)
	{
		q1.enqueue(i);
		q1.enqueue(i*2);

		SINT val = q1.dequeue();
		if(i % 2 == 0)
		{
			result |= val != expected;
		}
		else
		{
			result |= val != expected * 2;
			++expected;
		}
	}
	result |= q1.size() != 10;
	if(result)
	{
		Test::printError(title, 1);
		++tErrors;
	}
	++tTests;

	// Print results
	Test::printResult(tErrors, tTests, title);

	// Increase total error count
	errors += tErrors;
	tests += tTests;
}
	
////*************************************************************************************************
//// Queue deletion
////*************************************************************************************************
//void TestQueueDelete(SUINT& errors, SUINT& tests);
//
////*************************************************************************************************
//// Clear
////*************************************************************************************************
//void TestQueueClear(SUINT& errors, SUINT& tests);

