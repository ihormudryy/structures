#include "node/node.h"
#include <memory>

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#pragma once

namespace customalgorythms
{

/**
 * Doubly liked list
 * template class LinkedList is derived class from Node
 */
template <typename T>
class LinkedList
{

#ifdef TESTING_MODE_H
template <typename Type>
friend class TestDerivedClass;
#endif // TESTING_MODE_H

template <typename Type>
friend class Stack;

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
    void remove(T, bool = false);
    void addBefore(T, T);
    void addAfter(T, T);
	void back();
	void clear();
    int getSize();

protected:
	T getHead();
	T getTail();
	T popHead();
	T popTail();

private:
    int size = 0;
	void init(T);
	bool initialized = false;
    Node<T>* _headNode;
    Node<T>* _tailNode;
    Node<T>* _currentNode;
	T _pop(bool = false);
    void _add(T&, T&, bool = false);
};

template <typename T>
inline LinkedList<T>::LinkedList()
{
}

template <typename T>
inline LinkedList<T>::~LinkedList()
{
    //delete _tailNode;
    //delete _headNode;
    //delete _currentNode;
}

template <typename T>
inline LinkedList<T>::LinkedList(T arg)
{
	this->init(arg);
}

template <typename T>
bool LinkedList<T>::next()
{
    if (_currentNode->getNextNode() != NULL)
	{
        _currentNode = _currentNode->getNextNode();
        return true;
    }
    else
        return false;
}

template <typename T>
bool LinkedList<T>::prev()
{
    if (_currentNode->getPreviousNode() != NULL)
    {
        _currentNode = _currentNode->getPreviousNode();
        return true;
    }
    else
        return false;
}

template <typename T>
T LinkedList<T>::get()
{
	return (_currentNode) ? _currentNode->getValue() : NULL;
}

template <typename T>
bool LinkedList<T>::hasNext()
{
	if (initialized)
		return _currentNode->getNextNode() != NULL;
	else
		return false;
}

template <typename T>
bool LinkedList<T>::hasPrev()
{
	if (initialized)
		return _currentNode->getPreviousNode() != NULL;
	else
		return false;
}

template <typename T>
void LinkedList<T>::init(T node)
{
    Node<T>* new_node = new Node<T>;
    new_node->setValue(node);
    _tailNode = new_node;
    _headNode = new_node;
    _currentNode = new_node;
    size++;
    initialized = true;
}

template <typename T>
void LinkedList<T>::add(T elem)
{
	if (initialized)
	{
        Node<T>* new_node = new Node<T>();
        Node<T>* copy_node_ptr = new Node<T>();
        copy_node_ptr = _tailNode;
        new_node->setValue(elem);
        new_node->setPreviousNode(copy_node_ptr);
        copy_node_ptr->setNextNode(new_node);
        _tailNode = new_node;
        size++;
	}
	else
	{
		this->init(elem);
	}
}

template <typename T>
void LinkedList<T>::_add(T& value, T& elem, bool before)
{
	if (initialized)
	{
		Node<T>* node_ptr = _headNode;
		do
		{
			if (node_ptr->getValue() == elem)
			{
				Node<T>* new_node = new Node<T>();
				Node<T>* _tmp_node = new Node<T>();
				_tmp_node = (before) ? node_ptr->getPreviousNode() : node_ptr->getNextNode();
				new_node->setValue(value);
				new_node->setNextNode(before ? node_ptr : _tmp_node);
				new_node->setPreviousNode(before ? _tmp_node : node_ptr);
				if (before)
				{
					node_ptr->setPreviousNode(new_node);
					_tmp_node->setNextNode(new_node);
				}
				else
				{
					_tmp_node->setPreviousNode(new_node);
					node_ptr->setNextNode(new_node);
				}
				size++;
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
void LinkedList<T>::addBefore(T value, T elem)
{
	this->_add(value, elem, true);
}

template <typename T>
void LinkedList<T>::addAfter(T value, T elem)
{
	this->_add(value, elem, false);
}

template <typename T>
void LinkedList<T>::remove(T elem, bool all)
{
    Node<T>* node_ptr = _headNode;
    do {
        if (node_ptr->getValue() == elem)
        {
            Node<T>* prev_node = node_ptr->getPreviousNode();
            Node<T>* next_node = node_ptr->getNextNode();
            prev_node->setNextNode(next_node);
            next_node->setPreviousNode(prev_node);
            size--;
            if (all == false)
                break;
        }
        node_ptr = node_ptr->getNextNode();
    } while (node_ptr->getNextNode());
}

template <typename T>
int LinkedList<T>::getSize()
{
    return size;
}

template <typename T>
T LinkedList<T>::getHead()
{
    return _headNode->getValue();
}

template <typename T>
T LinkedList<T>::getTail()
{
    return _tailNode->getValue();
}

/*
 * If head is true then pop from the head of the list, if false then from tail
*/
template <typename T>
T LinkedList<T>::_pop(bool head)
{
	Node<T>* _node = (head) ? _headNode : _tailNode;
	T res = _node->getValue();
	Node<T>* _next = (head) ? _node->getNextNode() : _node->getPreviousNode();
	if (_next)
	{
		Node<T>* _toRemove = (head) ? _next->getPreviousNode() : _next->getNextNode();
		(head) ? _next->setPreviousNode(NULL) : _next->setNextNode(NULL);
		_currentNode = (_currentNode == _node) ? _next : _currentNode;
		if (head) _headNode = _next;
		else _tailNode = _next;
		if (_toRemove) delete _toRemove;
	}
	else
	{
		delete _node;
		_headNode = NULL;
		_tailNode = NULL;
		_currentNode = NULL;
		initialized = false;
	}
	size--;
	return res;
}


template <typename T>
T LinkedList<T>::popHead()
{
	return (size > 0) ? this->_pop(true) : NULL;
}

template <typename T>
T LinkedList<T>::popTail()
{
	return (size > 0) ? this->_pop(false) : NULL;
}

template <typename T>
void LinkedList<T>::back()
{
	_currentNode = _headNode;
}

template <typename T>
void LinkedList<T>::clear()
{
	while (popHead()) {};
}

}

#endif // LINKEDLIST_H
