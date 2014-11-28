#include <gtest/gtest.h>
#include <iostream>
#include "../include/node/node.h"
#include <memory>

using namespace std;
using namespace customalgorythms;

Node<int> node;

TEST(TestNode, create)
{
	ASSERT_TRUE(node.getValue() == NULL);
}

TEST(TestNode, setValue)
{
	node.setValue(1);
	ASSERT_TRUE(node.getValue() == 1);
	ASSERT_TRUE(node.getPreviousNode() == NULL);
	ASSERT_TRUE(node.getNextNode() == NULL);
}

TEST(TestNode, setNextAndPrev)
{
	Node<int> new_node;
	new_node.setValue(2);
	new_node.setPreviousNode(&node);
	node.setNextNode(&new_node);
	ASSERT_TRUE(node.getNextNode()->getValue() == 2);
	ASSERT_TRUE(new_node.getPreviousNode()->getValue() == 1);
}

TEST(TestNode, makeList)
{
	typedef unique_ptr<Node<int>> node_ptr;
	node_ptr current_node(new Node<int>);
	current_node->setValue(101);
	ASSERT_TRUE(current_node->getValue() == 101);
	for (int i = 0; i < 10; i++)
	{
		node_ptr new_node(new Node<int>);
		new_node->setValue(i);
		new_node->setPreviousNode(current_node.get());
		current_node->setNextNode(new_node.get());
		current_node = move(new_node);
	}
	Node<int>* m_node = current_node->getPreviousNode();
	while (m_node->getPreviousNode() != NULL)
	{
		m_node = current_node->getPreviousNode();
		cout << m_node->getValue() << ", ";
	}
}
