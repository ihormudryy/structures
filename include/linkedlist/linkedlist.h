#include "node/node.h"
#include "sort/sort.h"
#include <memory>
#include <iostream>

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#pragma once

namespace customalgorithms
{

/**
 * Doubly liked list
 * template class LinkedList is includes Node class
 */
template <typename T>
class LinkedList : public Sort
{

#ifdef TESTING_MODE_H
template <typename Type>
friend class TestDerivedClass;
#endif // TESTING_MODE_H

template <typename Type>
friend class Stack;
template <typename Type>
friend class Queue;

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
    int size();
    T operator [](unsigned int);
    void print();
	void sort(sorting_alg = CYCLE_SORT);
	
protected:
	void exchangeNodes(Node<T>&, Node<T>&);
	void exchangeValues(Node<T>&, Node<T>&);
	T getHead();
	T getTail();
	T popHead();
	T popTail();

private:
    int _size = 0;
	bool _initialized = false;
    Node<T>* _headNode;
    Node<T>* _tailNode;
    Node<T>* _currentNode;
	void _init(T);
	T _pop(bool = false);
    void _add(T&, T&, bool = false);
	void m_cycle_sort();
	void m_insertion_sort();	
};

template <typename T>
inline LinkedList<T>::LinkedList()
{
}

template <typename T>
inline LinkedList<T>::LinkedList(T arg)
{
	this->_init(arg);
}

template <typename T>
inline LinkedList<T>::~LinkedList()
{
    while (_size > 0) this->popHead();
}

/**
* Move to a next node in linked list.
* @returns bool true if next element exists and false is there is no any
*/
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

/**
* Move to a previous node in linked list.
* @returns bool true if previous element exists and false is there is no any
*/
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

/**
* Get value of current node in linked list.
* @returns typename value or NULL if list is empty
*/
template <typename T>
T LinkedList<T>::get()
{
	return (_currentNode) ? _currentNode->getValue() : NULL;
}

/**
* Check if next node exists in linked list.
* @returns bool true if next element exists
*/
template <typename T>
bool LinkedList<T>::hasNext()
{
	if (_initialized)
		return _currentNode->getNextNode() != NULL;
	else
		return false;
}

/**
* Check if previous node exists in linked list.
* @returns bool true if previous element exists
*/
template <typename T>
bool LinkedList<T>::hasPrev()
{
	if (_initialized)
		return _currentNode->getPreviousNode() != NULL;
	else
		return false;
}

template <typename T>
void LinkedList<T>::_init(T node)
{
    Node<T>* new_node = new Node<T>;
    new_node->setValue(node);
    _tailNode = new_node;
    _headNode = new_node;
    _currentNode = new_node;
    _size++;
    _initialized = true;
}

/**
* Add new element at the end of the list.
* @param typename value of new node
*/
template <typename T>
void LinkedList<T>::add(T elem)
{
	if (_initialized)
	{
        Node<T>* new_node = new Node<T>();
        Node<T>* copy_node_ptr = new Node<T>();
        copy_node_ptr = _tailNode;
        new_node->setValue(elem);
        new_node->setPreviousNode(copy_node_ptr);
        copy_node_ptr->setNextNode(new_node);
        _tailNode = new_node;
        _size++;
	}
	else
	{
		this->_init(elem);
	}
}

template <typename T>
void LinkedList<T>::_add(T& value, T& elem, bool before)
{
	if (_initialized)
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
				_size++;
				break;
			}
			node_ptr = node_ptr->getNextNode();
		} while (node_ptr->getNextNode());
	}
	else
	{
		this->_init(elem);
	}
}

/**
* Add new element before some node which has value 'elem' (only one hit). 
* It searched for specified element and if finds then inserts new node just before it.
* @param typename value of new node
* @param typename elem value of special node
*/
template <typename T>
void LinkedList<T>::addBefore(T value, T elem)
{
	this->_add(value, elem, true);
}

/**
* Add new element after some node which has value 'elem' (only one hit).
* It searched for specified element and if finds then inserts new node just after it.
* @param typename value of new node
* @param typename elem value of special node
*/
template <typename T>
void LinkedList<T>::addAfter(T value, T elem)
{
	this->_add(value, elem, false);
}

