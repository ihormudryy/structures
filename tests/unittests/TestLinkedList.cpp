#include <gtest/gtest.h>
#include "../include/linkedlist/linkedlist.h"

customalgorythms::LinkedList<int> list;

TEST(TestLinkedList, Create)
{
	ASSERT_TRUE(&list != NULL);
}

TEST(TestLinkedList, Fill)
{
    for (int i = 0; i < 20; i++)
    {
        list.add(i % 5);
        ASSERT_TRUE(list.get() == 0);
    }
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
