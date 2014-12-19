#include <gtest/gtest.h>
#include <memory>

#ifndef TESTING_MODE_H
#define TESTING_MODE_H
#endif // TESTING_MODE_H

#include "../include/node/node.h"

using namespace customalgorithms;

Node<int>* current_node = new Node<int>();

TEST(TestNode, createEmpty)
{
    cout << sizeof(bool) << " " << sizeof(char) << endl;
    ASSERT_TRUE(current_node->getValue() == NULL);
}

TEST(TestNode, setValue)
{
    current_node->setValue(100);
    ASSERT_TRUE(current_node->getValue() == 100);
}

TEST(TestNode, setNextNode)
{
    Node<int>* new_node = new Node<int>();
    new_node->setValue(500);
    new_node->setPreviousNode(current_node);
    current_node->setNextNode(new_node);
    ASSERT_TRUE(current_node->getNextNode()->getValue() == 500);
    ASSERT_TRUE(new_node->getPreviousNode()->getValue() == 100);
}

TEST(TestNode, setPrevNode)
{
    Node<int>* new_node = new Node<int>();
    new_node->setValue(-192);
    new_node->setNextNode(current_node);
    current_node->setPreviousNode(new_node);
    ASSERT_TRUE(current_node->getPreviousNode()->getValue() == -192);
    ASSERT_TRUE(new_node->getNextNode()->getValue() == 100);
}

TEST(TestNode, makeList)
{
    for (int i = 0; i < 10; i++)
    {
        Node<int>* new_node = new Node<int>();
        Node<int>* copy_node_ptr = new Node<int>();
        copy_node_ptr = current_node;
        new_node->setValue(i);
        new_node->setPreviousNode(copy_node_ptr);
        copy_node_ptr->setNextNode(new_node);
        current_node = new_node;
        ASSERT_TRUE(current_node->getValue() == i);
    }
}

TEST(TestNode, makeNodesWithOtherTypes)
{
    Node<float> float_node_0;
    ASSERT_TRUE(float_node_0.getValue() == NULL);
    float val = -1.012;
    Node<float> float_node_1(val);
    ASSERT_TRUE(float_node_1.getValue() == val);
    Node<float> float_node_2(float_node_1);
    ASSERT_TRUE(float_node_2.getValue() == val);
    double d_val = 213145875320121233e-6;
    Node<double> double_node_3(d_val);
    ASSERT_TRUE(double_node_3.getValue() == d_val);
    char st[] = "AbasRHLAPs12";
    Node<char> char_node_4(*st);
    ASSERT_TRUE(char_node_4.getValue() == *st);
}

TEST(TestNode, testEqualsOperator)
{
	Node<int> n1(34);
	Node<int> n2(34);
	Node<int> n3(100);
	ASSERT_TRUE(n1 == n2);
	ASSERT_FALSE(n1 == n3);
}
