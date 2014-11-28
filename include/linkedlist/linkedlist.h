#include "../include/node/node.h"
#include <memory>

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#pragma once

namespace customalgorythms
{

template <typename T>
class LinkedList
{

typedef unique_ptr< Node<T> > node_ptr;

public:
	LinkedList();
	LinkedList(T);
    ~LinkedList();
	bool hasNext();
    bool hasPrev();
    T get();
    bool next();
    bool prev();
	void add(T);
    void remove(T, bool);
    void addBefore(T, T);
    void addAfter(T, T);
    int getSize();

protected:
	T getHead();
	T getTail();

private:
    int size = 0;
	void init(T);
	bool initialized = false;
    Node<T>* _headNode;
    Node<T>* _tailNode;
    Node<T>* _currentNode;
};

template <typename T>
inline LinkedList<T>::LinkedList()
{
}

template <typename T>
inline LinkedList<T>::~LinkedList()
{
    //delete this->_tailNode;
    //delete this->_headNode;
    //delete this->_currentNode;
}

template <typename T>
inline LinkedList<T>::LinkedList(T arg)
{
	this->init(arg);
}

template <typename T>
bool LinkedList<T>::next()
{
    if (this->_currentNode->getNextNode() != NULL)
	{
        this->_currentNode = this->_currentNode->getNextNode();
        return true;
    }
    else
        return false;
}

template <typename T>
bool LinkedList<T>::prev()
{
    if (this->_currentNode->getPreviousNode() != NULL)
    {
        this->_currentNode = this->_currentNode->getPreviousNode();
        return true;
    }
    else
        return false;
}

template <typename T>
T LinkedList<T>::get()
{
    return this->_currentNode->getValue();
}

template <typename T>
bool LinkedList<T>::hasNext()
{
    return this->_currentNode->getNextNode() != NULL;
}

template <typename T>
bool LinkedList<T>::hasPrev()
{
    return this->_currentNode->getPreviousNode() != NULL;
}

template <typename T>
void LinkedList<T>::init(T node)
{
    Node<T>* new_node = new Node<T>;
    new_node->setValue(node);
    this->_tailNode = new_node;
    this->_headNode = new_node;
    this->_currentNode = new_node;
    this->size++;
    initialized = true;
}

template <typename T>
void LinkedList<T>::add(T elem)
{
	if (initialized)
	{
        Node<int>* new_node = new Node<int>();
        Node<int>* copy_node_ptr = new Node<int>();
        copy_node_ptr = this->_tailNode;
        new_node->setValue(elem);
        new_node->setPreviousNode(copy_node_ptr);
        copy_node_ptr->setNextNode(new_node);
        this->_tailNode = new_node;
        this->size++;
	}
	else
	{
		this->init(elem);
	}
}

template <typename T>
void LinkedList<T>::addBefore(T value, T elem)
{
    if (initialized)
    {
        Node<int>* node_ptr = this->_headNode;
        do
        {
            if(node_ptr->getValue() == elem)
            {
                Node<int>* new_node = new Node<int>();
                Node<int>* prev_node = new Node<int>();
                prev_node = node_ptr->getPreviousNode();
                new_node->setValue(value);
                new_node->setNextNode(node_ptr);
                new_node->setPreviousNode(prev_node);
                node_ptr->setPreviousNode(new_node);
                prev_node->setNextNode(new_node);
                this->size++;
                break;
            }
            node_ptr = node_ptr->getNextNode();
        } while (node_ptr->getNextNode());
    }
    else
    {
        this->init(elem);
    }
}

template <typename T>
void LinkedList<T>::addAfter(T value, T elem)
{
    if (initialized)
    {
        Node<int>* node_ptr = this->_headNode;
        do
        {
            if(node_ptr->getValue() == elem)
            {
                Node<int>* new_node = new Node<int>();
                Node<int>* next_node = new Node<int>();
                next_node = node_ptr->getNextNode();
                new_node->setValue(value);
                new_node->setNextNode(next_node);
                new_node->setPreviousNode(node_ptr);
                next_node->setPreviousNode(new_node);
                node_ptr->setNextNode(new_node);
                this->size++;
                break;
            }
            node_ptr = node_ptr->getNextNode();
        } while (node_ptr->getNextNode());
    }
    else
    {
        this->init(elem);
    }
}

template <typename T>
void LinkedList<T>::remove(T elem, bool all=false)
{
    Node<int>* node_ptr = this->_headNode;
    do {
        if (node_ptr->getValue() == elem)
        {
            Node<int>* prev_node = node_ptr->getPreviousNode();
            Node<int>* next_node = node_ptr->getNextNode();
            prev_node->setNextNode(next_node);
            next_node->setPreviousNode(prev_node);
            this->size--;
            if (all == false)
                break;
        }
        node_ptr = node_ptr->getNextNode();
    } while (node_ptr->getNextNode());
}

template <typename T>
int LinkedList<T>::getSize()
{
    return this->size;
}

template <typename T>
T LinkedList<T>::getHead()
{
    return this->_headNode->getValue();
}

template <typename T>
T LinkedList<T>::getTail()
{
    return this->_tailNode->getValue();
}

}

#endif // LINKEDLIST_H
