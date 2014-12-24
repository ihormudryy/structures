#include <gtest/gtest.h>
#include <memory>

#ifndef TESTING_MODE_H
#define TESTING_MODE_H
#endif // TESTING_MODE_H

using namespace std;

class Error
{
public:
	int error;
	Error(int i) : error(i){};
	enum exceptions{
		NULL_PTR,
		OUT_OF_RANGE
	};
	void debug_print()
	{
		switch (error)
		{
		case(exceptions::NULL_PTR):
			cout << "Null pointer" << endl;
			break;
		case(exceptions::OUT_OF_RANGE) :
			cout << "Index is out of range" << endl;
			break;
		default:
			break;
		}
	};
};

#define ASSERT(value) ((value) == NULL ? throw Error(0) : "");

#include "../include/map/map.h"

using namespace customalgorithms;

TEST(TestMap, testCreate)
{
	Map<double, int> map1();
	Map<double, int> map2;
	Map<double, int> map3(map2);
	struct asdf {
		char fio[30];
		unsigned char date : 4;
		unsigned char code : 4;
	};
	std::cout << "Size of struct " << sizeof(asdf) << std::endl;
	Map<int, int>* a1 = NULL;
	try
	{
		ASSERT(a1);
	}
	catch (Error e)
	{
		e.debug_print();
        //terminate();
	}
    //ASSERT(a1);
	void* sd = malloc(1);
	ASSERT_THROW(ASSERT(a1), Error);

}
