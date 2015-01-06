#ifndef SORT_H
#define SORT_H

namespace customalgorithms {
/*
* Abstract class for sorting algorithms
* 
*/
class Sort
{
public:
    enum sorting_alg
	{
		CYCLE_SORT,
		INSERTION_SORT
    };
	virtual void sort(sorting_alg) = 0;
protected:
	virtual void m_cycle_sort() = 0;
	virtual void m_insertion_sort() = 0;
};

}

#endif // SORT_H
