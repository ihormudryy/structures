#include <gtest/gtest.h>

#ifndef TESTING_MODE_H
#define TESTING_MODE_H
#endif // TESTING_MODE_H

#include "../include/linkedlist/linkedlist.h"

customalgorithms::LinkedList<int> list;

TEST(TestLinkedList, Create)
{
	ASSERT_TRUE(&list != NULL);
	ASSERT_TRUE(!list.hasNext());
	ASSERT_TRUE(!list.hasPrev());
}

TEST(TestLinkedList, Fill)
{
    for (int i = 0; i < 20; i++)
    {
        list.add(i % 5);	
        ASSERT_TRUE(list.get() == 0);
    }
	ASSERT_TRUE(list.hasNext());
	ASSERT_TRUE(!list.hasPrev());
}

TEST(TestLinkedList, getNextPrev)
{
    int j = 0;
    do
    {
        ASSERT_TRUE(list.get() == j++ % 5);
    } while (list.next());

    ASSERT_TRUE(list.getSize() == 20);

    do
    {
        ASSERT_TRUE(list.get() == --j % 5);
    } while (list.prev());
}

TEST(TestLinkedList, testRemove)
{
    list.remove(3);
    ASSERT_TRUE(list.getSize() == 19);
    int j = 0;
    do
    {
        if (j == 3)
        ASSERT_TRUE(list.get() != 3);
    } while (list.next());

    list.remove(2, true);
    ASSERT_TRUE(list.getSize() == 15);
    do
    {
        if (j == 3)
        ASSERT_TRUE(list.get() != 2);
    } while (list.prev());
}

TEST(TestLinkedList, addBefore)
{
    list.addBefore(100, 3);
    do
    {
        if(list.get() == 100)
        {
            list.next();
            ASSERT_TRUE(list.get() == 3);
        }
    } while (list.next());

    ASSERT_TRUE(list.getSize() == 16);
}

TEST(TestLinkedList, addAfter)
{
    list.addAfter(1122200111, 4);
    do
    {
        if(list.get() == 1122200111)
        {
            list.prev();
            ASSERT_TRUE(list.get() == 4);
        }
    } while (list.prev());

    ASSERT_TRUE(list.getSize() == 17);
}


TEST(TestLinkedList, listOfPointers)
{
	customalgorithms::LinkedList<int*> listOfPtrs;
	for (int h = 0; h < 20; h++)
	{
		int* v = new int(h);
		listOfPtrs.add(v);
	}
	cout << "From PTR!!" << endl;
	do
	{
		int* l = listOfPtrs.get();
		cout << *l << " ";
	} while (listOfPtrs.next());
    cout << endl;
}

TEST(TestLinkedList, testBack)
{
	while (list.next()){};
	ASSERT_TRUE(list.get() == 4);
	list.back();
	ASSERT_TRUE(list.get() == 0);
}

TEST(TestLinkedList, testClear)
{
	customalgorithms::LinkedList<char> charList;

	for (int i = 49; i < 79; i++)
	{
		charList.add((char)i);
	}
	charList.clear();
	ASSERT_TRUE(charList.getSize() == 0);
	ASSERT_TRUE(charList.get() == NULL);

	for (int i = 49; i < 79; i++)
	{
		charList.add((char)i);
	}

	ASSERT_TRUE(charList.getSize() == 30);
	for (int i = 49; i < 79; i++)
	{
		char c = charList.get();
		charList.next();
		ASSERT_TRUE((int)c == i);
	}
}

TEST(TestLinkedList, testOperators)
{
    list.back();
    for (int i = 0; i < list.getSize() - 1; i++)
    {
        ASSERT_EQ(list.get(), list[i]);
        cout << list[i] << "==" << list.get() << endl;
        list.next();
    }
    cout << endl;
}
