#include <memory>
#include <linkedlist/linkedlist.h>

#pragma once

namespace customalgorithms
{

/**
* Stack class
* template class Stack which composes LinkedList
*/
template <typename T>
class Stack
{
public:
	Stack();
	Stack(T);
	~Stack();
	void push(const T);
	T pop() const;
	int size();

private:
	LinkedList<T>* _list;
}; 

template <typename T>
Stack<T>::Stack()
{
	_list = new LinkedList<T>();
}

template <typename T>
Stack<T>::Stack(T arg)
{
	_list = new LinkedList<T>(arg);
}

template <typename T>
Stack<T>::~Stack()
{
	delete _list;
}

template <typename T>
void Stack<T>::push(const T val)
{
	_list->add(val);
}

template <typename T>
T Stack<T>::pop() const
{
	return _list->popTail();
}

template <typename T>
int Stack<T>::size()
{
	return _list->getSize();
}

}
