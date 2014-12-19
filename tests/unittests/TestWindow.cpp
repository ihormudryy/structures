#include <gtest/gtest.h>

#ifdef __linux__

TEST(TestSomething, testScreen)
{
    struct _size{
        int XMAX;
        int YMAX;
        _size (int v1, int v2)
        {
            XMAX = v1;
            YMAX = v2;
        }
    };
	_size m(256, 256);
	ASSERT_TRUE(true);
}

#endif // __linux__