/**
* Remove specified element
* @param typename elem - element to be found and removed
* @param bool all - specify if all elements with such value have to be removed
*/
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
            _size--;
            if (all == false)
                break;
        }
        node_ptr = node_ptr->getNextNode();
    } while (node_ptr->getNextNode());
}

/**
* Get number of elements in linked list
* @returns int number of elements
*/
template <typename T>
int LinkedList<T>::getSize()
{
    return _size;
}

template <typename T>
int LinkedList<T>::size()
{
    return getSize();
}

template <typename T>
inline T LinkedList<T>::operator [](unsigned int value)
{
    int _t = 0;
    for (Node<T>* iter = _headNode; iter; iter = iter->getNextNode())
    {
        if(value == _t++)
            return iter->getValue();
    }
    return NULL;
}

template <typename T>
void LinkedList<T>::print()
{
    for (Node<T>* iter = _headNode; iter; iter = iter->getNextNode())
        std::cout << iter->getValue() << endl;
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
		_initialized = false;
	}
	_size--;
	return res;
}


template <typename T>
T LinkedList<T>::popHead()
{
    return (_size > 0) ? this->_pop(true) : NULL;
}

template <typename T>
T LinkedList<T>::popTail()
{
	return (_size > 0) ? this->_pop(false) : NULL;
}

/**
* Put the current node to the head of the list
*/
template <typename T>
void LinkedList<T>::back()
{
	_currentNode = _headNode;
}

/**
* Clear and reset linked list to its empty state
*/
template <typename T>
void LinkedList<T>::clear()
{
	if (_headNode != NULL) 
	{
		popTail();
		clear();
	};
}

template <typename T>
void LinkedList<T>::exchangeNodes(Node<T>& from, Node<T>& to)
{
	Node<T> tmp_node(from);
	from.setNextNode(to.getNextNode());
	from.setPreviousNode(to.getPreviousNode());
	to.setNextNode(tmp_node.getNextNode());
	to.setPreviousNode(tmp_node.getPreviousNode());

	if (from.getNextNode())
		from.getNextNode()->setPreviousNode(&from);
	else
		_tailNode = &from;
	if (from.getPreviousNode())
		from.getPreviousNode()->setNextNode(&from);
	else
		_headNode = &from;

	if (to.getNextNode())
		to.getNextNode()->setPreviousNode(&to);
	else
		_tailNode = &to;
	if (to.getPreviousNode())
		to.getPreviousNode()->setNextNode(&to);
	else
		_headNode = &to;
}

template <typename T>
void LinkedList<T>::exchangeValues(Node<T>& from, Node<T>& to)
{
	T tmp_val = from.getValue();
	from.setValue(to.getValue());
	to.setValue(tmp_val);
}

/**
* Sort all elements in linked list
* @param Optional sorting_alg enum. Default is CYCLE_SORT
*/
template <typename T>
void LinkedList<T>::sort(sorting_alg arg)
{
	switch (arg)
	{
	case CYCLE_SORT:
		this->m_cycle_sort();
		break;
	case INSERTION_SORT:
		this->m_insertion_sort();
		break;
	}
}

template <typename T>
void LinkedList<T>::m_cycle_sort()
{
	for (Node<T>* i = _headNode; i; i = i->getNextNode())
	{
		Node<T>* min = i;
		for (Node<T>* j = i; j; j = j->getNextNode())
		{
			if (j->getValue() < min->getValue()) min = j;
		}
		exchangeValues(*min, *i);
	}
}

template <typename T>
void LinkedList<T>::m_insertion_sort()
{
	for (Node<T>* i = _headNode->getNextNode(); i; i = i->getNextNode())
	{
		for ( Node<T>* j = i;
			 j->getPreviousNode() && j->getPreviousNode()->getValue() > j->getValue();
			 j = j->getPreviousNode() )
			exchangeValues(*j, *(j->getPreviousNode()));
	}
}

}

#endif // LINKEDLIST_H