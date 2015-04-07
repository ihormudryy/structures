#include <gtest/gtest.h>
#include <memory>

#ifndef TESTING_MODE_H
#define TESTING_MODE_H
#endif // TESTING_MODE_H
/*
using namespace std;
/
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
            cerr << "Null pointer" << endl;
			break;
		case(exceptions::OUT_OF_RANGE) :
            cerr << "Index is out of range" << endl;
			break;
		default:
			break;
		}
	};
};

#define ASSERT(value) ((value) == NULL ? throw Error(0) : "");

#include "../include/map/map.h"

using namespace customalgorithms;
*/
TEST(TestMap, testCreate)
{
	/*
	Map<double, int> map1();
	Map<double, int> map2;
	Map<double, int> map3(map2);
	Map<int, int>* a1 = NULL;
	try
	{
		ASSERT(a1);
	}
	catch (Error e)
	{
        e.debug_print();
    }
#ifndef __EMSCRIPTEN__
	ASSERT_THROW(ASSERT(a1), Error);
#endif // __EMSCRIPTEN__
*/
}
