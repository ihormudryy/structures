#include <gtest/gtest.h>
#include <iostream>
#include "../include/linkedlist/linkedlist.h"

customalgorythms::LinkedList<int> list;
using namespace std;

TEST(LinkedList, Create)
{
	ASSERT_TRUE(&list != NULL);
}

TEST(LinkedList, Fill)
{
	for (int i = 0; i < 10; i++)
	{
		//list.add(i);
		//if (i > 0)
		//	ASSERT_TRUE(list.hasNext());
	}
}

TEST(LinkedList, GetNext)
{
	//while (list.hasNext())
	//{
		//int v = list.next();
		//cout << v << " ";
		//ASSERT_TRUE(v >= 0 && v < 10);
	//}
}