#include <gtest/gtest.h>
#include "queue/queue.h"

#ifndef TESTING_MODE_H
#define TESTING_MODE_H
#endif // TESTING_MODE_H

using namespace customalgorithms;

TEST(TestQueue, createEmptyQueue)
{
	Queue<int> queue;
	ASSERT_TRUE(queue.size() == 0);
	ASSERT_TRUE(queue.dequeue() == NULL);
	queue.enqueue(841);
	ASSERT_TRUE(queue.size() == 1);
	ASSERT_TRUE(queue.dequeue() == 841);
}

TEST(TestQueue, testCharQueue)
{
	Queue<char*> charPtrQueue;
	Queue<char> charQueue;
	char* name = "Ihor";
	char* lastname = "Mudryy";
	char* company = "HERE";
	charQueue.enqueue(*name);
	charQueue.enqueue(*lastname);
	charQueue.enqueue(*company);

	charPtrQueue.enqueue(name);
	charPtrQueue.enqueue(lastname);
	charPtrQueue.enqueue(company);

	while (charPtrQueue.size() > 0)
	{
		char* val_ptr = charPtrQueue.dequeue();
		if (val_ptr)
			cout << val_ptr;
		cout << endl;
	}
	ASSERT_TRUE(charPtrQueue.dequeue() == NULL);
	cout << "NORMAL QUEUE " << endl;

	while (charQueue.size() > 0)
	{
		char val = charQueue.dequeue();
		cout << val++;
		cout << endl;
	}
}