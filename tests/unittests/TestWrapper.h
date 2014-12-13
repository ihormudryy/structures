#ifndef TESTING_MODE_H
#define TESTING_MODE_H
#endif // TESTING_MODE_H

#include "linkedlist/linkedlist.h"

namespace ca_test
{
	template <typename T>
	class TestDerivedClass
	{
	public:
		TestDerivedClass();
		~TestDerivedClass();
		void add(T);
		T getHead() const;

	private:
		customalgorithms::LinkedList<T>* list;
	};

	template <typename T>
	inline TestDerivedClass<T>::TestDerivedClass()
	{
		//cout << PI << endl;
		this->list = new customalgorithms::LinkedList<T>();
	}

	template <typename T>
	inline TestDerivedClass<T>::~TestDerivedClass()
	{
		delete this->list;
	}

	template <typename T>
	inline void TestDerivedClass<T>::add(T arg)
	{
		this->list->add(arg);
	}

	template <typename T>
	T ca_test::TestDerivedClass<T>::getHead() const
	{
		//T a;
		//return a;

		return this->list->getHead();
	}

}