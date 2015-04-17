#include <linkedlist/linkedlist.h>

#pragma once

namespace customalgorithms
{

/**
 * template class Queue
 */
template <typename T>
class Queue
{
public:
	Queue();
	Queue(T);
	~Queue();
	void enqueue(const T);
	T dequeue() const;
	int size();

private:
	LinkedList<T>* _list;
};

template <typename T>
Queue<T>::Queue()
{
	_list = new LinkedList<T>();
}

template <typename T>
Queue<T>::Queue(T arg)
{
	_list = new LinkedList<T>(arg);
}

template <typename T>
Queue<T>::~Queue()
{
	delete _list;
}

template <typename T>
void Queue<T>::enqueue(const T val)
{
	_list->add(val);
}

template <typename T>
T Queue<T>::dequeue() const
{
	return _list->popHead();
}

template <typename T>
int Queue<T>::size()
{
	return _list->getSize();
}

}
