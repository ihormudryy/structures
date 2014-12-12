#include <gtest/gtest.h>
#include <memory>
#include <math.h> 
#include <limits> 

#ifndef TESTING_MODE_H
#define TESTING_MODE_H
#endif // TESTING_MODE_H

#define HW(name) cout<<"Hello World " << name <<endl

using namespace std;

struct b_struct
{
	int power = 0;
	int mantissa;
};
/*
void testReloading(int q)
{
    cout << "Called by value " << q << endl;
}
*/
void testReloading(int& q)
{
    cout << "Called by reference " << q << endl;
}

void testReloading(int* q)
{
    cout << "Called by pointer " << q << endl;
}

void setValueToReference(int a, int& b, const int& c = 0)
{
    a += 10;
    b += 200;
}

void flipInts(int* a, int* b = 0)
{
	int tmp = *b;
	*b = *a;
	*a = tmp;
}

const char* base = "0";
const int m = (int)*base;
int toInt(char* string)
{
    int res = 0;
    do
    {
       res *= 10;
       int digit = (int)*string;
       cout << digit << endl;
       res += digit % m;
    } while(*++string);
    return res;
}

char* parseString(int number)
{
    int grade = 0;
    int cp_num = number;
    do{ grade++; cout << cp_num << " ";} while ((cp_num /= 10) > 0);

    char* res = new char[grade + 1];

    int tmp = 0;
    while (number > 0)
    {
        tmp = number % 10;
        number /= 10;
        char val = (char)(tmp + m);
        res[--grade] = val;
        cout << number << endl;
    }
    //res[grade] = "\0";
    return res;
}

b_struct parseDouble(double v)
{
	b_struct res;
	double fractpart, intpart;
	double tmp_val = v;
    while (tmp_val - floor(tmp_val) >= 1.0e-6)
	{
		res.power++;
		tmp_val *= 10;
	}
	res.mantissa = tmp_val;
	return res;
};

TEST(TestByteStruct, simpleStructrure)
{
    char t = 0;
    for (int i = 0; i < 128; i++)
    {
        t = i;
        if ((t >= 'a' && t <= 'z') || (t >= '0' && t <= '9'))
            cout << t << " = " << (int)t << " ";
    }
	cout<<endl;
	double* doub = new double(243454412e-5);
	//cout.precision(20);
	//cout << "double " << FLT_RADIX << endl;
	b_struct instance = parseDouble(*doub);
	cout << "power -" << instance.power << endl;
	cout << "mantissa " << instance.mantissa << endl;
	int m = 2 << 31;
	cout << "Max int " << m << endl;
	int* a1 = new int(195485);
	int* b1 = new int(578323);
	flipInts(a1, b1);
	cout << "A " << *a1 << " B " << *b1 << endl;

	int& a2 = *b1;
	int& b2 = *a1;
	flipInts(&a2, &b2);
	cout << "A " << *a1 << " B " << *b1 << endl;
}

TEST(TestByteStruct, limits)
{
	cout << "int max " << numeric_limits<int>::max() << " min " << numeric_limits<int>::min() << endl;
	cout << "char max " << (int)numeric_limits<char>::max() << " min " << (int)numeric_limits<char>::min() << endl;
	cout << "short max " << numeric_limits<short>::max() << " min " << numeric_limits<short>::min() << endl;
	cout << "long max " << numeric_limits<long>::max() << " min " << numeric_limits<long>::min() << endl;
	cout << "float max " << numeric_limits<float>::max() << " min " << numeric_limits<float>::min() << endl;
	cout << "double max " << numeric_limits<double>::max() << " min " << numeric_limits<double>::min() << endl;
	cout << "unsigned max " << numeric_limits<unsigned>::max() << " min " << numeric_limits<unsigned>::min() << endl;
	cout << "bool max " << numeric_limits<bool>::max() << " min " << numeric_limits<bool>::min() << endl;
}

TEST(TestByteStruct, arrays)
{
	double dbarr[3] = { 1.45, 53.42, 1.3e-3 };
	double* s = dbarr;
	cout << "First " << *s << endl;
//	while (s++)
    //	cout << *s << endl;

	cout << "INTEGERS" << endl;

	int intarr[4] = { 1, 52, 3, 19 };
	int* a = intarr;
	cout << "First int " << *a << endl;
//	while (a++)
//		cout << *a << endl;
    cout << "ToInt " << toInt("100412") << endl;
    char* string = parseString(4823923);
    cout << "parseString 4823923 == " << string << endl;
}

TEST(TestByteStruct, references)
{
    int a0 = 2;
    int a1 = 2;
    setValueToReference(a0, a1);
    cout << "a0 was 2 " << a0 << " a1 was 2 " << a1 <<endl;
    setValueToReference(a1, a0);
    cout << "a1 was 202 " << a1 <<endl;
}

TEST(TestByteStruct, testReload)
{
    int g = 10;
    testReloading(g);
    testReloading(&g);
    void (*efct)(int, int&, const int&);
    efct = &setValueToReference;
    cout << "Pointer to function " << efct << endl;
    (*efct)(g,g, 10);
	cout << "Pointer to function called " << g << endl;
    HW("FML");
}

TEST(TestByteStruct, testCipher)
{
    //char a = (int)"a"^2;
    //cout << "encrypted " << a << endl;
    //cout << "decrypted " << (char)(2^(int)a) << endl;
}
