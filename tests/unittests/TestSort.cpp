#include <gtest/gtest.h>
#include "sort/sort.h"
#include "linkedlist/linkedlist.h"
#include "timer.h"

#ifndef TESTING_MODE_H
#define TESTING_MODE_H
#endif // TESTING_MODE_H

using namespace customalgorithms;

Timer timer;

TEST(TestSortingAlgorithm, testCycleSort)
{

    LinkedList<int> list;
    for (int i = 0; i < 100; i++)
        list.add(rand() % 100);
    
	std::cout << endl;
    timer.start();
	list.sort(LinkedList<int>::CYCLE_SORT);
    timer.stop();
    cout << timer.getTime();

	int prev = list.get();
	int next = list.get();
	do
	{
		list.next();
		next = list.get();
		ASSERT_GE(next, prev);
		
	} while (list.hasNext());
}

TEST(TestSortingAlgorithm, TestInsertionSort)
{
	LinkedList<int> list;
	for (int i = 0; i < 100; i++)
		list.add(rand() % 100);
	
	//list.print();
	list.sort(LinkedList<int>::INSERTION_SORT);
	//list.print();
	int prev = list.get();
	int next = list.get();
	do
	{
		list.next();
		next = list.get();
		ASSERT_GE(next, prev);

	} while (list.hasNext());
}
