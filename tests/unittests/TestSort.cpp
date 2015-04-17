#include <gtest/gtest.h>
#include <sort/sort.h>
#include <linkedlist/linkedlist.h>

#ifndef TESTING_MODE_H
#define TESTING_MODE_H
#endif // TESTING_MODE_H

#include <timer.h>

using namespace customalgorithms;

void sorting(LinkedList<int>::sorting_alg param, bool print)
{
    testtools::Timer timer;
	LinkedList<int> list;
	for (int i = 0; i < 100; i++)
		list.add(rand() % 100);
	if (print)	list.print();
	std::cout << endl;
    timer.startWatch();
	list.sort(param);
    timer.stopWatch();
	if (print)	list.print();
	int prev = list.get();
	int next = list.get();
	do
	{
		list.next();
		next = list.get();
		ASSERT_GE(next, prev);

	} while (list.hasNext());
}
TEST(TestSortingAlgorithm, testCycleSort)
{
	sorting(LinkedList<int>::CYCLE_SORT, false);
}

TEST(TestSortingAlgorithm, TestInsertionSort)
{
	sorting(LinkedList<int>::INSERTION_SORT, false);
}

TEST(TestSortingAlgorithm, TestShellSort)
{
	sorting(LinkedList<int>::SHELL_SORT, false);
}
